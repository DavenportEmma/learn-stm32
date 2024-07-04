#include <stdint.h>
#include "stm32f722xx.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"

int main() {
    HAL_Init();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef g;
    g.Mode = GPIO_MODE_OUTPUT_PP;
    g.Pull = GPIO_NOPULL;
    g.Speed = GPIO_SPEED_LOW;
    g.Pin = GPIO_PIN_7;
    HAL_NVIC_SetPriority(SysTick_IRQn,14,0);
    HAL_GPIO_Init(GPIOB, &g);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

    while(1) {
        HAL_Delay(1000);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
    }

    return 0;
}