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

//#define FW_VER_STR "0.0.1v"	//초기버전
//#define FW_VER_STR "0.0.2v"	//필터 감도 변경
//#define FW_VER_STR "0.0.3v"	//버전표시, 슬라이드 범위, 슬라이드 맵핑
//#define FW_VER_STR "0.0.4v"	//장치설정 아이디 슬롯 8->2 로 변경, 범위설정시 휠 버튼으로 모터 위치 동기화
//#define FW_VER_STR "0.0.5v"		//4094 슬라이드 미동작 수정
#define FW_VER_STR "0.0.6v" 	//todo : 활성시 2씩 감소하는 현상 수정. 활성후 첫 슬라이드 위치가 받은 위치에서 +/- 200일때 통신 시작.
//#define FW_VER_STR "0.0.7v" //todo : CAN 아이디 별 데이터 구분, 필터 활성,비활성, //링크 활성 비활성

#define ADC_SHIFT 19

#define TEST_OUT_MIN 4095
#define TEST_OUT_MAX 0

//MASTER CAN ID
#define MASTER_CAN_ID 0

/*************?��?��?�� RAM버퍼?�� ?��?�� ?��?��******************/
#define CAN_Q_BUFF_SIZE 	512   //  ((?��?�� 4 Byte + ?��?��?�� 8 Byte) x 512(CAN_Q_BUFF_SIZE)) x 2(rx,tx) = 12,288 Byte
// CAN 1개일 경우
#define CAN_1	0 // ?��?���? ?��?��?�� define
#define CAN_CNT 1
/*
// CAN 2개일 경우
#define CAN_1	0 // ?��?���? ?��?��?�� define
#define CAN_2	1
#define CAN_CNT 2
*/

/*************?��?��?�� RAM버퍼?�� ?��?�� ?��?��******************/

#include "dl_can.h"
#include "net_phd_pid.h"
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
#define LCD_DAT_2_Pin GPIO_PIN_2
#define LCD_DAT_2_GPIO_Port GPIOE
#define LCD_DAT_3_Pin GPIO_PIN_3
#define LCD_DAT_3_GPIO_Port GPIOE
#define LCD_DAT_4_Pin GPIO_PIN_4
#define LCD_DAT_4_GPIO_Port GPIOE
#define LCD_DAT_5_Pin GPIO_PIN_5
#define LCD_DAT_5_GPIO_Port GPIOE
#define LCD_DAT_6_Pin GPIO_PIN_6
#define LCD_DAT_6_GPIO_Port GPIOE
#define HC595_LCD_BTN_DATA_Pin GPIO_PIN_4
#define HC595_LCD_BTN_DATA_GPIO_Port GPIOA
#define HC595_BAR_DATA_Pin GPIO_PIN_5
#define HC595_BAR_DATA_GPIO_Port GPIOA
#define HC595_COMMON_CLK_Pin GPIO_PIN_7
#define HC595_COMMON_CLK_GPIO_Port GPIOA
#define HC595_COMMON_LATCH_Pin GPIO_PIN_5
#define HC595_COMMON_LATCH_GPIO_Port GPIOC
#define LCD_DAT_7_Pin GPIO_PIN_7
#define LCD_DAT_7_GPIO_Port GPIOE
#define LCD_SEL_A0_Pin GPIO_PIN_8
#define LCD_SEL_A0_GPIO_Port GPIOE
#define LCD_SEL_A1_Pin GPIO_PIN_9
#define LCD_SEL_A1_GPIO_Port GPIOE
#define LCD_SEL_A2_Pin GPIO_PIN_10
#define LCD_SEL_A2_GPIO_Port GPIOE
#define LCD_SEL_EN_Pin GPIO_PIN_11
#define LCD_SEL_EN_GPIO_Port GPIOE
#define LCD_CMD_Pin GPIO_PIN_13
#define LCD_CMD_GPIO_Port GPIOE
#define LCD_CLK_Pin GPIO_PIN_14
#define LCD_CLK_GPIO_Port GPIOE
#define HC595_WHEEL_DATA_Pin GPIO_PIN_7
#define HC595_WHEEL_DATA_GPIO_Port GPIOC
#define HC595_WHEEL_LATCH_Pin GPIO_PIN_8
#define HC595_WHEEL_LATCH_GPIO_Port GPIOC
#define HC595_WHEEL_CLK_Pin GPIO_PIN_9
#define HC595_WHEEL_CLK_GPIO_Port GPIOC
#define HC595_ALL_ENABLE_Pin GPIO_PIN_10
#define HC595_ALL_ENABLE_GPIO_Port GPIOA
#define HC165_WHEEL_PL_Pin GPIO_PIN_0
#define HC165_WHEEL_PL_GPIO_Port GPIOD
#define HC165_WHEEL_CLK_Pin GPIO_PIN_1
#define HC165_WHEEL_CLK_GPIO_Port GPIOD
#define HC165_WHEEL_DATA_Pin GPIO_PIN_3
#define HC165_WHEEL_DATA_GPIO_Port GPIOD
#define HC165_BTN_PL_Pin GPIO_PIN_4
#define HC165_BTN_PL_GPIO_Port GPIOD
#define HC165_BTN_CLK_Pin GPIO_PIN_5
#define HC165_BTN_CLK_GPIO_Port GPIOD
#define HC165_BTN_DATA_Pin GPIO_PIN_7
#define HC165_BTN_DATA_GPIO_Port GPIOD
#define LCD_DAT_0_Pin GPIO_PIN_0
#define LCD_DAT_0_GPIO_Port GPIOE
#define LCD_DAT_1_Pin GPIO_PIN_1
#define LCD_DAT_1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
