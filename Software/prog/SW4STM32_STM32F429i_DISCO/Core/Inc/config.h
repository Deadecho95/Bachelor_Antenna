/*
 * config.h
 *
 *  Created on: 27 juin 2019
 *      Author: chena
 */

#ifndef APPLICATION_USER_CORE_INC_CONFIG_H_
#define APPLICATION_USER_CORE_INC_CONFIG_H_

//uart
#define MAX_BIT_SIGNAL 8

//button
#define NBR_OF_BUTTONS 2

//ball
#define MAX_BALL 15

#define USART_BUFFER_SIZE 20

//lt5537
#define MIN_LT5537 91 //value minimum in dbm from the lt5537
#define SLOPE_mVDBm 27	//slope in mV/dBm calculated in the report
#define ADC_MIN_VALUE 0.735	//1bit in mV for the adc
#define MAX_POWER 30	//power max when the sensorball is front of us //\\(it can be changed)\\//
#define RECEPTION_LIMIT 70	//minimum value in dBm that the lt5537 can see
#define DAC_INCREMENT 400 //increment for the comparator //\\(it can be changed)\\//

//reception
#define MIN_TIME_WITHOUT_SIGNAL 100
//different type of interruptions
typedef enum interrupt {
	BUTTON1press = 0,
	BUTTON2press = 1,
	BLUE_BUTTONpress = 2,
	RECEIVED_SIGNAL = 3
}Interrupt;

//different type of states
typedef enum state {
	wait = 0,
	menu = 1,
	startReception = 2,
	calibrate = 3,
	reception = 4
}State;

#endif /* APPLICATION_USER_CORE_INC_CONFIG_H_ */
