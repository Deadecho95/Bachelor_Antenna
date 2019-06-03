#ifndef XF_PORT_IDF_QT_MUTEX_H
#define XF_PORT_IDF_QT_MUTEX_H

#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION != 0)

#include <stdint.h>
#include <QMutex>
#include "xf/interface/mutex.h"

/** @ingroup port_idf_qt
 *  @{
 */

/**
 * @brief XFMutexPort implementation for the IDF Qt port.
 */
class XFMutexPort : public interface::XFMutex
{
public:
	XFMutexPort();
	virtual ~XFMutexPort();

	virtual void lock();
	virtual void unlock();

	virtual bool tryLock(int32_t timeout = 0);

protected:
    QMutex _mutex;              ///< The real mutex.
};

/** @} */ // end of port_idf_qt group
#endif // USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION
#endif // XF_PORT_IDF_QT_MUTEX_H
