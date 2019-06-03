#ifndef XF_INTERFACE_EVENT_QUEUE_H
#define XF_INTERFACE_EVENT_QUEUE_H

#include <stdint.h>

class XFEvent;

namespace interface {

/**
 * @brief Interface to be implemented by the event queue
 */
class XFEventQueue
{
public:
    virtual ~XFEventQueue() {}

    virtual bool empty() const = 0;					///< Returns true if no event is in the queue.
    virtual bool push(const XFEvent * pEvent) = 0;	///< Pushes the given event onto the queue.
    virtual const XFEvent * front() = 0;			///< Returns pointer to next event to pop.
    virtual void pop() = 0;							///< Pops the next event from the queue.
    virtual bool pend() = 0;						///< Wait for the next event to arrive. Returns true if an event is in the queue.

public:
    XFEventQueue() {}
};

} // namespace interface
#endif // XF_INTERFACE_EVENT_QUEUE_H
