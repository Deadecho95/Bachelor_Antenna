/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2018  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.46 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Software GmbH
Licensed to:              ARM Ltd, 110 Fulbourn Road, CB1 9NJ Cambridge, UK
Licensed SEGGER software: emWin
License number:           GUI-00181
License model:            LES-SLA-20007, Agreement, effective since October 1st 2011 
Licensed product:         MDK-ARM Professional
Licensed platform:        ARM7/9, Cortex-M/R4
Licensed number of seats: -
----------------------------------------------------------------------
File        : example.c
Purpose     : Main program Template
---------------------------END-OF-HEADER------------------------------
*/

#include "main.h"
#include "GUI.h"
#include "UserInterface.h"
#include "WIDGET.h"
#include "dialog.h"
#include "Board_Buttons.h"
#include <string.h>
#include <stdlib.h>


#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif

// Main stack size must be multiple of 8 Bytes
#define APP_MAIN_STK_SZ (1024U)
uint64_t app_main_stk[APP_MAIN_STK_SZ / 8];
const osThreadAttr_t app_main_attr = {
  .stack_mem  = &app_main_stk[0],
  .stack_size = sizeof(app_main_stk)
};



/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
__NO_RETURN void app_main (void *argument) {
  int32_t xPos, yPos, xSize, ySize, value, oldvalue;


  (void)argument;


  GUI_SetBkColor(GUI_RED);
  GUI_Clear();
  GUI_Delay(200);
  GUI_SetBkColor(GUI_GREEN);
  GUI_Clear();
  GUI_Delay(200);
  GUI_SetBkColor(GUI_BLUE);
  GUI_Clear();
  GUI_Delay(200);

  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();

  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();

  GUI_SetFont(&GUI_FontComic24B_1);
  GUI_SetColor(GUI_WHITE);



	value = 0;
	oldvalue = 0;

  xPos = xSize / 2;
  yPos = ySize / 2;
	
	//interface
	
	char valueToStr[3];
	sprintf(valueToStr, "%d", value);
	
	//concat value + text
	char* text = "power : ";
	
	char textToDisp[12];
	strcat(textToDisp, text);
	strcat(textToDisp,valueToStr);
	
	//display string
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontComic24B_1);
	GUI_DispStringHCenterAt("Receiver",   xPos, 20);
	GUI_DispStringAt(textToDisp, xPos-40, 90);
	
	//prog bar vertical
  PROGBAR_Handle hProgBar;
	hProgBar = PROGBAR_CreateEx(xPos-20,120, 40, 100,0, WM_CF_SHOW, PROGBAR_CF_VERTICAL, 1);
	PROGBAR_SetText(hProgBar, "power");

  while (1) {
		
		//change value
		value = (value + Buttons_GetState())%101;
		
		//toString the value
		sprintf(valueToStr, "%d", value);
		
		//show the value
		strcpy(textToDisp, text);
		strcat(textToDisp,valueToStr);
		
		//show press or not
    GUI_DispStringAt((Buttons_GetState())? "pressed     " : "not pressed", 10, yPos+yPos/2);
		
		if(value != oldvalue){
		GUI_DispStringAt("power :      ", xPos-40, 90);
		}
		GUI_DispStringAt(textToDisp, xPos-40, 90);
		PROGBAR_SetValue(hProgBar, value);
		oldvalue = value;
		GUI_Delay(10);
  } 
}
