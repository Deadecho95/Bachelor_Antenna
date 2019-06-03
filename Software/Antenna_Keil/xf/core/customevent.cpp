#include "xf/customevent.h"

XFCustomEvent::XFCustomEvent(int id, interface::XFReactive * pBehavior)
	: XFEvent(XFEvent::Event, id, pBehavior),
	  _bDeleteAfterConsume(true)
{

}

XFCustomEvent::~XFCustomEvent()
{

}
