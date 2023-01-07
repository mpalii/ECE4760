/*
 * uart328p.c
 *
 * Created: 04/01/2023 20:58:47
 *  Author: Maksym_Palii
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include "uart328p.h"

void init_frame_format()
{
	/************************************************************************/
	/* Default frame format:                                                */
	/* 1 start bit, 8 data bits, no parity bit, 1 stop bit					*/
	/************************************************************************/
}

void UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled)
{
	// TODO add description
	uint32_t baud_rate_divider = 16;
	
	// Check double speed (U2X) mode
	if (double_speed_enabled)
	{
		UCSR0A = _BV(U2X0);
		baud_rate_divider /= 2;
	}
	
	// Set baud rate
	UBRR0 = f_cpu / (baud_rate_divider * baud_rate) - 1;
	
	// Enable transmission
	UCSR0B = _BV(TXEN0);
	
	init_frame_format();
}

void UART_transmit(char data)
{
	// Wait for empty transmit buffer
	loop_until_bit_is_set(UCSR0A, UDRE0);
	// Put data into buffer, sends the data
	UDR0 = data;
}

void UART_transmit_array(char* array)
{
	uint8_t i = 0;
	while (array[i] != '\0')
	{
		UART_transmit(array[i]);
		i++;
	}
}
