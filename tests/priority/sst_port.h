#ifndef TEST_SST_PORT_H_
#define TEST_SST_PORT_H_

#include <stdint.h>

typedef uint16_t SST_TaskPrio;

#define SST_PRIO(sst_, framework_) \
    ((SST_TaskPrio)(((uint16_t)(framework_) << 8U) | (uint16_t)(sst_)))

#define SST_PORT_TASK_OPER \
    void SST_Task_setPrio(SST_Task * const me, SST_TaskPrio prio);

#define SST_PORT_CRIT_STAT
#define SST_PORT_CRIT_ENTRY() ((void)0)
#define SST_PORT_CRIT_EXIT()  ((void)0)
#define SST_PORT_TASK_PEND()  ((void)0)

typedef uint32_t SST_LockKey;

void SST_onIdle(void);

#endif
