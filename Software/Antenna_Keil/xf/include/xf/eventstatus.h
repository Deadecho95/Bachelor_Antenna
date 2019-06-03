#ifndef XF_EVENTSTATUS_H
#define XF_EVENTSTATUS_H

/** @ingroup xf_core
 *  @{
 */

/**
 * @brief Event status returned after event processing.
 *
 * The XFEventStatus is used after consumption of an event. It gives an
 * information on how the event was consument and how the framework should
 * react.
 */
class XFEventStatus
{
public:
	/**
	 * Status values about the event processed.
	 *
	 * \see XFBehavior::process
	 */
	typedef enum
	{
		Unknown			= 0,
		Consumed		= 0x0001,		///< Event consumed
		NotConsumed		= 0x0002,		///< Event not consumed
		RegionFinished  = 0x0004,		///< Composite state machine finished
		Terminate		= 0x0008		///< Terminate state machine
	} eEventStatus;

	/**
	 * Constructor
	 *
	 * \param eventStatus Initial value of the event status.
	 */
    XFEventStatus(eEventStatus eventStatus = Unknown) : _status(eventStatus) {}

	/**
	 * Checks if both variables contain the same event status.
	 */
    bool operator == (const XFEventStatus::eEventStatus & eventStatus) const
	{
		return (this->_status == eventStatus);
	}

    /**
     * @brief OR assignment.
     *
     * OR's the right event status with the left event status.
     */
    void operator |= (const XFEventStatus & eventStatus)
	{
		unsigned int s1 = _status, s2 = eventStatus._status;
		s1 |= s2;
		_status = (eEventStatus)s1;
	}

    /**
     * @brief Checks if the given event status (r-value) is present in the actual (l-value).
     */
	bool is(const eEventStatus eventStatus) const
	{
		unsigned int mask = (unsigned int)eventStatus;
		return ((((unsigned int)_status) & mask) == mask);
	}

public:
	eEventStatus _status;		///< Attribute containing the status of the event.
};

typedef XFEventStatus::eEventStatus eEventStatus;

/** @} */ // end of xf_core group
#endif // XF_EVENTSTATUS_H
