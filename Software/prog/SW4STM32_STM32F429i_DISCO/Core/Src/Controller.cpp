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

	signalValue = 0;
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

	//wait for adc
	while(!ADC3Flag || !ADC1Flag){
	}

	//get the chosen ball nbr by the user
	osEvent event = osMessageGet(ChosenBallQueueHandle,osWaitForever);

	//check if current signal and chosen ball are identical
	if(event.status == osStatus::osEventMessage){
		if(signalValue ==event.value.v){
			goodSignal = 1;
			//send adc value to the model
			//todo in percent//
			osMessagePut(ADCQueue1Handle,ADC1val*100/4096,NULL);
			osMessagePut(ADCQueue2Handle,ADC3val*100/4096,NULL);
		}
		else{
			goodSignal = 0;
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
			break;
		default:
			break;
	}
}

void Controller::readBits(uint8_t signalValue) {

	this->signalValue = signalValue;
	osThreadResume(controllerTaskHandle);
}
