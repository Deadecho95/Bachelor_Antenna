#include <config/xf-config.h>

#if (USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION != 0)

#include "resourcefactory-default.h"
#include "mutex-default.h"

//static
interface::XFResourceFactory * interface::XFResourceFactory::getInstance()
{
	return XFResourceFactoryDefault::getInstance();
}

//static
interface::XFResourceFactory * XFResourceFactoryDefault::getInstance()
{
    static XFResourceFactoryDefault theResourceFactory;

	return &theResourceFactory;
}

interface::XFDispatcher * XFResourceFactoryDefault::getDefaultDispatcher()
{
	return &_mainDispatcher;
}

interface::XFDispatcher * XFResourceFactoryDefault::createDispatcher()
{
	// Default implementation cannot create new dispatcher. Return the default dispatcher
	return getDefaultDispatcher();
}

interface::XFThread * XFResourceFactoryDefault::createThread(interface::XFThreadEntryPointProvider * pProvider,
												  	  	     interface::XFThread::EntryMethodBody entryMethod,
														     const char * threadName,
														     const uint32_t stackSize /* = 0 */)
{
	// Default implementation cannot create threads (no underlying OS present)
	return nullptr;
}

interface::XFMutex * XFResourceFactoryDefault::createMutex()
{
	static XFMutexDefault mutex;

	return &mutex;
}

#endif // USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION
