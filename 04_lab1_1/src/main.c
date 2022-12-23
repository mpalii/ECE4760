/**
 * @author Maksym Palii
 * @brief Lab1_1
 * @version 0.1
 * @date 2022-11-18 
 */

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"

#define t1 250
#define t2 125
#define t3 60

volatile unsigned char time1, time2, time3;
unsigned char tsk2c, tsk3m, led;
volatile uint32_t general_time;

FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

void initialize(void);
void task1(void);
void task2(void);
void task3(void);

ISR(TIMER0_COMPA_vect)
{
	general_time++;
	if (time1 > 0) --time1;
	if (time2 > 0) --time2;
	if (time3 > 0) --time3;
}

int main(void)
{
	initialize();
	while (1)
	{
		if (0 == time1) {time1 = t1; task1();}
		if (0 == time2) {time2 = t2; task2();}
		if (0 == time3) {time3 = t3; task3();}
	}
}

void initialize(void)
{
	DDRB = 0x03;
	PORTB = 0x03;
	DDRD = 0x02;	// DDRD = (1 << PORTD1);	// uart and pin7 output
	PORTD = 0x80;	// pull-up resistor
	
	TIMSK0 = (1 << OCIE0A);
	OCR0A = 249;
	TCCR0A = (1 << WGM01);
	TCCR0B = 3;		// 0b00000011
	
	led = 0x00;
	
	time1 = t1;
	time2 = t2;
	time3 = t3;
	
	tsk2c = 4;
	tsk3m = 0;
	
	uart_init();
	stdout = stdin = stderr = &uart_str;
	fprintf(stdout, "Starting...\n");
	
	sei();
}

void task1(void)
{
	fprintf(stdout, "t1:%lu\n", general_time);
	if (tsk3m) time1 >>= 2;
	led = led ^ 1;
	PORTB = led;
}

void task2(void)
{
	if (--tsk2c == 0)
	{
		fprintf(stdout, "t2:%lu\n", general_time);
		tsk2c = 4;
		led = led ^ 0x02;
		PORTB = led;
	}
}

void task3(void)
{
	tsk3m = ~PIND & 0x80; //PD7 pin
}
