/*
 * uart328p.h
 *
 * Created: 02/01/2023 20:43:00
 *  Author: Maksym_Palii
 */ 


#ifndef UART328P_H_
#define UART328P_H_

void UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);
void UART_recieve(void);
char* UART_get_rx_data(void);
void UART_transmit_string(char *str);

#endif /* UART328P_H_ */