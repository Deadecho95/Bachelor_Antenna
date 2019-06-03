
#include <config/xf-config.h>

#if (USE_XF_PORT_RTOS_KEIL_TIMEOUTMANAGER_IMPLEMENTATION != 0)

#include <assert.h>
#include "xf/interface/reactive.h"
#include "timeoutmanager.h"

interface::XFTimeoutManager * interface::XFTimeoutManager::getInstance()
{
    return XFTimeoutManagerPort::getInstance();
}

interface::XFTimeoutManager * XFTimeoutManagerPort::getInstance()
{
	static XFTimeoutManagerPort timeoutManager;
	return &timeoutManager;
}

XFTimeoutManagerPort::XFTimeoutManagerPort() :
	_osTimerId(0)
{

	_osTimerId = osTimerNew(&XFTimeoutManagerPort::timerCallback, osTimerPeriodic,this,NULL);
	assert(_osTimerId);     // You may need to enable timers in the FreeRTOS section of the STM32CubeMX project (USE_TIMERS = Enabled)
}

XFTimeoutManagerPort::~XFTimeoutManagerPort()
{
}

/*
 * Gets called every #_tickInterval interval.
 */
//static
void XFTimeoutManagerPort::timerCallback(void * argument)
{
	// Argument given is in fact a Timer_t * (see timers.h in FreeRTOS)
	// The argument we want is in pTimer->pvTimerID which is 8*4bytes
	// more down in the structure pointed by pTimer:
	uint32_t * pTimer = (uint32_t *) argument;
	XFTimeoutManagerPort * const pThis = (XFTimeoutManagerPort *)*(pTimer);

	pThis->tick();	// Call method handling timeouts
}

void XFTimeoutManagerPort::start()
{
	// Check tickInterval. Set default value if not set
	if (_tickInterval == 0)
	{
		_tickInterval = 10;
	}

	assert(_osTimerId);		// Check existence of timer
	osTimerStart(_osTimerId, _tickInterval);	// Start OS timer
}

void XFTimeoutManagerPort::scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive * pReactive)
{
	XFTimeout * pTimeout = new XFTimeout(timeoutId, interval, pReactive);

	if (pTimeout)
	{
		addTimeout(pTimeout);
	}
}

void XFTimeoutManagerPort::unscheduleTimeout(int32_t timeoutId, interface::XFReactive * pReactive)
{
	removeTimeouts(timeoutId, pReactive);
}

void XFTimeoutManagerPort::tick()
{
	int32_t intervalToSubtract = _tickInterval;

	while (!_timeouts.empty())
	{
		_mutex.lock();
		{
			XFTimeout * pFirstTimeout = _timeouts.front();

			// Subtract time elapsed
			pFirstTimeout->substractFromRelTicks(intervalToSubtract);

			// From now on set it to zero.
			intervalToSubtract = 0;

			// Check timeout timed out
			if (pFirstTimeout->getRelTicks() <= 0)
			{
				// Check remaining ticks can be given further
				if (_timeouts.size() > 1)
				{
					TimeoutList::iterator i = _timeouts.begin();

					// Add ticks overrun to next timeout
					i++;
					(*i)->substractFromRelTicks(pFirstTimeout->getRelTicks());
				}

				// Inject the timeout back to the behavioral class
				returnTimeout(pFirstTimeout);

				// Remove timeout
				_timeouts.pop_front();

				// Check if timeouts with same timeout value are present
				for (TimeoutList::iterator it = _timeouts.begin(); it != _timeouts.end(); /*Do not increment here!*/)
				{
					if ((*it)->getRelTicks() == 0)
					{
						returnTimeout(*it);			// Return them true
						it = _timeouts.erase(it);	// Remove timeout and adjust iterator to next element
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				_mutex.unlock();
				// Done. Exit while loop
				break;
			}
		}
		_mutex.unlock();
	}
}

void XFTimeoutManagerPort::addTimeout(XFTimeout * pNewTimeout)
{
	_mutex.lock();
	{
		if (!_timeouts.empty())
		{
			// Insert timeout before timeout(s) triggering later
			TimeoutList::iterator i = _timeouts.begin();

			unsigned int index = 0;

			// Find the right place to insert new timeout
			while (i != _timeouts.end() &&
				   (*i)->getRelTicks() < pNewTimeout->getRelTicks())
			{	// -> by: test4, test5
				pNewTimeout->substractFromRelTicks((*i)->getRelTicks());
				i++; index++;
			}

			if (i != _timeouts.end())
			{
				if ((*i)->getRelTicks() != pNewTimeout->getRelTicks())
				{	// -> by: test1, test4, test5
					// Timeout are going to timeout at different times

					// Insert new timeout before
					_timeouts.insert(i, pNewTimeout);

					// Remove time from following timeout
					(*i)->substractFromRelTicks(pNewTimeout->getRelTicks());

				}
				else
				{	// -> by: test1, test5
					const int32_t relTicks = (*i)->getRelTicks();
					// Timeouts timeout at the same time. Put
					// the new one behind the actual.
					i++;

					// Check if even more timeouts with the same timeout
					while(i != _timeouts.end() && (*i)->getRelTicks() == 0)
					{	// -> by: test5
						i++;
					}

					// Insert new timeout behind actual
					_timeouts.insert(i, pNewTimeout);
					// Remove time from actual timeout
					pNewTimeout->substractFromRelTicks(relTicks);
				}
			}
			else
			{	// -> by: test4, test5
				// Add timeout at the end of the list
				_timeouts.insert(_timeouts.end(), pNewTimeout);
			}
		}
		else
		{	// -> by: test1, test2, test3, test4, test5
			_timeouts.push_front(pNewTimeout);
		}
	}
	_mutex.unlock();
}

void XFTimeoutManagerPort::removeTimeouts(int32_t timeoutId, interface::XFReactive * pReactive)
{
	const XFTimeout timeout(timeoutId, 0, pReactive);
	XFTimeout * pTimeout;

	_mutex.lock();
	{
		for (TimeoutList::iterator i = _timeouts.begin();
			 i != _timeouts.end(); /*Do not increment here!*/)
		{
			pTimeout = *i;

			// Check if behavior and timeout id are equal
			if (*pTimeout == timeout)
			{
				TimeoutList::iterator next = i;

				// Check if remaining ticks can be given further
				if (++next != _timeouts.end())
				{
					// Add (remaining) ticks to next timeout in list
					(*next)->addToRelTicks(pTimeout->getRelTicks());
				}

				i = _timeouts.erase(i);
				// Iterator now points to the next element

				delete pTimeout;
			}
			else
			{
				i++;
			}
		}
	}
	_mutex.unlock();
}

void XFTimeoutManagerPort::returnTimeout(XFTimeout * pTimeout)
{
	pTimeout->getBehavior()->pushEvent(pTimeout);
}

#endif // USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_TIMEOUTMANAGER_IMPLEMENTATION
