#ifndef HAL_UART_H
#define HAL_UART_H

#include "config/uart-config.h"
#include "assert.h"

#ifndef UART_TX_DMA_BUFFER_SIZE
    #define UART_TX_DMA_BUFFER_SIZE 128
#endif

/**
 * @brief Provides general access to the microcontrollers UART peripheral.
 */
class Uart
{
	friend class Factory;

public:
	Uart(const unsigned char uartNbr, UART_HandleTypeDef * uartHandle, bool bTxDMA = false);
	virtual ~Uart();

	bool initialize();

	bool enable();
	bool disable();

	void write(const char * str, unsigned int length = 0);


	/**
	 * Static accessor to the instances of UART. Used by the factory.
	 * You should not use this method directly. Use the factory to
	 * access an UART instead.
	 */
	static inline Uart & uart(const unsigned char uartNbr)
	{
		assert(uartNbr < UART_COUNT);
		return *_sUart[uartNbr];
	}

	/**
	 * Checks if UART is present and initialized
	 */
	static inline bool present(const unsigned char uartNbr)
	{
		return (uartNbr < UART_COUNT &&
				_sInitialized[uartNbr]) ? true : false;
	}

protected:
    void writeUsingDMA(const uint8_t * str, uint32_t length);

protected:
	static const unsigned char UART_COUNT = 3;	///< Constant indicating how many USART the MCU has

	unsigned char _uartNbr;						///< Number of UART. Index starting at 0
	UART_HandleTypeDef * _pUartHandle;          ///< Reference to the USART structure

	static Uart * _sUart[UART_COUNT];			///< Array to check if USB device was created already
	static bool _sInitialized[UART_COUNT];		///< Indicates if the UART has been initialized

    const bool _bTxDMA;                                 ///< Use DMA for transmission
    uint8_t _pTxDmaBuffer[UART_TX_DMA_BUFFER_SIZE];     ///< Buffer used by DMA for transmission
};

#endif // HAL_UART_H
