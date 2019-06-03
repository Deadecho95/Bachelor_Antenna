#ifndef XF_PORT_IDF_QT_THREAD_H
#define XF_PORT_IDF_QT_THREAD_H

#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION != 0)

#include <QThread>
#include <stdint.h>
#include "xf/interface/thread.h"

/** @ingroup port_idf_qt
 *  @{
 */

/**
 * @brief Thread implementation for the IDF Qt port
 */
class XFThreadPort : public QThread,
                     public interface::XFThread
{
    friend class XFResourceFactoryPort;

    // interface::Thread interface implementation
public:
    virtual void start();
    virtual void suspend();
    virtual void stop();

    virtual void setPriority(XFThreadPriority priority);
    virtual XFThreadPriority getPriority() const;

    virtual void delay(uint32_t milliseconds);

protected:
    /**
     * @brief Protected XFThreadPort constructor
     * @param pProvider Instance providing the method to be executed by the thread.
     * @param entryMethod Method to be executed by the Thread (usually containing a infinite loop).
     * @param threadName Name of the thread.
     * @param stackSize Stack size of the thread.
     *
     * Constructor is protected because only the XFResourceFactory interface
     * based class (XFResourceFactoryPort) is allowed to created threads.
     */
    XFThreadPort(interface::XFThreadEntryPointProvider * pProvider,
                 interface::XFThread::EntryMethodBody entryMethod,
                 const char * threadName,
                 const uint32_t stackSize = 0);

    // QThread interface implementation
protected:
    virtual void run();                                                 ///< Override of the QThread run method.

protected:
    interface::XFThreadEntryPointProvider * _pEntryMethodProvider;      ///< Pointer to object providing the entry method.
    interface::XFThread::EntryMethodBody _entryMethod;                  ///< Entry method to be called/executed by the thread.
};

/** @} */ // end of port_idf_qt group
#endif // USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION
#endif // XF_PORT_IDF_QT_THREAD_H
