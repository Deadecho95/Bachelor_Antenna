#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_PORT_RTOS_KEIL_MUTEX_IMPLEMENTATION != 0)

#include "mutex.h"

XFMutexPort::XFMutexPort() :
	_mutexId(0)
{
	_mutexId = osMutexNew(&_mutexDefinition);
	assert(_mutexId);
}

XFMutexPort::~XFMutexPort()
{

}

void XFMutexPort::lock()
{
	assert(_mutexId);
	osStatus_t status = osMutexAcquire(_mutexId, osWaitForever);
	assert(status == osOK);
}


void XFMutexPort::unlock()
{
	osStatus_t status = osMutexRelease(_mutexId);
	assert(status == osOK);
}


bool XFMutexPort::tryLock(int32_t timeout /* = 0 */)
{
	osStatus_t status = osMutexAcquire(_mutexId, timeout);
	return (status == osOK) ? true : false;
}

#endif // USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_IMPLEMENTATION
