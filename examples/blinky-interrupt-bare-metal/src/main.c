#include <stdint.h>
#include "stm32f7xx_hal_def.h"
#include "stm32f7xx_hal_cortex.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal_conf.h"
#include "stm32f722xx.h"
#include "stm32f7xx_hal_tim.h"

TIM_HandleTypeDef htim;

#define RCC_BASE      0x40023800
#define RCC_APB1ENR   (*(volatile uint32_t *)(RCC_BASE + 0x40))
#define TIM2EN        (1 << 0)

#define TIM2_BASE     0x40000000
#define TIM2_CR1      (*(volatile uint32_t *)(TIM2_BASE + 0x00))
#define TIM2_DIER     (*(volatile uint32_t *)(TIM2_BASE + 0x0C))
#define TIM2_SR       (*(volatile uint32_t *)(TIM2_BASE + 0x10))
#define TIM2_EGR      (*(volatile uint32_t *)(TIM2_BASE + 0x14))
#define TIM2_CCMR1    (*(volatile uint32_t *)(TIM2_BASE + 0x18))
#define TIM2_CCER     (*(volatile uint32_t *)(TIM2_BASE + 0x20))
#define TIM2_CNT      (*(volatile uint32_t *)(TIM2_BASE + 0x24))
#define TIM2_PSC      (*(volatile uint32_t *)(TIM2_BASE + 0x28))
#define TIM2_ARR      (*(volatile uint32_t *)(TIM2_BASE + 0x2C))
#define TIM2_CCR1     (*(volatile uint32_t *)(TIM2_BASE + 0x34))

#define NVIC_ISER0    (*(volatile uint32_t *)0xE000E100)
#define TIM2_IRQn     28

void TIM2_IRQHandler(void);

int main(void) {
    // Enable the TIM2 clock
    RCC_APB1ENR |= TIM2EN;

    // Set prescaler to divide the timer clock
    TIM2_PSC = 16000 - 1;  // Assuming a 16 MHz clock, this sets the timer clock to 1 kHz

    // Set auto-reload value for a desired period
    TIM2_ARR = 1000 - 1;  // This sets the timer period to 1 second

    // Set the output compare value
    TIM2_CCR1 = 500;  // This sets the compare value to trigger an interrupt at 0.5 seconds

    // Configure the output compare mode
    TIM2_CCMR1 &= ~(0xFF);
    TIM2_CCMR1 |= (0x30);  // Set to toggle mode on compare match

    // Enable the capture/compare channel
    TIM2_CCER |= 1;

    // Enable the update interrupt
    TIM2_DIER |= 1 << 1;  // Enable CC1 interrupt

    // Enable the TIM2 interrupt in the NVIC
    NVIC_ISER0 |= (1 << TIM2_IRQn);

    // Start the timer
    TIM2_CR1 |= 1;  // Enable the timer

    while (1) {
        // Main loop
    }
}

void TIM2_IRQHandler(void) {
    if (TIM2_SR & (1 << 1)) {  // Check if CC1 interrupt flag is set
        TIM2_SR &= ~(1 << 1);  // Clear the interrupt flag

        // Your interrupt handling code here
    }
}