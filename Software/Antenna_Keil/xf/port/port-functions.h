#ifndef XF_PORT_FUNCTIONS_H
#define XF_PORT_FUNCTIONS_H

#include <stdint.h>

/**
 * Following functions need to have "C" signature as they can be
 * called in C (and C++).
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief C function allowing to start the timer needed by the TimeoutManager instance.
 */
void XF_startTimeoutManagerTimer(uint32_t tickInterval);

/**
 * @brief Must be called regularly in a timer ISR or software timer callback.
 *
 * The XF_tick() function must be called with the same interval given to the
 * TimeoutManager (tickInterval).
 */
void XF_tick();

/**
 * C function returning the tick interval in milliseconds with which the XF_tick()
 * function should be called. This is the parameter given to the XF::init() method
 * and may be different for each project.
 */
int32_t XF_tickIntervalInMilliseconds();

#ifdef __cplusplus
}
#endif
#endif // XF_PORT_FUNCTIONS_H
