#include "mcu/mcu.h"
#include "critical.h"

volatile int bInISR = 0;
volatile int bOMEnterCriticalRegionNested = 0;

int inISR()
{
	// Variable must be put to TRUE in every ISR to indicate execution
	// of an ISR and need to put back to FALSE before leaving ISR.
	return bInISR;
}

void enterCritical()
{
	// Only disable interrupts when not calling from an ISR
	if (!inISR())
	{
		if (!bOMEnterCriticalRegionNested)
		{
			// Turn off the priority configurable interrupts
		    __disable_irq();
		}
		bOMEnterCriticalRegionNested++;
	}
}

void exitCritical()
{
	// Only enable interrupts when not calling from an ISR
	if (!inISR())
	{
		bOMEnterCriticalRegionNested--;

		if (!bOMEnterCriticalRegionNested)
		{
			// Turn on the interrupts with configurable priority
		    __enable_irq();
		}
	}
}
