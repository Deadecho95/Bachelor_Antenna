#include "config/trace-config.h"

#if (USE_PLATFORM_F7_DISCO_GCC_TRACE != 0)

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "hal/uart.h"
#include "trace/trace.h"        // Include the general trace.h file (common for many projects)

#ifndef TRACE_ADD_CRLF_SEQU
#define TRACE_ADD_CRLF_SEQU 	0
#endif

static Uart traceUart(TRACE_UART_CONSTRUCTOR_PARAMETERS);
static char strTrace[255];

static int32_t checkStringEnding(char * str, uint32_t len);

void trace_initialize()
{
    Trace::initialize();
}

void trace_out(const char * const format , ...)
{
    va_list args;

    // Format string
    va_start(args, format);
    vsprintf(strTrace, format, args);
    va_end(args);

    checkStringEnding(strTrace, strlen(strTrace));

    traceUart.write(strTrace);
}

//static
void Trace::initialize()
{
	traceUart.initialize(TRACE_UART_BAUD_RATE);
}

static int32_t checkStringEnding(char * str, uint32_t len)
{
	if (!len)
	{
		return 0;
	}

	if (str[len-1] != '\n')
	{
#if (TRACE_ADD_CRLF_SEQU != 0)
		// Add "\r\n" at the end of the string
		str[len] = '\r';
		str[len+1] = '\n';
		str[len+2] = '\0';
#else
		// Add "\n" at the end of the string
		str[len] = '\n';
		str[len+1] = '\0';
#endif // TRACE_ADD_CRLF_SEQU
		}
#if (TRACE_ADD_CRLF_SEQU != 0)
	// Check string finishing with "\r\n"
	else if (str[len-1] == '\n')
	{
		// Check if second last char is an '\r'
		if (len == 1 ||
			(len >= 2 && str[len-2] != '\r'))
		{
			// Squeeze a '\r'
			memmove(&str[len], &str[len-1], 2);
			str[len-1] = '\r';
		}
	}
#endif // TRACE_ADD_CRLF_SEQU
	return strlen(str);
}

void Trace::out(string str)
{
	if (str[str.length()-1] != '\n')
	{
		str += '\n';
	}
	traceUart.write(str.data(), str.length());
}

void Trace::out(const char * format, ...)
{
	va_list args;

	// Format string
	va_start(args, format);
	vsprintf(strTrace, format, args);
	va_end(args);

	checkStringEnding(strTrace, strlen(strTrace));

	traceUart.write(strTrace);
}

#endif // USE_PLATFORM_F7_DISCO_GCC_TRACE
