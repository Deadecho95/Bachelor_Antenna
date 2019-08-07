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
extern osMessageQId stateQueueHandle;

extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac;
Controller::Controller() {
	// TODO Auto-generated constructor stub

	//init private variable
	for (int var = 0; var < MAX_BIT_SIGNAL; ++var) {
		signalArray[var] = 0;
	}

	signalValue = 0;
	ADC1Flag = 0;
	ADC3Flag = 0;
	ADC1val = 0;
	ADC3val = 0;
	mainState = state::menu;
	power = 0;
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

Controller* Controller::getInstance() {

	static Controller controller;

	return &controller;
}

void Controller::taskEntry() {

	//get state from gui
	osEvent event = osMessageGet(stateQueueHandle,0);


	//switch pattern
	if(event.status == osStatus::osEventMessage){
		mainState = state(event.value.v);
	}


	//check current state
	switch (mainState) {

		case state::menu:
			HAL_GPIO_WritePin(EN_DEMODULATOR_GPIO_Port,EN_DEMODULATOR_Pin,GPIO_PinState::GPIO_PIN_RESET);
			osThreadSuspend(controllerTaskHandle);
			break;

		case state::calibrate:

			HAL_GPIO_WritePin(EN_DEMODULATOR_GPIO_Port,EN_DEMODULATOR_Pin,GPIO_PinState::GPIO_PIN_SET);
			osDelay(2);	//wait the set of the fin

			HAL_ADC_Start_IT(&hadc1);

			//wait for adc
			while(!ADC1Flag){
			}
			ADC3Flag = ADC1Flag = 0;

			HAL_DAC_SetValue(&hdac,DAC_CHANNEL_2,DAC_ALIGN_12B_R,ADC1val+DAC_INCREMENT);

			osMessagePut(ADCQueue1Handle,ADC1val*ADC_MIN_VALUE,0);

			mainState = state::menu;
			break;

		case state::reception:

			//wait for adc
			if(!ADC3Flag || !ADC1Flag){
				osThreadSuspend(controllerTaskHandle);
			}

			//reset flag
			ADC3Flag = ADC1Flag = 0;


			//get the chosen ball nbr by the user
			 event = osMessageGet(ChosenBallQueueHandle,osWaitForever);

			//check if current signal and chosen ball are identical
			if(event.status == osStatus::osEventMessage){
				if(signalValue ==event.value.v){
					//send adc value to the model
					//todo in percent//
					osMessagePut(ADCQueue1Handle,ADC1val*ADC_MIN_VALUE,0);
					osMessagePut(ADCQueue2Handle,ADC3val*ADC_MIN_VALUE,0);
				}
				else{
					osMessagePut(ADCQueue1Handle,0,0);
					osMessagePut(ADCQueue2Handle,0,0);
				}
			}
			signalValue = -1;
			osThreadSuspend(controllerTaskHandle);
			break;

			case state::startReception:
				HAL_GPIO_WritePin(EN_DEMODULATOR_GPIO_Port,EN_DEMODULATOR_Pin,GPIO_PinState::GPIO_PIN_SET);
				mainState = state::reception;
				osThreadSuspend(controllerTaskHandle);
				break;
		default:
			break;
	}

}

void Controller::setADC1Value(uint32_t value) {

	//send adc value the the gui
	ADC1val = value;
	ADC1Flag = 1;

	//if two conversion down, wake up thread
	if(ADC1Flag && ADC3Flag){
		osThreadResume(controllerTaskHandle);
	}
}

void Controller::setADC3Value(uint32_t value) {

	//send adc value the the gui
	ADC3val = value;
	ADC3Flag = 1;

	//if two conversion down, wake up thread
	if(ADC1Flag && ADC3Flag){
		osThreadResume(controllerTaskHandle);
	}
}

void Controller::IsInterrupt(uint8_t value) {

	//send the pressed button the the gui
	switch (value) {
		case interrupt::BLUE_BUTTONpress:
			osMessagePut(InterruptQueueHandle,interrupt::BLUE_BUTTONpress,0);
			break;

		case interrupt::BUTTON1press:
			osMessagePut(InterruptQueueHandle,interrupt::BUTTON1press,0);
			break;

		case interrupt::BUTTON2press:
			osMessagePut(InterruptQueueHandle,interrupt::BUTTON2press,0);
			break;

		case interrupt::RECEIVED_SIGNAL:
			osMessagePut(InterruptQueueHandle,interrupt::RECEIVED_SIGNAL,0);
			break;
		default:
			break;
	}
}

void Controller::readBits(uint8_t signalValue) {

	this->signalValue = signalValue;
	osThreadResume(controllerTaskHandle);
}

State Controller::getState() {
	return mainState;
}
