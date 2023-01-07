/*
 * uart328p.h
 *
 * Created: 02/01/2023 16:17:31
 *  Author: Maksym_Palii
 */ 


#ifndef UART328P_H_
#define UART328P_H_

FILE* UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);

#endif /* UART328P_H_ */