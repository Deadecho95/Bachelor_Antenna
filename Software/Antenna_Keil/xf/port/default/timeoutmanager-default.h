#ifndef XF_TIMEOUTMANAGER_DEFAULT_H
#define XF_TIMEOUTMANAGER_DEFAULT_H

#include <list>
#include <config/xf-config.h>

#if (USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/timeout.h"
#include "xf/interface/mutex.h"

/** @ingroup port_default
 *  @{
 */

/**
 * @brief Default implementation of the XF TimeoutManager
 */
class XFTimeoutManagerDefault : public interface::XFTimeoutManager
{
    friend interface::XFTimeoutManager * interface::XFTimeoutManager::getInstance();
public:
	virtual ~XFTimeoutManagerDefault();
	
    static interface::XFTimeoutManager * getInstance();     ///< Returns a pointer to the single instance of the class.

	virtual void start();
    virtual void scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive * pReactive);
    virtual void unscheduleTimeout(int32_t timeoutId, interface::XFReactive * pReactive);
	virtual void tick();

protected:
	XFTimeoutManagerDefault();
	virtual void addTimeout(XFTimeout * pNewTimeout);	///< Adds the timeout to #_timeouts.
	
	/**
	 * Removes all timeouts corresponding the given parameters.
	 */
    virtual void removeTimeouts(int32_t timeoutId, interface::XFReactive * pReactive);
	
	/**
	 * Returns the timeout back to the queue of the thread executing
	 * the behavioral instance.
	 */
	void returnTimeout(XFTimeout * pTimeout);	///< Returns timeout back to behavioral class.

protected:
	typedef std::list<XFTimeout *> TimeoutList;		///< Type used for the _timeouts property.
	
	TimeoutList _timeouts;							///< Container holding timeouts to manage.

	interface::XFMutex * _pMutex;					///< Mutex to protect access to TimeoutList.
};

/** @} */ // end of port_default group
#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION
#endif // XF_TIMEOUTMANAGER_DEFAULT_H
