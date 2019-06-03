#ifndef XF_PORT_STM32CUBE_CMSIS_FREERTOS_EVENT_QUEUE_H
#define XF_PORT_STM32CUBE_CMSIS_FREERTOS_EVENT_QUEUE_H
#ifdef __cplusplus

#include <config/xf-config.h>

#if (USE_XF_PORT_RTOS_KEIL_EVENT_QUEUE_IMPLEMENTATION != 0)

#include "xf/interface/eventqueue.h"
#include "cmsis_os2.h" 
#include <stdint.h>
#include <queue>

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

    EventQueue _queue;	
};

#endif // USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_EVENT_QUEUE_IMPLEMENTATION
#endif // __cplusplus
#endif // XF_PORT_STM32CUBE_CMSIS_FREERTOS_EVENT_QUEUE_H
