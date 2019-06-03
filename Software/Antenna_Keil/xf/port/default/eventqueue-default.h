#ifndef XF_EVENT_QUEUE_DEFAULT_H
#define XF_EVENT_QUEUE_DEFAULT_H
#ifdef __cplusplus

#include "config/xf-config.h"

#if (USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION != 0)

#include <stdint.h>
#include <queue>
#include "xf/interface/eventqueue.h"

/** @ingroup port_default
 *  @{
 */

/**
 * @brief Default implementation of the event queue using a `std::queue` as container.
 *
 * This class does not provide a blocking pend() method. This means that this class
 * can be used in an IDF, but is not the right choice for a RTOS based XF.
 */
class XFEventQueueDefault : public interface::XFEventQueue
{
public:
    XFEventQueueDefault();
    virtual ~XFEventQueueDefault();

    // XFEventQueue interface implementation
public:
    virtual bool empty() const;							///< Returns true if no event is in the queue.
    virtual bool push(const XFEvent * pEvent);          ///< Pushes the given event onto the queue.
    virtual const XFEvent * front();                    ///< Returns pointer to next event to pop.
    virtual void pop();                                 ///< Pops the next event from the queue.
                                                        ///< Wait for the next event to arrive. Returns true if an event is in the queue.
    virtual bool pend();

protected:
    typedef std::queue<const XFEvent *> EventQueue;		///< Type of the event queue.

    EventQueue _queue;									///< Internal queue holding the events.
};

/** @} */ // end of port_default group
#endif // USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION
#endif // __cplusplus
#endif // XF_EVENT_QUEUE_DEFAULT_H
