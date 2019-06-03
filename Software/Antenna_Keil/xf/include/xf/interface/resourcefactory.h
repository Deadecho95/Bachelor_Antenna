#ifndef XF_INTERFACE_RESOURCE_FACTORY_H
#define XF_INTERFACE_RESOURCE_FACTORY_H

#include "xf/interface/dispatcher.h"
#include "xf/interface/thread.h"
#include "xf/interface/mutex.h"

namespace interface {

/**
 * @brief Responsible to create and return XF resources.
 *
 * The XF resource factory provides instances of following classes
 *  - Dispatcher
 *  - Thread
 *  - Mutex
 *
 * The XFResourceFactory::getInstance() method needs to be implemented
 * in the class realizing this interface.
 *
 */
class XFResourceFactory
{
public:
    static XFResourceFactory * getInstance();   ///< Returns a pointer to the unique instance of the XF resource factory.

    /**
     * @brief Returns the default dispatcher.
     *
     * In case a bahavior does not have a specific dispatcher the
     * default dispatcher ist used.
     *
     * @return A pointer to the default dispatcher.
     */
    virtual interface::XFDispatcher * getDefaultDispatcher() = 0;

    /**
     * @brief Creates a new dispatcher.
     *
     * Per default this method returns a new active dispatcher. In
     * case there is no OS present (IDF) the default dispatcher may
     * be returned.
     *
     * @return The new dispatcher
     */
    virtual interface::XFDispatcher * createDispatcher() = 0;

    /**
     * @brief Creates a new Thread.
     * @param pProvider The instance providing the entry method.
     * @param entryMethod The method to by called by the new thread.
     * @param threadName The name of the thread.
     * @param stackSize The stack size of the thread.
     * @return Pointer to new thread
     *
     * The method may return null in case there is no OS present.
     */
    virtual interface::XFThread * createThread(interface::XFThreadEntryPointProvider * pProvider,
                                               interface::XFThread::EntryMethodBody entryMethod,
                                               const char * threadName,
                                               const uint32_t stackSize = 0) = 0;

    /**
     * @brief Returns a new mutex.
     * @return Pointer to new mutex.
     */
    virtual interface::XFMutex * createMutex() = 0;

    virtual ~XFResourceFactory()
	{
	}

protected:
    XFResourceFactory()
	{
	}
};

} // namespace interface
#endif // XF_INTERFACE_RESOURCE_FACTORY_H
