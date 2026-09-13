#include <assert.h>

#include "sst.h"

static unsigned int faultCount;
static SST_TaskPrio portPrio;

static void taskHandler(SST_Task * const me, SST_Evt const * const e)
{
    (void)me;
    (void)e;
}

void DBC_fault_handler(char const *module, int label)
{
    (void)module;
    (void)label;
    ++faultCount;
}

void SST_Task_setPrio(SST_Task * const me, SST_TaskPrio prio)
{
    me->prio = SST_PRIO_SST(prio);
    portPrio = prio;
}

void SST_start(void) {}
void SST_onStart(void) {}
void SST_onIdle(void) {}

SST_LockKey SST_Task_lock(SST_TaskPrio ceiling)
{
    (void)ceiling;
    return 0U;
}

void SST_Task_unlock(SST_LockKey lock_key)
{
    (void)lock_key;
}

int main(void)
{
    SST_Task task;
    SST_Evt const *queue[1];
    SST_TaskPrio const priority = SST_PRIO(1U, 24U);

    SST_Task_ctor(&task, taskHandler, taskHandler);
    SST_Task_start(&task, priority, queue, 1U, (SST_Evt const *)0);

    assert(faultCount == 0U);
    assert(task.prio == 1U);
    assert(portPrio == priority);
    assert(SST_PRIO_FRAMEWORK(portPrio) == 24U);

    return 0;
}
