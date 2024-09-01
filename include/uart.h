#ifndef _UART_H
#define _UART_H

#include "stm32f722xx.h"

int init_uart(USART_TypeDef* uart, uint16_t baud);

int send_uart(USART_TypeDef* u, char* msg, int len);

int print(char *msg);

#endif // _UART_H