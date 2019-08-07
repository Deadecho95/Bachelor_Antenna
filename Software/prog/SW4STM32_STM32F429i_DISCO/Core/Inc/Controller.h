/*
 * Controller.h
 *
 *  Created on: 27 juin 2019
 *      Author: chena
 */

#ifndef APPLICATION_USER_CORE_SRC_CONTROLLER_H_
#define APPLICATION_USER_CORE_SRC_CONTROLLER_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "cmsis_os.h"
#include "config.h"
#include <array>
#include <math.h>

/**
* @brief Control the interrupts and the signal logic
*/
class Controller {
public:


	Controller();
	virtual ~Controller();

	/**
	* @brief return the singleton Controller
	* @retval the Controller
	*/
	static Controller* getInstance();

	/**
	* @brief called task for the thread
	*/
	void taskEntry();

	/**
	* @brief set ADC1 value
	* @param value of the ADC
	*/
	void setADC1Value(uint32_t value);

	/**
	* @brief set ADC3 value
	* @param value of the ADC
	*/
	void setADC3Value(uint32_t value);

	/**
	* @brief a button is pressed
	* @param value: the pressed button
	*/
	void IsInterrupt(uint8_t value);

	/**
	* @brief read value of the UART
	* @param value: value of the Byte
	*/
	void readBits(uint8_t value);

	/**
	* @brief return the current state
	* @return the current state
	*/
	State getState();

private:

	std::array<bool, MAX_BIT_SIGNAL> signalArray;//array to receive the UART values
	int8_t signalValue; //uart value

	//adc values
	uint32_t ADC3val;
	uint32_t ADC1val;

	//adc flag when a new adc value is arrived
	bool ADC1Flag;
	bool ADC3Flag;

	State mainState;//state for the controller

	double power;//power to send to the gui (power is referenced with mV)

};

#endif /* APPLICATION_USER_CORE_SRC_CONTROLLER_H_ */
