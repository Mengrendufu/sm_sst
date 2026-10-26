//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
//============================================================================
#include "sst_time_evt.h"
#include "sst_port.h"
#include "dbc_assert.h"
#include <stddef.h>

DBC_MODULE_NAME("sst_time_evt")

static TimeEvt *TimeEvt_head_;

void TimeEvt_ctor(TimeEvt *me, void const *event,
                  TimeEvt_PostOperations const *delivery) {
    DBC_REQUIRE(100, me != NULL);
    DBC_REQUIRE(101, event != NULL);
    DBC_REQUIRE(102, delivery != NULL && delivery->post != NULL);
    for (TimeEvt *node = TimeEvt_head_; node != NULL; node = node->next) {
        DBC_REQUIRE(103, node != me);
    }
    me->event = event;
    me->delivery = delivery;
    me->remaining = 0U;
    me->interval = 0U;
    me->next = TimeEvt_head_;
    TimeEvt_head_ = me;
}

void TimeEvt_arm(TimeEvt *me, uint32_t delay, uint32_t interval) {
    DBC_REQUIRE(200, me != NULL && me->delivery != NULL);
    DBC_REQUIRE(201, delay > 0U);
    SST_PORT_CRIT_STAT
    SST_PORT_CRIT_ENTRY();
    me->remaining = delay;
    me->interval = interval;
    SST_PORT_CRIT_EXIT();
}

bool TimeEvt_disarm(TimeEvt *me) {
    DBC_REQUIRE(300, me != NULL && me->delivery != NULL);
    SST_PORT_CRIT_STAT
    SST_PORT_CRIT_ENTRY();
    bool const active = (me->remaining != 0U);
    me->remaining = 0U;
    me->interval = 0U;
    SST_PORT_CRIT_EXIT();
    return active;
}

void TimeEvt_tick(void) {
    for (TimeEvt *node = TimeEvt_head_; node != NULL; node = node->next) {
        bool expired = false;
        SST_PORT_CRIT_STAT
        SST_PORT_CRIT_ENTRY();
        if (node->remaining != 0U && --node->remaining == 0U) {
            node->remaining = node->interval;
            expired = true;
        }
        SST_PORT_CRIT_EXIT();
        if (expired) {
            node->delivery->post(node->delivery->context, node->event);
        }
    }
}
