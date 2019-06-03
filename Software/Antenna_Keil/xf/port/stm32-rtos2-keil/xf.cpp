#include <config/xf-config.h>

#if (PORT_RTOS_KEIL != 0)

#include <assert.h>
#include "cmsis_os2.h" 

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"

using interface::XFTimeoutManager;
using interface::XFResourceFactory;

bool XF::_bInitialized = false;

void XF_initialize(int timeInterval)
{
    XF::initialize(timeInterval);
}

void XF_exec()
{
    XF::exec();
}

void XF_execOnce()
{
    XF::execOnce();
}

void XF::initialize(int timeInterval /* = 10 */, int argc /* = 0 */, char * argv[] /* = nullptr */)
{
    if (!_bInitialized)
    {
		//osKernelInitialize();

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

	return 0;
}

int XF::execOnce()
{
    assert(false);  // Should not be called within the FreeRTOS based port! Call XF_exec() instead!
}

interface::XFDispatcher * XF::getDefaultDispatcher()
{
	return XFResourceFactory::getInstance()->getDefaultDispatcher();
}

#endif // PORT_STM32CUBE_CMSIS_FREERTOS
