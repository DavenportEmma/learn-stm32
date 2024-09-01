#ifndef _UART_H
#define _UART_H

#include "stm32f722xx.h"

#ifndef MAX_PRINT_LENGTH
#define MAX_PRINT_LENGTH 64
#endif


int send_uart(USART_TypeDef* u, char* msg, int len);

int print(char *msg);

#endif // _UART_H