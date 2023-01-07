/*
 * Multitasking example
 *
 * Created: 31/12/2022 20:00:13
 * Author : Maksym_Palii
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

void init_io_pins(void);
void init_tasks(void);
void init_timer_0(void);

// Task 1 
#define T1 250
void task_1(void);
volatile uint8_t time1;

// Task 2
#define T2 100
void task_2(void);
volatile uint8_t time2;

// Task 3
#define T3 20
void task_3(void);
volatile uint8_t time3;

// Task 4
#define T4 15
void task_4(void);
volatile uint8_t time4;

bool button_was_pressed = false;
bool double_speed_enabled = false;

ISR (TIMER0_COMPA_vect)
{
	if (time1 > 0) --time1;
	if (time2 > 0) --time2;
	if (time3 > 0) --time3;
	if (time4 > 0) --time4;
}

int main(void)
{
	init_io_pins();
	init_tasks();
	init_timer_0();
	sei();
	
    while (true) 
	{
		if (time1 == 0) { task_1(); }
		if (time2 == 0) { task_2(); }
		if (time3 == 0) { task_3(); }
		if (time4 == 0) { task_4(); }
	}
}


void init_io_pins(void)
{
	// Set port D pin 0, 1 and 2 as output
	DDRD |= _BV(DDD0) | _BV(DDD1) | _BV(DDD2);
	// Enable internal pull-up resistor pin 3 (port D)
	PORTD |= _BV(DDD3);
}

void init_tasks(void)
{
	time1 = T1;
	time2 = T2;
	time3 = T3;
	time4 = T4;
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

// Tasks implementation section

void task_1(void)
{
	// re-initialize task 1 timer
	time1 = T1;
	// Toggle pin 0 port D
	PORTD ^= _BV(PORTD0);
}

void task_2(void)
{
	// re-initialize task 2 timer
	time2 = T2;
	// Toggle pin 1 port D
	PORTD ^= _BV(PORTD1);
}

void task_3(void)
{
	// re-initialize task 3 timer
	time3 = double_speed_enabled ? (T3 / 2) : T3;
	// Toggle pin 2 port D
	PORTD ^= _BV(PORTD2);
}

void task_4(void)
{
	// re-initialize task 4 timer
	time4 = T4;
	// Button handling
	// check whether button was pressed
	if (bit_is_clear(PIND, PIND3) && !button_was_pressed)
	{
		button_was_pressed = true;
		// button push handling
		double_speed_enabled = double_speed_enabled ? false : true;
	}
	
	// check whether button was released
	if (bit_is_set(PIND, PIND3) && button_was_pressed)
	{
		button_was_pressed = false;
		// NOP on button release
	}
}
