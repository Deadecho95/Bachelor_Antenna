#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION != 0)
#if (XF_TRACE_EVENT_PUSH_POP != 0)
    #include "trace/trace.h"
#endif // XF_TRACE_EVENT_PUSH_POP
#include "xf/eventstatus.h"
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/reactive.h"
#include "xf/interface/resourcefactory.h"
#include "dispatcher-default.h"

using interface::XFTimeoutManager;
using interface::XFResourceFactory;

XFDispatcherDefault::XFDispatcherDefault() :
	_bInitialized(false),
	_bExecuting(false),
	_pMutex(nullptr)
{

}

XFDispatcherDefault::~XFDispatcherDefault()
{

}

void XFDispatcherDefault::initialize()
{
	if (!_bInitialized)
	{
		_bInitialized = true;
		_pMutex = XFResourceFactory::getInstance()->createMutex();
		assert(_pMutex);
	}
}

void XFDispatcherDefault::start()
{
	assert(_pMutex);		// Call initialize() first
	_bExecuting = true;
}

void XFDispatcherDefault::stop()
{
	_bExecuting = false;
}

void XFDispatcherDefault::pushEvent(XFEvent * pEvent)
{
	assert(_bInitialized);      // Call initialize() first

	_pMutex->lock();
	{
#ifdef XF_TRACE_EVENT_PUSH_POP
	    Trace::out("Push event: 0x%x", pEvent);
#endif // XF_TRACE_EVENT_PUSH_POP
		_events.push(pEvent);
	}
	_pMutex->unlock();
}

void XFDispatcherDefault::scheduleTimeout(int timeoutId, int interval, interface::XFReactive * pReactive)
{
	// Forward timeout to the timeout manager
	XFTimeoutManager::getInstance()->scheduleTimeout(timeoutId, interval, pReactive);
}

void XFDispatcherDefault::unscheduleTimeout(int timeoutId, interface::XFReactive * pReactive)
{
	// Forward timeout to the timeout manager
	XFTimeoutManager::getInstance()->unscheduleTimeout(timeoutId, pReactive);
}

int XFDispatcherDefault::execute(const void * param /* = nullptr */)
{
	(void)param;	// Parameter not used at the method

	while(_bExecuting)
	{
		while (_events.empty() && _bExecuting)
		{
			continue;	// Wait until something to do
		}

		executeOnce();  // Dispatch next event
	}

	return 0;
}

int XFDispatcherDefault::executeOnce()
{
    if (!_events.empty() and _bExecuting)
    {
        const XFEvent * pEvent;

        _pMutex->lock();
        {
        	// Deque next event from queue
        	pEvent = _events.front(); _events.pop();
#ifdef XF_TRACE_EVENT_PUSH_POP
        	Trace::out("Pop event:  0x%x", pEvent);
#endif // XF_TRACE_EVENT_PUSH_POP
    	}
    	_pMutex->unlock();

        if (pEvent)
        {
            // Forward the event to the behavioral class
            dispatchEvent(pEvent);

            if (pEvent->getEventType() == XFEvent::Terminate)
            {
                // Exit the event loop
                _bExecuting = false;
            }

            if (pEvent->deleteAfterConsume())
            {
                // Remove the consumed event
                delete pEvent;
            }
        }
    }

    return _bExecuting;
}

void XFDispatcherDefault::dispatchEvent(const XFEvent * pEvent) const
{
	XFEventStatus eventStatus;

	eventStatus = pEvent->getBehavior()->process(pEvent);

	// Check if behavior should be deleted
	if (eventStatus == XFEventStatus::Terminate)
	{
		delete pEvent->getBehavior();
	}
}

#endif // USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION
