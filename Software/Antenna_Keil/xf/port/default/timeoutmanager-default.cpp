
#include <config/xf-config.h>

#if (USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "xf/interface/reactive.h"
#include "xf/interface/resourcefactory.h"
#include "port-functions.h"
#include "timeoutmanager-default.h"

using interface::XFResourceFactory;

interface::XFTimeoutManager * interface::XFTimeoutManager::getInstance()
{
	return XFTimeoutManagerDefault::getInstance();
}

interface::XFTimeoutManager * XFTimeoutManagerDefault::getInstance()
{
	static XFTimeoutManagerDefault timeoutManager;
	return &timeoutManager;
}

XFTimeoutManagerDefault::XFTimeoutManagerDefault() :
	_pMutex(nullptr)
{
    _pMutex = XFResourceFactory::getInstance()->createMutex();
	assert(_pMutex);
}

XFTimeoutManagerDefault::~XFTimeoutManagerDefault()
{
}

void XFTimeoutManagerDefault::start()
{
	// Check tickInterval. Set default value if not set
	if (_tickInterval == 0)
	{
		_tickInterval = 10;
	}

	XF_startTimeoutManagerTimer(_tickInterval);
}

void XFTimeoutManagerDefault::scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive * pReactive)
{
	XFTimeout * pTimeout = new XFTimeout(timeoutId, interval, pReactive);

	if (pTimeout)
	{
		addTimeout(pTimeout);
	}
}

void XFTimeoutManagerDefault::unscheduleTimeout(int32_t timeoutId, interface::XFReactive * pReactive)
{
	removeTimeouts(timeoutId, pReactive);
}

void XFTimeoutManagerDefault::tick()
{
	assert(_tickInterval);      // Did you call start()?!
	int32_t intervalToSubtract = _tickInterval;

	while (!_timeouts.empty())
	{
		_pMutex->lock();
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
				_pMutex->unlock();
				// Done. Exit while loop
				break;
			}
		}
		_pMutex->unlock();
	}
}

void XFTimeoutManagerDefault::addTimeout(XFTimeout * pNewTimeout)
{
	if (!_timeouts.empty())
	{
		_pMutex->lock();
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
		_pMutex->unlock();
	}
	else
	{	// -> by: test1, test2, test3, test4, test5
		_timeouts.push_front(pNewTimeout);
	}
}

void XFTimeoutManagerDefault::removeTimeouts(int32_t timeoutId, interface::XFReactive * pReactive)
{
	const XFTimeout timeout(timeoutId, 0, pReactive);
	XFTimeout * pTimeout;

	_pMutex->lock();
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
	_pMutex->unlock();
}

void XFTimeoutManagerDefault::returnTimeout(XFTimeout * pTimeout)
{
	pTimeout->getBehavior()->pushEvent(pTimeout);
}

#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION
