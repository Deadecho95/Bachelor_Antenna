#ifndef XF_PORT_ACTIVE_QT_RESOURCE_FACTORY_H
#define XF_PORT_ACTIVE_QT_RESOURCE_FACTORY_H

#include "config/xf-config.h"

#if (USE_XF_PORT_ACTIVE_QT_RESOURCE_FACTORY_IMPLEMENTATION != 0)

#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"

class XFResourceFactoryPort : public interface::XFResourceFactory
{
public:
    virtual ~XFResourceFactoryPort() {}

    static interface::XFResourceFactory * getInstance();
	
    virtual interface::XFDispatcher * getDefaultDispatcher();
    virtual interface::XFDispatcher * createDispatcher();
    virtual interface::XFThread * createThread(interface::XFThreadEntryPointProvider * pProvider,
                                             interface::XFThread::EntryMethodBody entryMethod,
                                             const char * threadName,
                                             const uint32_t stackSize = 0);
    virtual interface::XFMutex * createMutex();

protected:
    XFResourceFactoryPort() {}
};

#endif // USE_XF_PORT_ACTIVE_QT_RESOURCE_FACTORY_IMPLEMENTATION
#endif // XF_PORT_ACTIVE_QT_RESOURCE_FACTORY_H
