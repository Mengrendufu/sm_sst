/*===========================================================================
* Super-Simple Tasker (SST/C)
*
* Copyright (C) 2006-2023 Quantum Leaps, <state-machine.com>.
*
* SPDX-License-Identifier: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
===========================================================================*/
#include "sst_pubsub.h" /* SST publish-subscribe */
#include "sst_priv.h"   /* SST private package API */
#include "dbc_assert.h" /* Design By Contract (DBC) assertions */

//============================================================================
DBC_MODULE_NAME("sst_pubsub") /* for DBC assertions in this module */

//============================================================================
static SST_SubscrSet *l_subscr_;
static SST_Signal l_maxPubSig_;

//============================================================================
void SST_PubSub_init(SST_SubscrSet * const subscrSto,
                     SST_Signal const maxPubSig)
{
    DBC_REQUIRE(250, subscrSto != (SST_SubscrSet *)0);
    DBC_REQUIRE(251, maxPubSig > 0U);

    l_subscr_ = subscrSto;
    l_maxPubSig_ = maxPubSig;

    for (SST_Signal sig = 0U; sig < maxPubSig; ++sig) {
        l_subscr_[sig] = (SST_SubscrSet)0;
    }
}
//............................................................................
void SST_Task_subscribe(SST_Task * const me, SST_Signal const sig) {
    DBC_REQUIRE(400, me != (SST_Task *)0);
    DBC_REQUIRE(401, l_subscr_ != (SST_SubscrSet *)0);
    DBC_REQUIRE(402, (0U < sig) && (sig < l_maxPubSig_));

    SST_PORT_CRIT_STAT
    SST_PORT_CRIT_ENTRY();

    SST_TaskPrio const prio = me->prio;
    DBC_REQUIRE(403, (0U < prio) && (prio <= SST_MAX_TASK));
    DBC_REQUIRE(404, SST_tasks_[prio] == me);
    l_subscr_[sig] |= (SST_SubscrSet)1U << (prio - 1U);

    SST_PORT_CRIT_EXIT();
}
//............................................................................
void SST_Task_unsubscribe(SST_Task * const me, SST_Signal const sig) {
    DBC_REQUIRE(500, me != (SST_Task *)0);
    DBC_REQUIRE(501, l_subscr_ != (SST_SubscrSet *)0);
    DBC_REQUIRE(502, (0U < sig) && (sig < l_maxPubSig_));

    SST_PORT_CRIT_STAT
    SST_PORT_CRIT_ENTRY();

    SST_TaskPrio const prio = me->prio;
    DBC_REQUIRE(503, (0U < prio) && (prio <= SST_MAX_TASK));
    DBC_REQUIRE(504, SST_tasks_[prio] == me);
    l_subscr_[sig] &= ~((SST_SubscrSet)1U << (prio - 1U));

    SST_PORT_CRIT_EXIT();
}
//............................................................................
void SST_publish(SST_Evt const * const e) {
    DBC_REQUIRE(600, e != (SST_Evt const *)0 &&
                     l_subscr_ != (SST_SubscrSet *)0 &&
                     (0U < e->sig) && (e->sig < l_maxPubSig_));

    SST_PORT_CRIT_STAT
    SST_PORT_CRIT_ENTRY();

    SST_SubscrSet subscr = l_subscr_[e->sig];
#if (SST_EVT_POOL_NUM > 0U)
    if (e->poolId != 0U) {
        DBC_INVARIANT(606, e->poolId <= SST_EVT_POOL_NUM
                           && e->refCtr < 255U);
        ++((SST_Evt *)e)->refCtr;
    }
#endif // (SST_EVT_POOL_NUM > 0U)

    SST_PORT_CRIT_EXIT();

    while (subscr != (SST_SubscrSet)0) {
        SST_TaskPrio const prio = (SST_TaskPrio)SST_LOG2(subscr);
        DBC_INVARIANT(603, (0U < prio && prio <= SST_MAX_TASK) &&
                           SST_tasks_[prio] != (SST_Task *)0);

        // SST_tasks_[prio] is set once during task start and never
        // cleared (no unregister). Safe to read outside critical section.
        // If task stop is ever added, re-add the critical section here.
        SST_Task * const target = SST_tasks_[prio];

        SST_Task_post(target, e);
        subscr &= ~((SST_SubscrSet)1U << (prio - 1U));
    }

    SST_GC(e);
}
