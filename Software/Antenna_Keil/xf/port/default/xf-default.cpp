#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DEFAULT_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"

using interface::XFResourceFactory;
using interface::XFTimeoutManager;

bool XF::_bInitialized = false;

void XF_initialize(int timeInterval)
{
    XF::initialize(timeInterval);
}

void XF_exec()
{
    XF::exec();
}

void XF_execOnce(
{
    XF::execOnce();
}

void XF::initialize(int timeInterval /* = 10 */, int argc /* = 0 */, char * argv[] /* = nullptr */)
{
    if (!_bInitialized)
    {
        // Create and initialize TimeoutManager
        XFTimeoutManager::getInstance()->initialize(timeInterval);

        // Initialize defaut dispatcher
        getDefaultDispatcher()->initialize();

        _bInitialized = true;
    }
}

int XF::exec()
{
	// Start timeout manager
	XFTimeoutManager::getInstance()->start();

	// Start default dispatcher
	getDefaultDispatcher()->start();

	// In case default dispatcher does not have a thread executing it,
	// call it with this thread
	if (!getDefaultDispatcher()->isActive())
	{
		getDefaultDispatcher()->execute();
	}
    return 0;
}

int XF::execOnce()
{
	static bool usingExecOnce = false;

	if (!usingExecOnce)
	{
		usingExecOnce = true;

		// Start timeout manager
		XFTimeoutManager::getInstance()->start();

		// It makes no sense to call execOnce() with
		// an active default dispatcher!
		assert(!getDefaultDispatcher()->isActive());
		// Default dispatcher needs to be started explicitly
		getDefaultDispatcher()->start();
	}

    // Execute once the default dispatcher
    return getDefaultDispatcher()->executeOnce();
}

interface::XFDispatcher * XF::getDefaultDispatcher()
{
    return XFResourceFactory::getInstance()->getDefaultDispatcher();
}

#endif // USE_XF_DEFAULT_IMPLEMENTATION
