/**
 * @author Maksym Palii
 * @brief Check644
 * @version 0.1
 * @date 2022-11-14 
 */

#define F_CPU (16000000UL)

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0x01;        // Configure data direction for pin 0 (port B) as OUTPUT

    while (true) 
    {
        _delay_ms(500);
        PORTB ^= _BV(PB0);
    }
}
