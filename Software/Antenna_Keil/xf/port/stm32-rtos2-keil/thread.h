#ifndef XF_PORT_STM32CUBE_CMSIS_FREERTOS_THREAD_H
#define XF_PORT_STM32CUBE_CMSIS_FREERTOS_THREAD_H

#include <config/xf-config.h>

#if (USE_XF_PORT_RTOS_KEIL_THREAD_IMPLEMENTATION != 0)

#include <stdint.h>
#include "cmsis_os2.h" 
#include "xf/interface/thread.h"

class XFThreadPort : public interface::XFThread
{
	friend class XFResourceFactoryPort;

public:
	virtual void start();
	virtual void suspend();
	virtual void stop();

	virtual void setPriority(XFThreadPriority priority);
	virtual XFThreadPriority getPriority() const;

	virtual void delay(uint32_t milliseconds);

protected:
	XFThreadPort(interface::XFThreadEntryPointProvider * pProvider,
		   	   	 interface::XFThread::EntryMethodBody entryMethod,
				 const char * threadName,
				 const uint32_t stackSize = 0);

	static void threadEntryPoint(void * param);

protected:
	interface::XFThreadEntryPointProvider * _pEntryMethodProvider;
	interface::XFThread::EntryMethodBody _entryMethod;

	osThreadAttr_t _threadDefinition;
	char _threadName[32];

	osThreadId_t _threadId;
};

#endif // USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_THREAD_IMPLEMENTATION
#endif // XF_PORT_STM32CUBE_CMSIS_FREERTOS_THREAD_H
