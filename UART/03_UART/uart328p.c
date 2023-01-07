/*
 * uart328p.c
 *
 * Created: 02/01/2023 16:19:22
 *  Author: Maksym_Palii
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "uart328p.h"

static FILE uart_stream;

int UART_transmit(char data, FILE* stream)
{
	// Wait for empty transmit buffer
	loop_until_bit_is_set(UCSR0A, UDRE0);
	// Put data into buffer, sends the data
	UDR0 = data;
	
	return 0;
}

int UART_receive(FILE* stream)
{
	// Wait for data to be received
	loop_until_bit_is_set(UCSR0A, RXC0);
	// Get and return received data from buffer
	return UDR0;
}

void init_frame_format()
{
	/************************************************************************/
	/* Default frame format:                                                */
	/* 1 start bit, 8 data bits, no parity bit, 1 stop bit					*/
	/************************************************************************/
}

FILE* UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled)
{
	// TODO description
	uint32_t baud_rate_divider = 16;
	
	// Check double speed (U2X) mode
	if (double_speed_enabled)
	{
		UCSR0A = _BV(U2X0);
		baud_rate_divider /= 2;
	}
	
	// Set baud rate
	UBRR0 = f_cpu / (baud_rate_divider * baud_rate) - 1;
	
	// Enable receiving and transmission
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	
	init_frame_format();
	
	// Initialize UART-related IO stream
	fdev_setup_stream(&uart_stream, UART_transmit, UART_receive, _FDEV_SETUP_RW);
	return &uart_stream;
}