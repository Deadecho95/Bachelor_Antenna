#include <string.h>
#include "mcu/mcu.h"
#include "uart.h"

#ifndef TRACE_UART_PREEMPTION_PRIO
#define TRACE_UART_PREEMPTION_PRIO	0
#endif

Uart * Uart::_sUart[Uart::UART_COUNT];				// Comment: Startup script should initialize pointers to zero (.bss section)
bool Uart::_sInitialized[Uart::UART_COUNT];			// Same for other arrays

Uart::Uart(const unsigned char uartNbr, UART_HandleTypeDef * uartHandle, bool bTxDMA /* = false */)
 : _uartNbr(-1),
   _pUartHandle(NULL),
   _bTxDMA(bTxDMA)
{
	assert(uartNbr < UART_COUNT);

	if (uartNbr < UART_COUNT)
    {
        if (!_sUart[uartNbr])
        {
            // Register instance
            _sUart[uartNbr] = this;
            _uartNbr = uartNbr;

            _pUartHandle = uartHandle;
        }
        else
        {
            assert(false);  // Error: Instance for specified UART already exists.
        }
    }
}

Uart::~Uart()
{

}

bool Uart::initialize()
{
	return true;
}

bool Uart::enable()
{
    // Enable the USART
    __HAL_UART_ENABLE(_pUartHandle);
    return true;
}

bool Uart::disable()
{
    // enable the USART
    __HAL_UART_DISABLE(_pUartHandle);
    return true;
}

void Uart::write(const char * str, unsigned int length /* = 0 */)
{
	if (!length)
	{
		length = strlen(str);
	}

    if (!_bTxDMA)
    {   // Transmit without DMA
        // Send next character
        HAL_UART_Transmit(_pUartHandle, (uint8_t *)str, length, 50);
    }
    else
    {   // TX DMA enabled
        writeUsingDMA((const uint8_t *)str, length);
    }
}

void Uart::writeUsingDMA(const uint8_t * str, uint32_t length)
{
    assert(length <= sizeof(_pTxDmaBuffer));

    // Copy data to TX DMA buffer
    ::memcpy(_pTxDmaBuffer, str, length);

    // Check that a Tx process is not already ongoing
    // (should never happen, but who knows!)
    while (_pUartHandle->gState != HAL_UART_STATE_READY)
    { continue; }

    // Give data to TX DMA
    HAL_UART_Transmit_DMA(_pUartHandle, _pTxDmaBuffer, length);
}

