/*
 * 00_Check.c
 *
 * Created: 08/11/2022 15:23:33
 * Author : Maksym_Palii
 */ 

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//timeout values for each task
#define t1 1000  
#define t2 500
 
//the three task subroutines
void task1(void);  	//blink 1 
void task2(void);	//blink 2 
void initialize(void); //all the usual mcu stuff 
          
volatile uint16_t time1, time2;	//timeout counters 

ISR (TIMER0_COMPA_vect)
{  
	//PORTD ^= 1;
	if (time1>0)	--time1;
	//if (time2>0) 	--time2;
}  

int main(void)
{  
  initialize();
  
  while(1)
  { 
	  
    if (time1==0){ time1=t1; task1(); }
    //if (time2==0){ time2=t2; task2(); }
		
  }
}
  

void task1(void) 
{  
	PORTD ^= 0x01;
}

void task2(void) 
{
	PORTB ^= 0x02;
}


void initialize(void)
{
  //set up the ports
  DDRB=0x03;    // PORT B is an output  
  DDRD=0x01;	// PORT D is an input 
           
  //set up timer 0 for 1 mSec ticks
  
  TIMSK0 = 2;		//turn on timer 0 cmp match ISR 
  
  OCR0A = 124;  	//set the compare reg to 250 time ticks
  
  TCCR0A = 0b00000010; // turn on clear-on-match
  
  TCCR0B = 0b00000011;	// clock prescaler to 64
  
  /*
  // Enable 16-bit Timer/Counter1; CLK/64 (from prescaler)
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // Set Output Compare Register 1A value
  OCR1A = 250;
  // Enable Clear Timer on Compare (CTC) mode
  TCCR1A |= (1 << COM1A1);
  // Enable 16-bit Timer/Counter1 output compare a match interrupt
  TIMSK1 |= (1 << OCIE1A);*/

  time1=t1;
  time2=t2;

  sei();
}

