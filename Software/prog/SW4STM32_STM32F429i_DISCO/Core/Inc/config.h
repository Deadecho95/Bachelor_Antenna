/*
 * config.h
 *
 *  Created on: 27 juin 2019
 *      Author: chena
 */

#ifndef APPLICATION_USER_CORE_INC_CONFIG_H_
#define APPLICATION_USER_CORE_INC_CONFIG_H_

#define START_BIT 2
#define MAX_BIT_SIGNAL 8
#define CRC_SIGNAL 4
#define NBR_OF_BUTTONS 2

//different type of interruptions
typedef enum interrupt {
	BUTTON1press = 0,
	BUTTON2press = 1,
	BLUE_BUTTONpress = 2,
	RECEIVED_SIGNAL = 3
}Interrupt;

#endif /* APPLICATION_USER_CORE_INC_CONFIG_H_ */
