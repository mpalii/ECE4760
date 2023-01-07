/*
 * Timer 0 usage example, 50kHz generator
 *
 * Created: 28/12/2022 18:42:11
 * Author : Maksym_Palii
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>

void init_io_pins(void);
void init_timer_0(void);

ISR (TIMER0_COMPA_vect)
{
	// Toggle pin 0 port D
	PORTD ^= _BV(PORTD0);
}

int main(void)
{
	init_io_pins();
	init_timer_0();
	sei();
	
    while (true) 
	{ 
		// NOP
	}
}

void init_io_pins(void)
{
	// Set port D pin 0 as output
	DDRD |= _BV(DDD0);
}

/****************************************************************************/
/* Set up timer 0 for 1 uSec timebase										*/
/* (1 (prescaler) * 80 (OCR0A + 1)) / 8_000_000 MHz = 0.00001Sec = 10uSec	*/
/****************************************************************************/
void init_timer_0(void)
{	
	// TCCR0A – Timer/Counter0 Control Register channel A
	TCCR0A = _BV(WGM01);				// Clear Timer on Compare Match (CTC) mode (only works with channel)
	
	// TCCR0B – Timer/Counter0 Control Register channel B
	TCCR0B = _BV(CS00);					// No prescaling
	
	// OCR0A – Timer/Counter0 Output Compare Register channel A
	OCR0A =	79;							//set the compare reg to 80 time ticks (zero based)
	
	// TIMSK0 – Timer/Counter0 Interrupt Mask Register
	TIMSK0 = _BV(OCIE0A);				// Timer/Counter0 Output Compare Match channel A Interrupt Enable
}
