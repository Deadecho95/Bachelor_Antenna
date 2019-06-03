#ifndef XF_PORT_STM32CUBE_CMSIS_FREERTOS_TIMEOUTMANAGER_H
#define XF_PORT_STM32CUBE_CMSIS_FREERTOS_TIMEOUTMANAGER_H

#include <list>
#include <config/xf-config.h>

#if (USE_XF_PORT_RTOS_KEIL_TIMEOUTMANAGER_IMPLEMENTATION != 0)

#include "cmsis_os2.h" 
#include "xf/interface/timeoutmanager.h"
#include "xf/timeout.h"
#include "mutex.h"

/**
 * Default implementation of the XF TimeoutManager
 */
class XFTimeoutManagerPort : public interface::XFTimeoutManager
{
	friend interface::XFTimeoutManager * interface::XFTimeoutManager::getInstance();
public:
	virtual ~XFTimeoutManagerPort();
	
	static interface::XFTimeoutManager * getInstance();

	virtual void start();
	virtual void scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive * pReactive);
	virtual void unscheduleTimeout(int32_t timeoutId, interface::XFReactive * pReactive);
	virtual void tick();

protected:
	XFTimeoutManagerPort();
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

	static void timerCallback(void * argument);	///< Callback "function" needed by OS timer.

protected:
	typedef std::list<XFTimeout *> TimeoutList;		///< Type used for the _timeouts property.
	
	TimeoutList _timeouts;							///< Container holding timeouts to manage.


	osTimerId_t _osTimerId;							///< OS timer used to handle timeouts.

	XFMutexPort _mutex;								///< Mutex to protect the timeout list.
};

#endif // USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_TIMEOUTMANAGER_IMPLEMENTATION
#endif // XF_PORT_STM32CUBE_CMSIS_FREERTOS_TIMEOUTMANAGER_H
