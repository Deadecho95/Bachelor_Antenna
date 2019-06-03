#ifndef XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_H
#define XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_H

#include <config/xf-config.h>

#if (USE_XF_PORT_RTOS_KEIL_MUTEX_IMPLEMENTATION != 0)

#include <stdint.h>
#include "cmsis_os2.h" 
#include "xf/interface/mutex.h"

class XFMutexPort : public interface::XFMutex
{
public:
	XFMutexPort();
	virtual ~XFMutexPort();

	virtual void lock();
	virtual void unlock();

	virtual bool tryLock(int32_t timeout = 0);

protected:
	osMutexAttr_t _mutexDefinition;
	osMutexId_t _mutexId;
};

#endif // USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_IMPLEMENTATION
#endif // XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_H
