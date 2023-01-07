/*
 * uart328p.c
 *
 * Created: 02/01/2023 20:43:41
 *  Author: Maksym_Palii
 */

#include <avr/io.h>
#include <stdbool.h>
#include <stddef.h>
#include "uart328p.h"

#define BUFFER_SIZE 9

char input_buffer[BUFFER_SIZE] = {'\0'};
int i = 0;
bool rx_allowed = true;

void UART_recieve(void)
{
	if (rx_allowed)
	{
		char data = UDR0;
		
		if (i >= BUFFER_SIZE)
		{
			i = 0;
		}
		
		if (data == '\n' || data == '\r')
		{
			input_buffer[i] = '\0';
			rx_allowed = false;
			i = 0;
		}
		else
		{
			input_buffer[i] = data;
			i++;
		}
	}
}

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
	
	// Enable receiving and transmission
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	
	init_frame_format();
	
	// enable interrupt on receiving
	UCSR0B |= _BV(RXCIE0);
}

char* UART_get_rx_data()
{
	return (rx_allowed) ? NULL : input_buffer;
}



void UART_transmit_byte(char data)
{
	// Wait for empty transmit buffer
	loop_until_bit_is_set(UCSR0A, UDRE0);
	// Put data into buffer, sends the data
	UDR0 = data;
}

void UART_transmit_string(char *str)
{
	uint8_t i = 0;
	while (str[i] != '\0')
	{
		UART_transmit_byte(str[i]);
		i++;
	}
}
