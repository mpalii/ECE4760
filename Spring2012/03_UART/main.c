/*
 * 03_UART.c
 *
 * Created: 04/01/2023 20:55:38
 * Author : Maksym_Palii
 */ 

#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "uart328p.h"

void init_timer_0(void);

volatile uint32_t operation_time = 0;					// 4 bytes

char init_message[] = "Start up...\n\r";				// 14 bytes message (including '\0' byte, '\n' is CR and LF symbols)
char test_message[] = "********************\n\r";		// 23 bytes message (including '\0' byte, '\n' is CR and LF symbols)
char buffer[50];

ISR (TIMER0_COMPA_vect)
{
	operation_time++;
}

int main(void)
{
	init_timer_0();
	sei();
	UART_init(F_CPU, 9600, false);
	
	UART_transmit_array(init_message);
	
	uint32_t start_time = operation_time;
	UART_transmit_array(test_message);
	uint32_t finish_time = operation_time;
	
	sprintf(buffer, "TX time: %lu ms\n\r", (finish_time - start_time));
	UART_transmit_array(buffer);
	
    while (true) 
    {
		// NOP
    }
}

/****************************************************************************/
/* Set up timer 0 for 1 mSec timebase										*/
/* (64 (prescaler) * 125 (OCR0A + 1)) / 8_000_000 MHz = 0.001Sec = 1mSec	*/
/****************************************************************************/
void init_timer_0(void)
{
	// TCCR0A – Timer/Counter0 Control Register channel A
	TCCR0A = _BV(WGM01);				// Clear Timer on Compare Match (CTC) mode (only works with channel)
	
	// TCCR0B – Timer/Counter0 Control Register channel B
	TCCR0B = _BV(CS01) | _BV(CS00);		// clk/64 (From prescaler)
	
	// OCR0A – Timer/Counter0 Output Compare Register channel A
	OCR0A =	124;  						//set the compare reg to 125 time ticks (zero based)
	
	// TIMSK0 – Timer/Counter0 Interrupt Mask Register
	TIMSK0 = _BV(OCIE0A);				// Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

