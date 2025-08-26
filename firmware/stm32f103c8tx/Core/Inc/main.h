/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_utils.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin LL_GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define PIN_A_ADC_Pin LL_GPIO_PIN_0
#define PIN_A_ADC_GPIO_Port GPIOA
#define PIN_B_ADC_Pin LL_GPIO_PIN_1
#define PIN_B_ADC_GPIO_Port GPIOA
#define PIN_C_ADC_Pin LL_GPIO_PIN_2
#define PIN_C_ADC_GPIO_Port GPIOA
#define PIN_A_0Ohm_Pin LL_GPIO_PIN_3
#define PIN_A_0Ohm_GPIO_Port GPIOA
#define PIN_A_680Ohms_Pin LL_GPIO_PIN_4
#define PIN_A_680Ohms_GPIO_Port GPIOA
#define PIN_A_470kOhms_Pin LL_GPIO_PIN_5
#define PIN_A_470kOhms_GPIO_Port GPIOA
#define PIN_B_0Ohm_Pin LL_GPIO_PIN_6
#define PIN_B_0Ohm_GPIO_Port GPIOA
#define PIN_B_680Ohms_Pin LL_GPIO_PIN_7
#define PIN_B_680Ohms_GPIO_Port GPIOA
#define PIN_B_470kOhms_Pin LL_GPIO_PIN_0
#define PIN_B_470kOhms_GPIO_Port GPIOB
#define PIN_C_0Ohm_Pin LL_GPIO_PIN_1
#define PIN_C_0Ohm_GPIO_Port GPIOB
#define PIN_C_680Ohms_Pin LL_GPIO_PIN_2
#define PIN_C_680Ohms_GPIO_Port GPIOB
#define PIN_C_470kOhms_Pin LL_GPIO_PIN_10
#define PIN_C_470kOhms_GPIO_Port GPIOB
#define LED_Transistor_Pin LL_GPIO_PIN_12
#define LED_Transistor_GPIO_Port GPIOB
#define LED_Diode_Pin LL_GPIO_PIN_13
#define LED_Diode_GPIO_Port GPIOB
#define LED_Capacitor_Pin LL_GPIO_PIN_14
#define LED_Capacitor_GPIO_Port GPIOB
#define LED_Resistor_Pin LL_GPIO_PIN_15
#define LED_Resistor_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif  // MAIN_H
