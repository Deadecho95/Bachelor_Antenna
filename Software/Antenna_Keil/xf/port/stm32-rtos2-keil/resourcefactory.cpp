#include <config/xf-config.h>

#if (USE_XF_PORT_RTOS_KEIL_RESOURCE_FACTORY_IMPLEMENTATION != 0)

#include "thread.h"
#include "mutex.h"
#include "default/dispatcher-active.h"
#include "resourcefactory.h"

//static
interface::XFResourceFactory * interface::XFResourceFactory::getInstance()
{
  static XFResourceFactoryPort theResourceFactory;
	return &theResourceFactory;
}

interface::XFDispatcher * XFResourceFactoryPort::getDefaultDispatcher()
{
	static XFDispatcherActiveDefault mainDispatcher;
	return &mainDispatcher;
}

interface::XFDispatcher * XFResourceFactoryPort::createDispatcher()
{
	return new XFDispatcherActiveDefault;
}

interface::XFThread * XFResourceFactoryPort::createThread(interface::XFThreadEntryPointProvider * pProvider,
													    interface::XFThread::EntryMethodBody entryMethod,
														const char * threadName,
														const uint32_t stackSize /* = 0 */)
{
	return new XFThreadPort(pProvider, entryMethod, threadName, stackSize);
}

interface::XFMutex * XFResourceFactoryPort::createMutex()
{
    return new XFMutexPort;
}

#endif // USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_RESOURCE_FACTORY_IMPLEMENTATION
