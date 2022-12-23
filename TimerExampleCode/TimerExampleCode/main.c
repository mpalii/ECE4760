#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "uart.h"

#define t1 500
#define t2 250
#define t3 60

volatile unsigned int time1, time2, time3;
bool flag = false;
volatile uint32_t general_time;

FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

void initialize(void);
void task1(void);
void task2(void);
void task3(void);

ISR(TIMER0_COMPA_vect)
{
	general_time++;
	if (time1 > 1) --time1;
	if (time2 > 1) --time2;
	if (time3 > 1) --time3;
}

int main(void)
{
	initialize();
	while (1)
	{
		if (1 == time1) task1();
		if (1 == time2) task2();
		if (1 == time3) task3();
	}
}

void initialize(void)
{
	DDRB = 0x03;
	PORTB = 0x03;
	DDRD = 0x02;	// DDRD = (1 << PORTD1);	// uart and pin7 output
	PORTD = 0x80;	// pull-up resistor
	
	TIMSK0 = (1 << OCIE0A);
	OCR0A = 71;
	TCCR0A = (1 << WGM01);
	TCCR0B = 4;		// 0b00000100
	
	time1 = t1 + 1;
	time2 = t2 + 1;
	time3 = t3 + 1;
	
	flag = false;
	
	uart_init();
	stdout = stdin = stderr = &uart_str;
	fprintf(stdout, "Starting...\n");
	
	sei();
}

void task1(void)
{
	time1 = t1 + 1; 
	PORTB ^= 1;
	fprintf(stdout, "t1:%lu\n", general_time);
}

void task2(void)
{
	time2 = flag ? t2/2 + 1 : t2 + 1;
	PORTB ^= 2;
	fprintf(stdout, "t2:%lu\n", general_time);
}

void task3(void)
{
	time3 = t3 + 1;
	flag = (~PIND & 0x80) ? true : false; //PD7 pin
}

















// #include <inttypes.h>
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <stdio.h>
// #include "uart.h"
// 
// #define t1 250  
// #define t2 125
// #define t3 60  
//  
// void task1(void);  
// void task2(void);
// void task3(void);	
// 
// void initialize(void);
//           
// volatile unsigned char time1, time2, time3;	//timeout counters 
// unsigned char tsk2c;				
// unsigned char tsk3m;				
// unsigned char led;					
// unsigned int time;					
// 
// 
// // UART file descriptor
// // putchar and getchar are in uart.c
// FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
//          
// //**********************************************************
// //timer 0 compare ISR
// ISR (TIMER0_COMPA_vect)
// {      
//   //Decrement the three times if they are not already zero
//   if (time1>0)	--time1;
//   if (time2>0) 	--time2;
//   if (time3>0)	--time3;
// }
// 
// 
// int main(void)
// {  
// 	initialize();
//   
// 	while(1)
// 	{    
// 		if (time1==0){ time1=t1; task1();}
// 		if (time2==0){ time2=t2; task2();}
// 		if (time3==0){ time3=t3; task3();}
// 	}
// }
//   
// //*******************************         
// //Task subroutines
// //Task 1
// void task1(void) 
// {  
//   if (tsk3m != 0) time1 >>= 2;  //check for task 3 message
//   
//   //toggle the zeros bit
//   led = led ^ 0x01;
//   PORTB = led;
// }
//  
// //******************************* 
// //Task 2  
// void task2(void) 
// {
//   if (--tsk2c == 0)  //have we waited 1/2 second?
//   {  
//   	tsk2c = 4;		//reload the 1/2 sec counter
//      //toggle the ones bit
//   	led = led ^ 0x02;
//   	PORTB = led;
// 	//fprintf(stdout,"%d\n\r",time++) ;
// 	
//   }
// }
//  
// //*******************************   
// //Task 3  
// void task3(void) 
// {
//   // detect D.7 button push and
//   // generate the message for task 1
//   tsk3m = ~PIND & 0x80;  
// }
//   
// //********************************************************** 
// //Set it all up
// void initialize(void)
// {
//   //set up the ports
//   DDRB=0x0f;    // PORT B is an output  
//   PORTB=0;
//   DDRD=0x00;	// PORT D is an input 
//            
//   //set up timer 0 for 1 mSec ticks
//   TIMSK0 = 2;		//turn on timer 0 cmp match ISR 
//   OCR0A = 250;  	//set the compare reg to 250 time ticks
//   TCCR0A = 0b00000010; // turn on clear-on-match
//   TCCR0B = 0b00000011;	// clock prescalar to 64
//     
//   //init the LED status (all off)
//   led=0xff; 
//   
//   //init the task timers
//   time1=t1;
//   time2=t2;
//   time3=t3;    
//   
//   //init the task 2 state variable for four ticks
//   tsk2c=4;
//   
//   //init the task 3 message for no message
//   tsk3m=0;
// 
//   //init the UART -- uart_init() is in uart.c
//   uart_init();
//   stdout = stdin = stderr = &uart_str;
//   fprintf(stdout,"Starting...\n\r");
//       
//   //crank up the ISRs
//   sei();
// }
// 
//    