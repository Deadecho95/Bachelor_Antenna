#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION != 0)

#include <assert.h>
#include <QtGlobal>
#include <QMutexLocker>
#include "eventqueue.h"

XFEventQueuePort::XFEventQueuePort() :
    _mutex(QMutex::NonRecursive)
{
}

XFEventQueuePort::~XFEventQueuePort()
{
    _newEvents.wakeAll();
}

bool XFEventQueuePort::empty() const
{
    return _queue.isEmpty();
}

bool XFEventQueuePort::push(const XFEvent * pEvent)
{
    QMutexLocker locker(&_mutex);
    _queue.enqueue(pEvent);
    // Tell waiting thread(s) there is again an event present
    _newEvents.wakeAll();
    return true;
}

const XFEvent * XFEventQueuePort::front()
{
    return _queue.front();
}

void XFEventQueuePort::pop()
{
    QMutexLocker locker(&_mutex);
    _queue.dequeue();
}

bool XFEventQueuePort::pend()
{
    QMutexLocker locker(&_mutex);
    // Wait for new events. Mutex needs to be in lock-state
    // prior to call wait()!
    _newEvents.wait(&_mutex);

    return !_queue.isEmpty();
}

#endif // USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION
