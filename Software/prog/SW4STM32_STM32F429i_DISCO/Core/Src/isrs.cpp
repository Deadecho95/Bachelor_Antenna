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
extern TIM_HandleTypeDef htim2;

uint8_t count;
GPIO_InitTypeDef GPIO_InitStruct = {0};
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
	case RECEIVED_SIGNAL_Pin:
		 Controller::getInstance()->IsInterrupt(interrupt::RECEIVED_SIGNAL);
		 HAL_TIM_OC_Start_IT(&htim2, htim2.Channel);   // Start TIM2 with trigger channel1
		 HAL_ADC_Start_IT(&hadc1);                     // Start ADC conversion
		 HAL_ADC_Start_IT(&hadc3);                     // Start ADC conversion
		 HAL_GPIO_DeInit(RECEIVED_SIGNAL_GPIO_Port, RECEIVED_SIGNAL_Pin);
		break;

	default:
		break;
  }

}

extern "C" void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  count++;

  /////////test/////////
  if(htim == &htim2){
  HAL_GPIO_TogglePin(EN_DEMODULATOR_GPIO_Port, EN_DEMODULATOR_Pin);
  }

  Controller::getInstance()->readBits(count, HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO_Port,BLUE_BUTTON_Pin));
  if(count == 12){
	  count = 0;
	  HAL_TIM_OC_Stop_IT(&htim2, 0);   // Stop TIM2 with trigger channel1
	  /*Configure GPIO pin : RECEIVED_SIGNAL_Pin */
	  GPIO_InitStruct.Pin = RECEIVED_SIGNAL_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(RECEIVED_SIGNAL_GPIO_Port, &GPIO_InitStruct);
  }
}

