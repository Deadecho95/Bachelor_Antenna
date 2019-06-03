#include <config/xf-config.h>

#if (USE_XF_PORT_RTOS_KEIL_THREAD_IMPLEMENTATION != 0)

#include <assert.h>
#include <string.h>
#include "thread.h"

#if !defined(XFTHREAD_DEFAULT_STACK_SIZE)
#	define XFTHREAD_DEFAULT_STACK_SIZE	128
#endif

//extern "C" const int  uxTopUsedPriority;
//const int __attribute__((used)) uxTopUsedPriority = configMAX_PRIORITIES - 1;

XFThreadPort::XFThreadPort(interface::XFThreadEntryPointProvider * pProvider,
	   	   	   	   	   	   interface::XFThread::EntryMethodBody entryMethod,
				 	 	   const char * threadName,
				 	 	   const uint32_t stackSize /* = 0 */)
{
	uint32_t threadStackSize = stackSize;

	_pEntryMethodProvider = pProvider;
	_entryMethod = entryMethod;

	strcpy(_threadName, threadName);

	if (threadStackSize == 0)
	{
		threadStackSize = XFTHREAD_DEFAULT_STACK_SIZE;
	}

	_threadDefinition.name = _threadName;
	_threadDefinition.priority = osPriorityNormal;
	_threadDefinition.stack_size = threadStackSize;

	_threadId = osThreadNew(threadEntryPoint, this, &_threadDefinition);
	assert(_threadId);		// Check if thread creation was successful

	// Always keep threads after creation in suspended state.
	// Must be explicitly started with start();
	suspend();
}

//static
void XFThreadPort::threadEntryPoint(void * param)
{
	XFThreadPort * pThis = (XFThreadPort *)param;

	(pThis->_pEntryMethodProvider->*pThis->_entryMethod)(param);
}

void XFThreadPort::start()
{
	assert(_threadId != 0);		// Check if thread was created
	osThreadResume(_threadId);
}

void XFThreadPort::suspend()
{
	osThreadSuspend(_threadId);
}

void XFThreadPort::stop()
{
	osThreadTerminate(_threadId);
}

void XFThreadPort::setPriority(XFThreadPriority priority)
{
    osPriority_t prio = osPriorityNormal;
    switch (priority)
    {
    case XF_THREAD_PRIO_LOW:
        prio = osPriorityLow;
        break;
    case XF_THREAD_PRIO_HIGH:
        prio = osPriorityHigh;
        break;
    default:
        break;
    }

    osThreadSetPriority(_threadId, prio);
}

XFThreadPriority XFThreadPort::getPriority() const
{
    const osPriority_t prio = osThreadGetPriority(_threadId);
    XFThreadPriority priority = XF_THREAD_PRIO_UNKNOWN;

    switch (prio)
    {
    case osPriorityLow:
        priority = XF_THREAD_PRIO_LOW;
        break;
    case osPriorityNormal:
        priority = XF_THREAD_PRIO_NORMAL;
        break;
    case osPriorityHigh:
        priority = XF_THREAD_PRIO_HIGH;
        break;
    default:
        break;
    }

    return priority;
}

void XFThreadPort::delay(uint32_t milliseconds)
{
	osDelay(milliseconds);
}

#endif // USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_THREAD_IMPLEMENTATION
