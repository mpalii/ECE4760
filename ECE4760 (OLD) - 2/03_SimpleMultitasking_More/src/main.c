/**
 * @author Maksym Palii
 * @brief Simple multitasking - tasks limit
 * @version 0.1
 * @date 2022-11-14 
 */

#include <avr/interrupt.h>

#define t1 501
#define t2 1001	
#define t3 2001	
#define t4 4001	
#define t5 8001	
#define t6 16001	
#define t7 32001	
#define t8 64001	
 
// simple blinking tasks
void task1(void);
void task2(void);
void task3(void);
void task4(void);
void task5(void);
void task6(void);
void task7(void);
void task8(void);

void initialize(void);
          
volatile uint16_t time1;
volatile uint16_t time2;
volatile uint16_t time3;
volatile uint16_t time4;
volatile uint16_t time5;
volatile uint16_t time6;
volatile uint16_t time7;
volatile uint16_t time8;
         
ISR (TIMER0_COMPA_vect)
{      
  if (time1 > 1) --time1;
  if (time2 > 1) --time2;
  if (time3 > 1) --time3;
  if (time4 > 1) --time4;
  if (time5 > 1) --time5;
  if (time6 > 1) --time6;
  if (time7 > 1) --time7;
  if (time8 > 1) --time8;
}  

int main(void)
{  
	initialize();

	while(1)
	{   
		if (time1==1){ time1=t1; task1();}
		if (time2==1){ time2=t2; task2();}
		if (time3==1){ time3=t3; task3();}
		if (time4==1){ time4=t4; task4();}
		if (time5==1){ time5=t5; task5();}
		if (time6==1){ time6=t6; task6();}
		if (time7==1){ time7=t7; task7();}
		if (time8==1){ time8=t8; task8();}
	}
}
  
//Task 1
void task1(void) 
{  
	PORTB ^= (1 << PB0);
}
 
//Task 2  
void task2(void) 
{
	PORTB ^= (1 << PB1);
}
 
//Task 3  
void task3(void) 
{
	PORTB ^= (1 << PB2);
}
 
//Task 4  
void task4(void) 
{
	PORTB ^= (1 << PB3);
}
 
//Task 5  
void task5(void) 
{
	PORTB ^= (1 << PB4);
}
 
//Task 6  
void task6(void) 
{
	PORTB ^= (1 << PB5);
}
 
//Task 7  
void task7(void) 
{
	PORTB ^= (1 << PB6);
}
 
//Task 8  
void task8(void) 
{
	PORTB ^= (1 << PB7);
}

//Set it all up
void initialize(void)
{
	//set up port B as output
	DDRB=0xFF;
       
	//set up timer 0 for 1 mSec timebase 
	TCCR0A= (1<<WGM01);				// turn on clear-on-match 
	TCCR0B= (1<<CS00) | (1<<CS01);	// set pre-scaler to divide by 64	
	OCR0A =	249;  					// set the compare reg to 250 time ticks (include zero)
	TIMSK0= (1<<OCIE0A);			// turn on timer 0 cmp match ISR 

	
	time1 = t1;
	time2 = t2;
	time3 = t3;
	time4 = t4;
	time5 = t5;
	time6 = t6;
	time7 = t7;
	time8 = t8;
  
	sei();
}