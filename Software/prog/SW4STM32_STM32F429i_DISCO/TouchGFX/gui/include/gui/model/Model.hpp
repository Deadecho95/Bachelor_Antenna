#ifndef MODEL_HPP
#define MODEL_HPP

#include "config.h"
#include "cmsis_os.h"
#include "stdint.h"

class ModelListener;

/**
 * The Model class defines the data model in the model-view-presenter paradigm.
 * The Model is a singular object used across all presenters. The currently active
 * presenter will have a pointer to the Model through deriving from ModelListener.
 *
 * The Model will typically contain UI state information that must be kept alive
 * through screen transitions. It also usually provides the interface to the rest
 * of the system (the backend). As such, the Model can receive events and data from
 * the backend and inform the current presenter of such events through the modelListener
 * pointer, which is automatically configured to point to the current presenter.
 * Conversely, the current presenter can trigger events in the backend through the Model.
 */
class Model
{
public:
    Model();

    /**
     * Sets the modelListener to point to the currently active presenter. Called automatically
     * when switching screen.
     */
    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    /**
     * This function will be called automatically every frame. Can be used to e.g. sample hardware
     * peripherals or read events from the surrounding system and inject events to the GUI through
     * the ModelListener interface.
     */
    void tick();

    /**
      * @brief set the chosen ball nbr
      * @param ballNbr : the number of chosen ball
      * @retval None
      */
    void setBallNbr(uint16_t ballNbr);

    /**
      * @brief get the chosen ball nbr
      * @param None
      * @retval the number of chosen ball
      */
    uint16_t getBallNbr();

    /**
      * @brief set the LPDA power
      * @param value : the power of the antenna
      * @retval None
      */
    void setPower(uint16_t value);

    /**
      * @brief get the LPDA power
      * @param None
      * @retval the power of the antenna
      */
    uint16_t getPower();

    /**
      * @brief set the LOOP power
      * @param value : the power of the antenna
      * @retval None
      */
    void setPosition(uint16_t value);

    /**
      * @brief get the LOOP power
      * @param None
      * @retval the power of the antenna
      */
    uint16_t getPosition();

    /**
      * @brief a new id arrived
      * @param None
      * @retval None
      */
    void newSignal();

    /**
      * @brief enable the calibration
      * @param None
      * @retval None
      */
    void activateCalibration();

    /**
      * @brief change the state of the controller sm
      * @param state : the state to change
      * @retval None
      */
    void changeState(state);

    /**
      * @brief set the minimum power when no ball emit
      * @param value : the power of the antenna
      * @retval None
      */
    void setMinPower(uint16_t value);

    /**
      * @brief get the minimum power when no ball emit
      * @param None
      * @retval the minimum power of the antenna
      */
    int16_t getMinPower();

protected:
    /**
     * Pointer to the currently active presenter.
     */
    ModelListener* modelListener;
	uint16_t ballNbr;
	uint16_t power;
	uint16_t minPower;
	uint16_t position;

	uint16_t noSignal;
};

#endif /* MODEL_HPP */
