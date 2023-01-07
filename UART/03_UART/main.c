/*
 * UART
 *
 * Created: 02/01/2023 15:43:09
 * Author : Maksym_Palii
 */

#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "uart328p.h"

#define BUFFER_SIZE 41
#define F_CPU 8000000UL

volatile char input_command[BUFFER_SIZE];

int main(void)
{
	stdin = stdout = stderr = UART_init(F_CPU, 9600, false);
	printf("Start up...\n\r");

	while (true)
	{
		scanf("%s", input_command);
		printf("INPUT:'%s'\n\r", input_command);
	}
}
