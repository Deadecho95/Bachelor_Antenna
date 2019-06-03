#ifndef XF_PORT_IDF_QT_EVENT_QUEUE_H
#define XF_PORT_IDF_QT_EVENT_QUEUE_H

#include "config/xf-config.h"

#if (USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION != 0)

#include <stdint.h>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include "xf/interface/eventqueue.h"

/** @ingroup port_idf_qt
 *  @{
 */

/**
 * @brief XFEventQueuePort implementation for the IDF Qt port.
 */
class XFEventQueuePort : public interface::XFEventQueue
{
public:
    XFEventQueuePort();
    virtual ~XFEventQueuePort();

    // XFEventQueue interface implementation
public:
    virtual bool empty() const;                     ///< Returns true if no event is in the queue.
    virtual bool push(const XFEvent * pEvent);      ///< Pushes the given event onto the queue.
    virtual const XFEvent * front();                ///< Returns pointer to next event to pop.
    virtual void pop();                             ///< Pops the next event from the queue.
    virtual bool pend();                            ///< Wait for the next event to arrive. Returns true if an event is in the queue.

protected:
    typedef QQueue<const XFEvent *> EventQueue;     ///< Type of the event queue.

    QMutex _mutex;                                  ///< Mutex protecting access to _queue.
    QWaitCondition _newEvents;                      ///< Wait condition to let thread wait until a new event arrives.
    EventQueue _queue;                              ///< Internal queue holding the events.
};

/** @} */ // end of port_idf_qt group
#endif // USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION
#endif // XF_PORT_IDF_QT_EVENT_QUEUE_H
