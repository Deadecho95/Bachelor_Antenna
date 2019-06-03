#ifndef XF_INTERFACE_REACTIVE_H
#define XF_INTERFACE_REACTIVE_H

#include <string>
#include "xf/event.h"
#include "xf/eventstatus.h"

class XFDispatcherDefault;
class XFDispatcherActiveDefault;
class XFDispatcherPort;
class XFDispatcherActivePort;

namespace interface {

/**
 * @brief Interface to receive and process events.
 *
 * Interface that needs to be implemented by every class having a
 * behavior. Interface methods are needed by the other parts of the XF.
 *
 * This interface is used by the dispatcher to process events.
 */
class XFReactive
{
	friend class ::XFDispatcherDefault;
	friend class ::XFDispatcherActiveDefault;
	friend class ::XFDispatcherPort;
    friend class ::XFDispatcherActivePort;

public:
    virtual ~XFReactive() {}

    virtual void startBehavior() = 0;                           ///< Starts the behavior.
    virtual void pushEvent(XFEvent * pEvent) = 0;               ///< Injects an event into the class.

protected:
    virtual XFEventStatus process(const XFEvent * pEvent) = 0;	///< Called by the dispatcher to process an event.

protected:
    XFReactive() {}
};

} // namespace interface
#endif // XF_INTERFACE_REACTIVE_H
