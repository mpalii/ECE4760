/*
 * Delay example, visual perception
 *
 * Created: 28/12/2022 22:24:18
 * Author : Maksym_Palii
 */ 

#define F_CPU 8000000UL
#define half_period_for_frequency(FR) (1000000 / (2.0 * FR))		// microseconds

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

int main(void)
{
	// Configure data direction for pins 0 (port D) as OUTPUT
	DDRD = _BV(DDD0);

	const double HALF_PERIOD = half_period_for_frequency(1);		// 1Hz - just a period of one second
	//const double HALF_PERIOD = half_period_for_frequency(24);		// 24Hz - frame rate standard for 35 mm sound films
	//const double HALF_PERIOD = half_period_for_frequency(50);		// 50Hz - AC frequency standart (use camera of a smartphone to see blinking)
	//const double HALF_PERIOD = half_period_for_frequency(240);	// 240Hz - display matrix refresh rate
	//const double HALF_PERIOD = half_period_for_frequency(50000);	// 50kHz - something really fast :)	
	
    while (true) 
    {
		PORTD ^= _BV(PORTD0);
		_delay_us(HALF_PERIOD);
    }
}
