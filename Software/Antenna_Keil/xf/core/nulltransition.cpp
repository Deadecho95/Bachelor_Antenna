#include "xf/nulltransition.h"

XFNullTransition::XFNullTransition(interface::XFReactive * pBehavior)
 : XFEvent(XFEvent::NullTransition, 0, pBehavior)
{
}

XFNullTransition::~XFNullTransition()
{

}

bool XFNullTransition::deleteAfterConsume() const
{
    return true;
}
