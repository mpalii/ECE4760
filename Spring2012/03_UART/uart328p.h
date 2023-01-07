/*
 * uart328p.h
 *
 * Created: 04/01/2023 20:58:31
 *  Author: Maksym_Palii
 */ 

#ifndef UART328P_H_
#define UART328P_H_

void UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);
void UART_transmit(char data);
void UART_transmit_array(char* array);

#endif /* UART328P_H_ */