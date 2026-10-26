// Host-only example port. Embedded clients supply their own header.
#ifndef TEST_SST_TIME_EVT_PORT_H_
#define TEST_SST_TIME_EVT_PORT_H_

#include <stddef.h>
#include <stdbool.h>

unsigned TimeEvt_testEnter(void);
void TimeEvt_testExit(unsigned previous);

// A saved critical-state token also supports ports that restore IRQ state.
#define SST_PORT_CRIT_STAT unsigned timeEvtCriticalState_;
#define SST_PORT_CRIT_ENTRY() \
    (timeEvtCriticalState_ = TimeEvt_testEnter())
#define SST_PORT_CRIT_EXIT() TimeEvt_testExit(timeEvtCriticalState_)

#endif // TEST_SST_TIME_EVT_PORT_H_
