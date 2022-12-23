#include <avr/interrupt.h>

#define t1 501			// 255-256
#define t2 501			// 255-256
 
// simple blinking tasks
void task1(void);
void task2(void);

void initialize(void);
          
volatile uint16_t time1;
volatile uint16_t time2;
         
ISR (TIMER0_COMPA_vect)
{      
  if (time1 > 1) --time1;
  if (time2 > 1) --time2;
}  

int main(void)
{  
	initialize();

	while(1)
	{   
		if (time1==1){ time1=t1; task1();}
		if (time2==1){ time2=t2; task2();}
	}
}
  
//Task 1
void task1(void) 
{  
	PORTD ^= (1 << PD0);
}
 
//Task 2  
void task2(void) 
{
	PORTD ^= (1 << PD1);
}

//Set it all up
void initialize(void)
{
	//set up port D as output
	DDRD=0xFF;
       
	//set up timer 0 for 1 mSec timebase 
	TIMSK0= (1<<OCIE0A);			//turn on timer 0 cmp match ISR 
	OCR0A =	249;  					//set the compare reg to 250 time ticks
	// turn on clear-on-match
	TCCR0A= (1<<WGM01);
	//set pre-scaler to divide by 64 
	TCCR0B= 0b00000011; 	

	
	time1 = t1;
	time2 = t2;
  
	sei();
}