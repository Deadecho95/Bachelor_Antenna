/*
 * isrs.cpp
 *
 *  Created on: 10 avr. 2019
 *      Author: chena
 */

#include "stm32f4xx_hal.h"
#include "config.h"
#include "main.h"
#include "Controller.h"
#include "cmsis_os.h"


extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc3;
extern uint8_t aRxBuffer[USART_BUFFER_SIZE];
extern UART_HandleTypeDef huart2;
extern osTimerId reboundTimerHandle;
extern TIM_HandleTypeDef htim2;
extern bool buttonsActive;

/**
* @brief Callback when an ADC completes a conversion
*/
extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{

	if(hadc == &hadc1){
		Controller::getInstance()->setADC1Value(HAL_ADC_GetValue(hadc));
	}
	if(hadc == &hadc3){
		Controller::getInstance()->setADC3Value(HAL_ADC_GetValue(hadc));
	}

}

/**
* @brief Callback when an there is an interrupt
*/
extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  switch (GPIO_Pin) {
	case BUTTON1_Pin:
		if(buttonsActive){
			 Controller::getInstance()->IsInterrupt(interrupt::BUTTON1press);
			 osTimerStart(reboundTimerHandle,50);
			 buttonsActive = false;
		}
		break;

	case BUTTON2_Pin:
		if(buttonsActive){
			 Controller::getInstance()->IsInterrupt(interrupt::BUTTON2press);
			 osTimerStart(reboundTimerHandle,50);
			 buttonsActive = false;
		}
		break;

	case BLUE_BUTTON_Pin:
		if(buttonsActive){
			 Controller::getInstance()->IsInterrupt(interrupt::BLUE_BUTTONpress);
			 osTimerStart(reboundTimerHandle,10);
			 buttonsActive = false;
		}
		 break;
	case RECEIVED_SIGNAL_Pin:


		if(Controller::getInstance()->getState() == State::reception){
			HAL_GPIO_DeInit(RECEIVED_SIGNAL_GPIO_Port,RECEIVED_SIGNAL_Pin);
//			HAL_TIM_OC_Start(&htim2,htim2.Channel);
			HAL_UART_Receive_IT(&huart2, (uint8_t *)aRxBuffer, 1); //start uart
			HAL_ADC_Start_IT(&hadc1);                     // Start ADC conversion
			HAL_ADC_Start_IT(&hadc3);                     // Start ADC conversion
		}
		break;

	default:
		break;
  }

}

/**
  * @brief Rx Transfer completed callbacks
  * @param huart: uart handle
  * @retval None
  */
extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	Controller::getInstance()->IsInterrupt(interrupt::RECEIVED_SIGNAL);
	Controller::getInstance()->readBits(aRxBuffer[0]);

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*Configure GPIO pin : RECEIVED_SIGNAL_Pin */
	GPIO_InitStruct.Pin = RECEIVED_SIGNAL_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(RECEIVED_SIGNAL_GPIO_Port, &GPIO_InitStruct);

}

extern "C" void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2) {
	HAL_UART_Receive_IT(&huart2, (uint8_t *)aRxBuffer, 1); //start uart
	HAL_ADC_Start_IT(&hadc1);                     // Start ADC conversion
	HAL_ADC_Start_IT(&hadc3);                     // Start ADC conversion
  }
  HAL_TIM_OC_Stop(&htim2,htim2.Channel);

}

