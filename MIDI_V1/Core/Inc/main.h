/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

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
#define HC595_BTN_DATA_Pin GPIO_PIN_5
#define HC595_BTN_DATA_GPIO_Port GPIOA
#define HC595_BTN_LATCH_Pin GPIO_PIN_10
#define HC595_BTN_LATCH_GPIO_Port GPIOD
#define HC595_BTN_CLK_Pin GPIO_PIN_12
#define HC595_BTN_CLK_GPIO_Port GPIOD
#define HC595_WHEEL_DATA_Pin GPIO_PIN_7
#define HC595_WHEEL_DATA_GPIO_Port GPIOC
#define HC595_WHEEL_LATCH_Pin GPIO_PIN_8
#define HC595_WHEEL_LATCH_GPIO_Port GPIOC
#define HC595_WHEEL_CLK_Pin GPIO_PIN_9
#define HC595_WHEEL_CLK_GPIO_Port GPIOC
#define HC595_ENABLE_Pin GPIO_PIN_10
#define HC595_ENABLE_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
