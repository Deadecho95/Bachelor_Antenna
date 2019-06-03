#ifndef XF_INTERFACE_THREAD_H
#define XF_INTERFACE_THREAD_H

#include "stdint.h"

typedef enum
{
    XF_THREAD_PRIO_UNKNOWN = 0,
    XF_THREAD_PRIO_LOW = 5,
    XF_THREAD_PRIO_NORMAL = 10,
    XF_THREAD_PRIO_HIGH = 15,
    XF_THREAD_PRIO_MAX = 20
} XFThreadPriority;

namespace interface {

/**
 * @brief Interface to be implemented by the class providing the thread entry method.
 */
class XFThreadEntryPointProvider
{
public:
    virtual ~XFThreadEntryPointProvider(){}
protected:
    XFThreadEntryPointProvider(){}
};

/**
 * @brief Interface for a Thread.
 *
 * Thread interface representing the instance executing the behavior. In an OS less XF
 * (hence an IDF), usually this class is not needed. In an XF interfacing an OS,
 * multiple instances can be made, each interfacing the real OS thread.
 *
 * Thread instances can be created using the ResourceFactory instance.
 *
 * The XF assumes that the Thread is in suspend state after creation. Automatically
 * starting the thread after creation may lead to unwanted behavior!
 */
class XFThread
{
public:
    virtual ~XFThread(){}

    typedef void (XFThreadEntryPointProvider::*EntryMethodBody)(const void *);  ///< Prototype of method to be executed by the thread.

    virtual void start() = 0;                                                   ///< Starts the thread.
    virtual void suspend() = 0;                                                 ///< Suspends the thread.
    virtual void stop() = 0;                                                    ///< Requests the thread to stop execution.

    virtual void setPriority(XFThreadPriority priority) = 0;                    ///< Set the thread priority.
    virtual XFThreadPriority getPriority() const = 0;                           ///< Returns the thread priority.

    virtual void delay(uint32_t milliseconds) = 0;                              ///< Causes the thread to sleep (for the given milliseconds).

protected:
    XFThread(){}
};

} // namespace interface
#endif // XF_INTERFACE_THREAD_H
