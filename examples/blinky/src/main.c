#include <stdint.h>
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32f7xx_hal_tim.h"
#include "stm32f722xx.h"

TIM_HandleTypeDef htim;

int main() {
    HAL_Init();

    htim.Instance = TIM2;
    htim.Channel = HAL_TIM_ACTIVE_CHANNEL_1;
    htim.Init.Prescaler = 999;
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim.Init.Period = 7199;
    htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim.Init.RepetitionCounter = 0;
    htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    HAL_TIM_Base_Init(&htim);

    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef g;
    g.Mode = GPIO_MODE_OUTPUT_PP;
    g.Pull = GPIO_NOPULL;
    g.Speed = GPIO_SPEED_LOW;
    g.Pin = GPIO_PIN_7;
    HAL_GPIO_Init(GPIOB, &g);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

    HAL_TIM_Base_Start_IT(&htim);

    while(1) {}

    return 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
}