#include <config/xf-config.h>

#if (USE_XF_PORT_RTOS_KEIL_EVENT_QUEUE_IMPLEMENTATION != 0)

#include <assert.h>
#include "eventqueue.h"

XFEventQueueDefault::XFEventQueueDefault()
{

}

XFEventQueueDefault::~XFEventQueueDefault()
{

}

bool XFEventQueueDefault::empty() const
{
    return _queue.empty();
}

bool XFEventQueueDefault::push(const XFEvent * pEvent)
{
    _queue.push(pEvent);

    return true;
}

const XFEvent * XFEventQueueDefault::front()
{
    return _queue.front();
}

void XFEventQueueDefault::pop()
{
    _queue.pop();
}

bool XFEventQueueDefault::pend()
{
    // Method cannot be used in an IDF! Waiting within
    // this method would block the whole XF
    return false;
}

#endif // USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_EVENT_QUEUE_IMPLEMENTATION
