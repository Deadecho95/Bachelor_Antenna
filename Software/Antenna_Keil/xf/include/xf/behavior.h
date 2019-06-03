#ifndef XF_BEHAVIOR_H
#define XF_BEHAVIOR_H

#include "xf/interface/reactive.h"
#include "xf/interface/dispatcher.h"
#include "xf/eventstatus.h"
#include "xf/initialevent.h"
#include "xf/nulltransition.h"
#include "xf/timeout.h"

class XFTimeout;

/** @ingroup xf_core
 *  @{
 */

/**
 * @brief Base class for state machines, activities, process and data flows.
 *
 * Reactive class implementing a behavior. This class can be used to
 * implement a state machine behavior or an activity behavior.
 *
 * Override the processEvent() operation in the inherited class to implement
 * your state machine behavior. The processEvent() method gets automatically
 * called every time an event or timeout arrives. The event (or timeout) can
 * be accessed via the getCurrentEvent() method.
 */
class XFBehavior : public interface::XFReactive
{
public:
    #define GEN(event) pushEvent(new event);

    /**
     * @brief Default Constructor
     *
     * Allows to provide a specific dispatcher for this behavior. In case none
     * is given the default dispatcher is automatically taken.
     *
     * @param pDispatcher Reference to dispatcher who will process the behavioral part of this reactive class.
     */
    explicit XFBehavior(interface::XFDispatcher * pDispatcher = nullptr);

    /**
     * @brief To choose between an own dispatcher (active) or the default dispatcher.
     */
    explicit XFBehavior(bool ownDispatcher);
    virtual ~XFBehavior();

    virtual void startBehavior();					///< Starts the behavior, resp. the state machine.

    virtual void pushEvent(XFEvent * pEvent);

protected:
    /**
     * Executes the current event in its implemented behavior.
     * This method needs to be overridden to implement the
     * behavior (i.e. state machine) needed.
     */
    virtual XFEventStatus processEvent() = 0;

    const XFEvent * getCurrentEvent() const;					///< Returns the current event to be processed in processEvent().
    interface::XFDispatcher * getDispatcher();					///< Returns reference to #_pDispatcher.
    inline bool isActive() const { return _isActive; }			///< True if behavior has its own active dispatcher.


    /** \brief Returns a reference to the actually processed timeout.
     *
     * Will work only if the current event is of type IXFEvent::Timeout.
     */
    const XFTimeout * getCurrentTimeout();

    inline void scheduleTimeout(int timeoutId, int interval) { getDispatcher()->scheduleTimeout(timeoutId, interval, this); }	///< @brief Schedules a timeout for this state machine.
    inline void unscheduleTimeout(int timeoutId) { getDispatcher()->unscheduleTimeout(timeoutId, this); }						///< @brief Unschedules a timeout for this state machine.

private:
    void setCurrentEvent(const XFEvent * pEvent);		///< Sets the current event to be processed in processEvent().

    /**
     * \brief Processes the given event.
     *
     * The dispatcher calls this method every time a new event
     * or timeout arrives. The process method stores the actual
     * event using the #_pCurrentEvent and then calls
     * processEvent().
     *
     * This method must be only called by the associated dispatcher
     * (see #_pDispatcher).
     *
     * In case you intend to call process() inside your state machine you
     * are doing something wrong! Call GEN() or pushEvent() instead!
     *
     * \param pEvent The event to process.
     */
    virtual XFEventStatus process(const XFEvent * pEvent);


protected:
    interface::XFDispatcher * _pDispatcher;			///< Reference to dispatcher processing this behavior.
    bool _isActive;									///< True if behavior has its own active dispatcher.
    const XFEvent * _pCurrentEvent;					///< Reference to actually processed event.
};

/** @} */ // end of xf_core group
#endif // XF_BEHAVIOR_H
