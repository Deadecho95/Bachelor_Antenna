#ifndef XF_TIMEOUT_H
#define XF_TIMEOUT_H

#include "xf/event.h"

namespace interface {
    class XFTimeoutManager;
}

/** @ingroup xf_core
 *  @{
 */

/**
 * @brief Used by the TimeoutManager to create and handle a timeout.
 *
 * Timeouts are created automatically by the TimeoutManager when
 * scheduling a timeout. After expiration they are queued to the event queue
 * and afterwards dispatched to the corresonding behavior.
 *
 * A timeout can be identified by checking against #Timeout using
 * the `getEventType()` method.
 *
 * XFTimeout is inheriting from XFEvent, so every timeout is
 * also an event.
 */
class XFTimeout : public XFEvent
{
    friend class interface::XFTimeoutManager;

public:
	/**
	 * Constructor of the class.
	 * \param id The id given by the behavioral class to uniquely identifying the timeout
	 * \param interval The interval in milliseconds the timeout expires
	 * \param pBehavior Pointer to behavioral class to which the timeout belongs
	 */
	XFTimeout(int id, int interval, interface::XFReactive * pBehavior);
	virtual ~XFTimeout();

	/**
	 * Operator checks if #_pBehavior and #_id are equal and returns
	 * true if so. All other attributes get no attention.
	 */
	bool operator ==(const XFTimeout & timeout) const;

    bool deleteAfterConsume() const override;                                                       ///< Tells the dispatcher if the event must be deleted or not.

    inline void setRelTicks(int relTicks) { _relTicks = relTicks; }                                 ///< Sets remaining ticks.
    inline int getRelTicks() const { return _relTicks; }                                            ///< Returns remaining ticks.
    inline void substractFromRelTicks(int ticksToSubstract) { _relTicks -= ticksToSubstract; }      ///< Substracts `ticksToSubstract` from remaining ticks.
    inline void addToRelTicks(int ticksToAdd) { _relTicks += ticksToAdd; }                          ///< Adds `ticksToAdd` to remaining ticks.

protected:
	int _interval;		///< Timeout interval
    int _relTicks;		///< Used by the TimeoutManager to calculate remaining time. Can get negative!
};

/** @} */ // end of xf_core group
#endif // XF_TIMEOUT_H
