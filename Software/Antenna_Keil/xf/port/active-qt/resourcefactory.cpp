#include <config/xf-config.h>

#if (USE_XF_PORT_ACTIVE_QT_RESOURCE_FACTORY_IMPLEMENTATION != 0)

#include <QtGlobal>
#include "idf-qt/mutex.h"
#include "idf-qt/thread.h"
#include "default/dispatcher-active.h"
#include "resourcefactory.h"

//static
interface::XFResourceFactory * interface::XFResourceFactory::getInstance()
{
    return XFResourceFactoryPort::getInstance();
}

// static
interface::XFResourceFactory * XFResourceFactoryPort::getInstance()
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
    // Create the new active dispatcher
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

#endif // USE_XF_PORT_ACTIVE_QT_RESOURCE_FACTORY_IMPLEMENTATION
