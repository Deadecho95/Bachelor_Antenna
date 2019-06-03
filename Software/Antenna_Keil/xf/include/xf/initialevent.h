#ifndef INITIALEVENT_H
#define INITIALEVENT_H

#include "xf/event.h"

/** @ingroup xf_core
 *  @{
 */

/**
 * @brief Initial event to start a behavior.
 *
 * Represents for example the first transition executed
 * in a state machine.
 */
class XFInitialEvent : public XFEvent
{
public:
	XFInitialEvent();
	virtual ~XFInitialEvent();

    bool deleteAfterConsume() const override;
};

/** @} */ // end of xf_core group
#endif // INITIALEVENT_H
