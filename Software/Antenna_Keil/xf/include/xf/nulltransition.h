#ifndef XF_NULLTRANSITION_H
#define XF_NULLTRANSITION_H

#include "xf.h"
#include "xf/event.h"

/** @ingroup xf_core
 *  @{
 */

/**
 * @brief State machine transition without trigger.
 *
 * Represents a transition in a state machine having no trigger.
 *
 * In case one wants to directly transition from one state to
 * an other (without a trigger) a null transition must be pushed.
 */
class XFNullTransition : public XFEvent
{
public:
	/**
	 * Constructor
	 *
	 * \param pBehavior Behavior in which the null transition will be executed.
	 */
	XFNullTransition(interface::XFReactive * pBehavior = nullptr);
	virtual ~XFNullTransition();

	bool deleteAfterConsume() const override;
};

/** @} */ // end of xf_core group
#endif // XF_NULLTRANSITION_H
