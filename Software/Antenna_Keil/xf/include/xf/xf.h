#ifndef XF_XF_H
#define XF_XF_H

#include "config/xf-config.h"

//
// What is seen only by the C++ compiler
//
#ifdef __cplusplus

#include "xf/interface/dispatcher.h"

/** \mainpage PTR Execution Framework Documentation
 *
 * \section sec_xf_intro Introduction
 *
 * This library implements an e<b>X</b>ecution <b>F</b>ramework (XF) to drive finite
 * state machines. Using this framework, it is possible to drive multiple state machines
 * in a concurrent manner (pseudo-parallel) without having an operating system.
 *
 * The XF defines an interface which gives the ability to reimplement parts of the XF to
 * make changes to an other target/platform. It is also possible to let the XF run with an RTOS.
 * This gives the possibility to run state machines in a OS like concurrent manner with
 * threads provided by the underlying RTOS.
 *
 * \section sec_xf_comp XF Component Diagram
 * The XF is split into two parts. One part is the XF core containing classes which
 * never change across platforms. The other part is the XF port containing classes
 * adjusted for a specific platform:
 *
 *  \image html comp-xf.png "Component Class Diagram"
 *
 * The XF core together with a port forms a complete XF which can be integrated into
 * a software project.
 *
 * \section sec_xf_cmd XF Class Diagram
 *
 * Following class diagram shows the basic relations between the most important classes
 * in the PTR XF. It shall give you a basic understanding about the relations between
 * these classes:
 *
 * \image html cmd-xf.png "XF Class Diagram"
 *
 * \section sec_xf_start Starting Point
 *
 * A good point to jump into the definitions of the classes is the `#XF` class. Other classes
 * of interest are `interface::XFTimeoutManager`, `interface::XFDispatcher` and `interface::XFReactive`.
 *
 * \section sec_xf_external_links Links to related Documentation
 * \if DOC_WITH_TESTBENCH
 * - <a href="../../../../../test-bench/doxygen/output/html/index.html">Test Bench Documentation</a>
 * \endif
 * - <a href="../../../../../src/mdw/trace/doxygen/output/html/index.html">Trace Documentation</a>
 *
 * \if DOC_WITH_RELEASE_HISTORY
 * \section sec_xf_releases XF Releases
 * \subsection xf_v_3_2 XF Version: 3.2 (2018-09)
 * - sth: Updated XF interfaces.
 * - sth: Added IDF_STM32CUBE, STM32CUBE_CMSIS_FREERTOS and ACTIVE_QT ports.
 * - sth: Removed old ports IDF_STM32F4 and CMSIS_RTOS_FREERTOS.
 * \subsection xf_v_3_1 XF Version: 3.1 (2017-11)
 * - sth: Fixed bug in removeTimeouts() method of XFTimeoutManager. Thanks to Gregory Dumoulin.
 * \subsection xf_v_3_0 XF Version: 3.0 (2017-10)
 * - sth: The new XF is providing interfaces to support other OS's.
 * - sth: Changed XF interfaces. Porting older applications to new XF need some adjustments.
 * - sth: Added 'port' folder to allow extensions to other platforms.
 * - sth: Added IDF_STM32F4, CMSIS_RTOS_FREERTOS and IDF_QT ports.
 * \subsection xf_v_2_1 XF Version: 2.1 (2015-03-02)
 * - sth: XFTimoutManager now returns timeouts with same value correctly.
 * \subsection xf_v_2_0 XF Version: 2.0 (2014-04-28)
 * - sth: Changed way how XFTimeoutManager handles timeouts which timeout at the same time.
 *        Now new timeouts get behind the timeouts with the same (timeout) time.
 * \subsection xf_v_1_0 XF Version: 1.0 (2014-04-24)
 * - sth: Renamed class XFEvent to XFCustomEvent
 * - sth: Renamed IXFEvent to XFEvent (because it was never a real interface)
 * \subsection xf_v_0_5 XF Version: 0.5 (2013-12-09)
 * - sth: Now properly stopping and terminating MainThreadExec instance
 * - sth: Added new literal to XFEventStatus to handle composite states
 * \subsection xf_v_0_4 XF Version: 0.4 (2013-12-05)
 * - sth: Added scheduleTimeout and unscheduleTimeout to XFBehavior class (helper operations)
 * \subsection xf_v_0_3 XF Version: 0.3 (2013-09-19)
 * - sth: Added handling for static events (IXFEvent::deleteAfterConsume())
 * \subsection xf_v_0_2 XF Version: 0.2 (2011-08-14)
 * - sth: Fixed bug in XFTimeoutManager::addTimeout method
 * \subsection xf_v_0_1 XF Version: 0.1 (2010-11-26)
 * - sth: First release
 * \endif
 */

/** @ingroup xf_core
 *  @{
 */

/**
 * @brief Static class grouping the basic methods for the XF together.
 */
class XF
{
public:
    /**
     * Initializes the e<b>X</b>ecution <b>F</b>ramework (XF). Call
     * this method prior to initialize the other objects of the system.
     *
     * @param timeInterval The interval in milliseconds with which the TimeoutManager should run.
     * @param argc Optional parameter to pass application argument number to XF.
     * @param argv Optional parameter to pass application arguments to XF.
     */
    static void initialize(int timeInterval = 10, int argc = 0, char * argv[] = nullptr);

    /**
     * Starts execution of the framework. This
     * results in processing the events in main loop.
     *
     * This method is blocking.
     */
    static int exec();

    /**
     * Executes once the dispatcher. To be called regularly in a while loop.
     *
     * This method is non-blocking.
     */
    static int execOnce();

    static interface::XFDispatcher * getDefaultDispatcher();	///< Returns pointer the default event dispatcher.

protected:
    static bool _bInitialized;			///< Changes from false to true after calling method initialize(int). Used to handle multiple calls to init(int).
};

#endif  // __cplusplus

//
// What is seen by the C and C++ compiler
//
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void XF_initialize(int timeInterval);       ///< Initializes XF within C code
void XF_exec();                             ///< Calls XF execution in C code (blocking call)
void XF_execOnce();                         ///< Calls XF execution in C code (non-blocking call)

#ifdef __cplusplus
}
#endif // __cplusplus

/** @} */ // end of xf_core group
#endif // XF_XF_H
