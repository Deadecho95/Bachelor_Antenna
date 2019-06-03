#ifndef XF_RESOURCE_FACTORY_DEFAULT_H
#define XF_RESOURCE_FACTORY_DEFAULT_H

#include <config/xf-config.h>

#if (USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION != 0)

#include "xf/interface/resourcefactory.h"
#include "dispatcher-default.h"

/** @ingroup port_default
 *  @{
 */

/**
 * @brief Default implementation of the XF resource factory.
 */
class XFResourceFactoryDefault : public interface::XFResourceFactory
{
public:
	virtual ~XFResourceFactoryDefault() {}
	
	static interface::XFResourceFactory * getInstance();		///< Returns a pointer to the unique instance of the XF resource factory.
	
	virtual interface::XFDispatcher * getDefaultDispatcher();										///< Returns the default dispatcher.
	virtual interface::XFDispatcher * createDispatcher();                                           ///< Creates and returns a new dispatcher.
	virtual interface::XFThread * createThread(interface::XFThreadEntryPointProvider * pProvider,   
											   interface::XFThread::EntryMethodBody entryMethod,    
											   const char * threadName,                             
											   const uint32_t stackSize = 0);                       ///< Creates and returns a new thread.
	virtual interface::XFMutex * createMutex();                                                     ///< Creates and returns a new mutex.
	
protected:
	XFResourceFactoryDefault() {}

protected:
	XFDispatcherDefault _mainDispatcher;		///< The default/main dispatcher.
};

/** @} */ // end of port_default group
#endif // USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION
#endif // XF_RESOURCE_FACTORY_DEFAULT_H
