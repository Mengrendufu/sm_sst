/*===========================================================================
* Super-Simple Tasker (SST/C) publish-subscribe API
*
* Copyright (C) 2005-2023 Quantum Leaps, <state-machine.com>.
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
#ifndef SST_PUBSUB_H_
#define SST_PUBSUB_H_

#include "sst.h" /* Super-Simple Tasker (SST) */

typedef uint32_t SST_PubSubSet;

typedef struct {
    SST_PubSubSet set;
} SST_SubscrList;

void SST_PubSub_init(SST_SubscrList * const subscrSto,
                     SST_Signal maxPubSig);
void SST_Task_subscribe(SST_Task * const me, SST_Signal sig);
void SST_Task_unsubscribe(SST_Task * const me, SST_Signal sig);
void SST_publish(SST_Evt const * const e);

#endif /* SST_PUBSUB_H_ */
