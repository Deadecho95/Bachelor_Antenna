#include "xf/timeout.h"

XFTimeout::XFTimeout(int id, int interval, interface::XFReactive * pBehavior)
 : XFEvent(XFEvent::Timeout, id, pBehavior),
   _interval(interval),
   _relTicks(interval)
{
}

XFTimeout::~XFTimeout()
{
}

bool XFTimeout::operator ==(const XFTimeout & timeout) const
{
	// Check behavior and timeout id attributes, if there are equal
	return (_pBehavior == timeout._pBehavior && getId() == timeout.getId()) ? true : false;
}

bool XFTimeout::deleteAfterConsume() const
{
	return true;
}
