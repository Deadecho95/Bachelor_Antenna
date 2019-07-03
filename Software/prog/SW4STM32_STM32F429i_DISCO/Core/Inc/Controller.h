/*
 * Controller.h
 *
 *  Created on: 27 juin 2019
 *      Author: chena
 */

#ifndef APPLICATION_USER_CORE_SRC_CONTROLLER_H_
#define APPLICATION_USER_CORE_SRC_CONTROLLER_H_

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
	* @brief read value of a bit of the received signal
	* @param bitNbr: the bit number
	* * @param bitValue: the value of the bit
	*/
	void readBits(uint8_t bitNbr);

private:
	std::array<bool, MAX_BIT_SIGNAL+CRC_SIGNAL+START_BIT> signalArray;
	uint8_t signalValue;
	bool goodSignal;
	uint32_t ADC3val;
	uint32_t ADC1val;
	bool ADC1Flag;
	bool ADC3Flag;
};

#endif /* APPLICATION_USER_CORE_SRC_CONTROLLER_H_ */
