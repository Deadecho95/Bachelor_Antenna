#include "xf/initialevent.h"

XFInitialEvent::XFInitialEvent()
	: XFEvent(XFEvent::Initial, 0, 0)
{
}

XFInitialEvent::~XFInitialEvent()
{

}

bool XFInitialEvent::deleteAfterConsume() const
{
    return true;
}
