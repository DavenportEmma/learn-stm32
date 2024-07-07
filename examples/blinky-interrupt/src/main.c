#include <stdint.h>
#include "stm32f7xx_hal_def.h"
#include "stm32f7xx_hal_cortex.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal_conf.h"
#include "stm32f722xx.h"
#include "stm32f7xx_hal_dma.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32f7xx_hal_rcc_ex.h"
#include "stm32f7xx_hal_tim.h"
#include "stm32f7xx_hal_flash_ex.h"
#define LED_PIN GPIO_PIN_7
#define LED_PORT GPIOB

TIM_HandleTypeDef htim;
TIM_ClockConfigTypeDef sClockSourceConfig;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*);

void main(void) {
    HAL_StatusTypeDef h = HAL_Init();
    SystemClock_Config();
    HAL_TIM_Base_MspInit(&htim);
    __HAL_RCC_TIM2_CLK_ENABLE();

    htim.Instance = TIM2;
    htim.Init.Prescaler = 14399;
    htim.Init.Period = 4999;
    htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim.Init.RepetitionCounter = 0;
    htim.State;
    htim.Init.AutoReloadPreload = 0xFFFF;

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_NONINVERTED;
    sClockSourceConfig.ClockPrescaler = TIM_ETRPRESCALER_DIV1;
    sClockSourceConfig.ClockFilter = 0x0;

    HAL_TIM_ConfigClockSource(&htim, &sClockSourceConfig);
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
    h = HAL_TIM_Base_Init(&htim);
    HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);
    TIM2->SR &= !TIM_SR_UIF;
    // __HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
    __HAL_TIM_ENABLE(&htim);
    // h = HAL_TIM_Base_Start_IT(&htim);
    // htim.State = HAL_TIM_STATE_BUSY;
    // __HAL_TIM_ENABLE_IT(&htim, TIM_IT_UPDATE);
    // __HAL_TIM_ENABLE(&htim);
    // hal tim base start it is fucked here is my own implementation
    pTIM_CallbackTypeDef(*HAL_TIM_PeriodElapsedCallback_ptr)(TIM_HandleTypeDef) = &HAL_TIM_PeriodElapsedCallback;
    h = HAL_TIM_RegisterCallback(&htim, HAL_TIM_PERIOD_ELAPSED_CB_ID, HAL_TIM_PeriodElapsedCallback_ptr);

    while(1) {
      int a = 1;
      int b = 2;
      int c = a+b;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    int i = 1;
}

void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;
    
    /* Enable HSE Oscillator and activate PLL with HSE as source
    Note: Since there is no oscillator on board, HSE clock is derived from STLink */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSEState = RCC_HSE_OFF;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 432;  
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 9;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        while(1) {};
    }
    
    /* Activate the OverDrive to reach the 216 Mhz Frequency */
    if(HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        while(1) {};
    }
    
    
    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
      clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
    {
        while(1) {};
    }
}

// void SystemClock_Config(void)
// {
//     RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//     RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//     RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

//     // Configure the main internal regulator output voltage
//     __HAL_RCC_PWR_CLK_ENABLE();
//     __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

//     // Initializes the HSE Oscillator and activates PLL with HSE as source
//     RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//     RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//     RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//     RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//     RCC_OscInitStruct.PLL.PLLM = 8;
//     RCC_OscInitStruct.PLL.PLLN = 432;
//     RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
//     RCC_OscInitStruct.PLL.PLLQ = 9;
//     if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//     {
//         // Initialization Error
//         while(1);
//     }

//     // Activate the OverDrive to reach the 216 MHz Frequency
//     if (HAL_PWREx_EnableOverDrive() != HAL_OK)
//     {
//         // Initialization Error
//         while(1);
//     }

//     // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
//     RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
//     RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//     RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//     RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
//     RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

//     if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
//     {
//         // Initialization Error
//         while(1);
//     }

//     // Configure the peripheral clock for timers, etc.
//     PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_TIM;
//     PeriphClkInitStruct.TimPresSelection = RCC_TIMPRES_ACTIVATED;

//     if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
//     {
//         // Initialization Error
//         while(1);
//     }
// }