/*
 * 04_UART_async.c
 *
 * Created: 02/01/2023 17:49:29
 * Author : Maksym_Palii
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "uart328p.h"

ISR(USART_RX_vect)
{
	UART_recieve();
}

int main(void)
{
    UART_init(F_CPU, 9600, false);
	sei();
	UART_transmit_string("Start up...\n\r");
	
    while (true) 
    {
		// NOP
    }
}

