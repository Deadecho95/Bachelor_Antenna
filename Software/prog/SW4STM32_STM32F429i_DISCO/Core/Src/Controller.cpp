/*
 * Controller.cpp
 *
 *  Created on: 27 juin 2019
 *      Author: chena
 */

#include "Controller.h"

extern osMessageQId ADCQueue1Handle;
extern osMessageQId ADCQueue2Handle;
extern osMessageQId InterruptQueueHandle;
extern osThreadId controllerTaskHandle;
extern osMessageQId ChosenBallQueueHandle;

Controller::Controller() {
	// TODO Auto-generated constructor stub

	//init private variable
	for (int var = 0; var < MAX_BIT_SIGNAL; ++var) {
		signalArray[var] = 0;
	}

	signalReceived = 0;
	goodSignal = 0;
	ADC1Flag = 0;
	ADC3Flag = 0;
	ADC1val = 0;
	ADC3val = 0;
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

Controller* Controller::getInstance() {

	static Controller controller;

	return &controller;
}

void Controller::taskEntry() {

	uint16_t result = 0;
	uint8_t crc = 0;
	uint8_t received_crc = 0;

	// 2^x * bit --> signal binary to integer
	for (int var = 0; var < MAX_BIT_SIGNAL; ++var) {
		// MAX_BIT_SIGNAL+2-var --> +2 because the start bit
		result = result+pow(2,MAX_BIT_SIGNAL-1-var)*signalArray[MAX_BIT_SIGNAL+START_BIT-var];
		crc = crc + signalArray[var+2];
	}

	//crc binary to integer
	for (int var = 0; var < CRC_SIGNAL; ++var) {
		received_crc = received_crc+pow(2,CRC_SIGNAL-1-var)*signalArray[CRC_SIGNAL+MAX_BIT_SIGNAL+START_BIT-var];
	}

	//check if crc ok
	if(crc == received_crc){
		signalReceived = result;

		//wait for adc
		while(!ADC3Flag || !ADC1Flag){
		}

		//get the chosen ball nbr by the user
		osEvent event = osMessageGet(ChosenBallQueueHandle,osWaitForever);

		//check if current signal and chosen ball are identical
		if(event.status == osStatus::osEventMessage){
			if(signalReceived ==event.value.v){
				goodSignal = 1;
				//send adc value to the model
				//todo in percent//
				osMessagePut(ADCQueue1Handle,ADC1val,NULL);
				osMessagePut(ADCQueue2Handle,ADC3val,NULL);
			}
			else{
				goodSignal = 0;
			}
		}
	}
	osThreadSuspend(controllerTaskHandle);
}

void Controller::setADC1Value(uint32_t value) {

	//send adc value the the gui
	ADC1val = value;
	ADC1Flag = 1;
}

void Controller::setADC3Value(uint32_t value) {

	//send adc value the the gui
	ADC3val = value;
	ADC3Flag = 1;
}

void Controller::IsInterrupt(uint8_t value) {

	//send the pressed button the the gui
	switch (value) {
		case interrupt::BLUE_BUTTONpress:
			osMessagePut(InterruptQueueHandle,interrupt::BLUE_BUTTONpress,NULL);
			break;

		case interrupt::BUTTON1press:
			osMessagePut(InterruptQueueHandle,interrupt::BUTTON1press,NULL);
			break;

		case interrupt::BUTTON2press:
			osMessagePut(InterruptQueueHandle,interrupt::BUTTON2press,NULL);
			break;

		case interrupt::RECEIVED_SIGNAL:
			osMessagePut(InterruptQueueHandle,interrupt::RECEIVED_SIGNAL,NULL);
			osThreadResume(controllerTaskHandle);
			break;
		default:
			break;
	}
}

void Controller::readBits(uint8_t bitNbr, bool bitValue) {

	signalArray[bitNbr] = bitValue;
	if(bitNbr == MAX_BIT_SIGNAL){
		osThreadResume(controllerTaskHandle);
	}
}
