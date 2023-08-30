/*
 * UART.h
 *
 * Created: 2023-08-29 오후 2:27:31
 *  Author: user
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void UART0_init();
void UART0_transmit(char data);
unsigned UART0_receive(void);




#endif /* UART_H_ */