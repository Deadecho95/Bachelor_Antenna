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



extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc3;
extern uint8_t aRxBuffer[USART_BUFFER_SIZE];
extern UART_HandleTypeDef huart2;
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
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);

  switch (GPIO_Pin) {
	case BUTTON1_Pin:
		 Controller::getInstance()->IsInterrupt(interrupt::BUTTON1press);
		break;

	case BUTTON2_Pin:
		 Controller::getInstance()->IsInterrupt(interrupt::BUTTON2press);
		break;

	case BLUE_BUTTON_Pin:
		 Controller::getInstance()->IsInterrupt(interrupt::BLUE_BUTTONpress);
		 break;
	case RECEIVED_SIGNAL_Pin:
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
	/* Prevent unused argument(s) compilation warning */
	UNUSED(huart);

	Controller::getInstance()->IsInterrupt(interrupt::RECEIVED_SIGNAL);
	Controller::getInstance()->readBits(aRxBuffer[0]);
	HAL_ADC_Start_IT(&hadc1);                     // Start ADC conversion
	HAL_ADC_Start_IT(&hadc3);                     // Start ADC conversion
	HAL_UART_Receive_IT(&huart2, (uint8_t *)aRxBuffer, 1);
}


