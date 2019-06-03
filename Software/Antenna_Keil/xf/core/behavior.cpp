#include <assert.h>
#include "xf/xf.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/timeout.h"
#include "xf/initialevent.h"
#include "xf/behavior.h"

using interface::XFResourceFactory;

XFBehavior::XFBehavior(interface::XFDispatcher * pDispatcher /* = nullptr */) :
    _pDispatcher((pDispatcher) ? pDispatcher : XF::getDefaultDispatcher()),
    _isActive(_pDispatcher != XF::getDefaultDispatcher()),
    _pCurrentEvent(NULL)
{
}

XFBehavior::XFBehavior(bool ownDispatcher) :
    _pDispatcher(nullptr),
    _isActive(ownDispatcher),
    _pCurrentEvent(NULL)
{
    if (ownDispatcher)
    {
        _pDispatcher = XFResourceFactory::getInstance()->createDispatcher();
    }
    else
    {
        _pDispatcher = XF::getDefaultDispatcher();
    }

    // Force isActive attribute to false in case actual
    // dispatcher is the default dispatcher. This may happen
    // if in an IDF an other dispatcher is requested, but
    // only the default dispatcher is present.
    if (_pDispatcher == XF::getDefaultDispatcher())
    {
        _isActive = false;
    }
}

XFBehavior::~XFBehavior()
{

}

void XFBehavior::startBehavior()
{
    // Send initial event to state machine
    GEN(XFInitialEvent());

    // Start dispatcher if behavior has its own active dispatcher
    if (isActive())
    {
        getDispatcher()->start();
    }
}

void XFBehavior::pushEvent(XFEvent * pEvent)
{
    // Set owner
    pEvent->setBehavior(this);
    // Push to dispatchers event queue
    getDispatcher()->pushEvent(pEvent);
}

XFEventStatus XFBehavior::process(const XFEvent * pEvent)
{
    XFEventStatus eventStatus;

    setCurrentEvent(pEvent);

    eventStatus = processEvent();

    setCurrentEvent(NULL);

    return eventStatus;
}

interface::XFDispatcher * XFBehavior::getDispatcher()
{
    return _pDispatcher;
}

void XFBehavior::setCurrentEvent(const XFEvent * pEvent)
{
    _pCurrentEvent = pEvent;
}

const XFEvent * XFBehavior::getCurrentEvent() const
{
    return _pCurrentEvent;
}

const XFTimeout * XFBehavior::getCurrentTimeout()
{
    assert(getCurrentEvent()->getEventType() == XFEvent::Timeout);

    return (const XFTimeout *)getCurrentEvent();
}
