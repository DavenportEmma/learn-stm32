#include "stm32f722xx.h"
#include "uart.h"
#include "config.h"

int init_uart(USART_TypeDef* uart, uint16_t baud) {
    #ifndef SYS_CLK
        #define SYS_CLK 16000000
    #endif

    uint8_t uartNum;
    GPIO_TypeDef* g;
    uint8_t gpioPin;

    if(uart == USART1) {
        uartNum = 1;
        g = GPIOB;
        gpioPin = 6;
        
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN_Msk;    // enable clock for gpio
        g->AFR[0] |= 0x7000000;                     // set alternate function to af7
        RCC->APB2ENR |= 0x10;                       // Enable clock for uart
    } else if (uart == USART3) {
        // this uart is connected to the stlink uart
        uartNum = 3;
        g = GPIOD;
        gpioPin = 8;
        
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN_Msk;
        g->AFR[1] |= 0x7;
        RCC->APB1ENR |= (1 << 18);
    } else {
        return 1;
    }
    
    g->MODER &= ~(0x3 << (gpioPin * 2));    // Clear mode bits for gpio
    g->MODER |= 2 << (gpioPin * 2);         // set alternate mode for pin

    RCC->DCKCFGR2 |= (1 << ((uartNum - 1) * 2));
    RCC->CR |= RCC_CR_HSION;

    uart->CR1 &= ~(0xFFFFFFFF);   // clear cr1
    uart->BRR |= SYS_CLK / baud;  // Assuming APB2 clock is 16 MHz
    uart->CR1 |= 0x1; // enable usart
    uart->CR1 |= 0x8; // enable tx

    return 0;
}

int send_uart(USART_TypeDef* u, char* msg, int len) {
    for(int i = 0; i < len; i++) {
        uint32_t timeout_counter = 0;

        while(!(u->ISR & (1 << 7))) {
            timeout_counter++;
            if(timeout_counter >= SEND_TIMEOUT) {
                return 1;
            }
        }
        u->TDR = msg[i];
    }

    return 0;
}

int print(char *msg) {
    for(int i = 0; i < MAX_PRINT_LENGTH; i++) {
        if(msg[i] == '\0') {
            return 0;
        }

        uint32_t timeout_counter = 0;

        while(!(PRINT_UART->ISR & (1 << 7))) {
            timeout_counter++;
            if(timeout_counter >= SEND_TIMEOUT) {
                return 1;
            }
        }
        PRINT_UART->TDR = msg[i];
    }

    return 0;
}

int getchar() {
    while(!(STLINK_UART->ISR & USART_ISR_RXNE)) {}
    STLINK_UART->RQR |= USART_RQR_RXFRQ;  // Example: Request a flush of the RX buffer (clears RXNE flag)
    return STLINK_UART->RDR - '0';
}