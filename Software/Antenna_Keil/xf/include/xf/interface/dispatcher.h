#ifndef XF_INTERFACE_DISPATCHER_H
#define XF_INTERFACE_DISPATCHER_H

#include "xf/event.h"

class XF;

namespace interface {

class XFReactive;
class XFThread;

/**
 * @brief Interface for the XF dispatcher providing the event processing loop.
 *
 * Depending on the implementation the dispatcher is executed by
 * an internal thread. It is up to the port implementation how
 * the class behaves.
 *
 * The dispatcher should at least provide a queue to hold events
 * and an algorithm (typically in execute()) that dispatches the queued
 * events to the associated behavior (eq. state machine, activity).
 *
 * There may exist multiple dispatchers. Each behavior needs to be
 * bound to a dispatcher. One dispatcher may serve different behaviors.
 *
 * In an IDF the attribute _pThread is usually null.
 */
class XFDispatcher
{
	friend class ::XF;

public:
    virtual ~XFDispatcher()
    {}

    virtual void initialize() = 0;                                  ///< Initializes the dispatcher.
    virtual bool isActive() const = 0;								///< True if dispatcher has its own thread.

    virtual void start() = 0;										///< Starts the thread.
    virtual void stop() = 0;										///< Stops the thread.
    virtual void pushEvent(XFEvent * pEvent) = 0;					///< Adds event to the events queue.

    /**
     * Adds a new timeout to be handled. The Thread will forward the timeout
     * information to the timeout manager which is responsible to handle all timeouts.
     */
    virtual void scheduleTimeout(int timeoutId, int interval, interface::XFReactive * pReactive) = 0;

    /**
     * Removes all timeouts corresponding the given parameters.
     */
    virtual void unscheduleTimeout(int timeoutId, interface::XFReactive * pReactive) = 0;

protected:
    /**
     * Constructor is protected because only method createInstance()
     * should be called to create Dispatcher instances
     */
    XFDispatcher()
    {}

    /**
     * @brief Returns pointer to thread executing the behavior.
     *
     * Within an IDF no threads are present and this method returns
     * always null.
     */
    virtual interface::XFThread * getThread() const { return nullptr; }

    /**
     * Main loop of the dispatcher. Implements event loop processing.
     */
    virtual int execute(const void * param = nullptr) = 0;

    /**
     * @brief Executes once the dispatcher.
     *
     * Usually, this method must not be called explicitly. The
     * standard way to call the dispatcher is to call execute().
     *
     * This method can be called by the Thread (or main function) if it
     * must perform concurrent (non-XF related) tasks in addition.
     *
     * When using this method start() must not be called.
     */
    virtual int executeOnce() = 0;

    /**
     * Dispatches the event to the corresponding behavioral part. For example
     * the state machine which should process the event.
     * \param pEvent The event to dispatch
     */
    virtual void dispatchEvent(const XFEvent * pEvent) const = 0;
};

} // namespace interface
#endif // XF_INTERFACE_DISPATCHER_H
