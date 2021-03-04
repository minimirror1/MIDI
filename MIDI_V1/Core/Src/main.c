/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "HC595_MIDI.h"
#include "HC595_MIDI_Control.h"

#include "HC165_MIDI.h"

#include "X_Touch_Extender_MotorAdc_packet.h"
#include "LCD_MIDI.h"
#include "LCD_MIDI_Control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	switch((uint32_t)htim->Instance)
	{
	case (uint32_t)TIM3:
		MAL_HC595_MIDI_TIM_Manager();
		break;
	case (uint32_t)TIM4:
		MAL_HC165_MIDI_TIM_Manager();
		break;
/*	case (uint32_t)TIM1:
		MAL_LCD_MIDI_TIM_Manager();
		break;*/
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */


	HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  MAL_UART_Init();
  MAL_X_TouchExtender_Packet_Init();
  MAL_X_touch_test();

  MAL_HC595_MIDI_Init();
  MAL_LED_Control_Init();
    MAL_HC165_MIDI_Init();




  MAL_LCD_Init();


  //LCD_SetText_DEC(0,5);


/*
  LCD_Pixel_wirte_logo(0);
  LCD_Pixel_wirte_logo(1);
  LCD_Pixel_wirte_logo(2);
  LCD_Pixel_wirte_logo(3);
  LCD_Pixel_wirte_logo(4);
  LCD_Pixel_wirte_logo(5);
  LCD_Pixel_wirte_logo(6);
  LCD_Pixel_wirte_logo(7);
*/

/*  LCD_pixel_write_sizeA_p(1, 'G', 1);
  LCD_pixel_write_sizeA_p(1, 'E', 2);
  LCD_pixel_write_sizeA_p(1, 'N', 3);
  LCD_pixel_write_sizeA_p(1, 'T', 4);
  LCD_pixel_write_sizeA_p(1, 'L', 5);
  LCD_pixel_write_sizeA_p(1, 'E', 6);

  LCD_pixel_write_sizeA_p(2, 'M', 1);
   LCD_pixel_write_sizeA_p(2, 'O', 2);
   LCD_pixel_write_sizeA_p(2, 'N', 3);
   LCD_pixel_write_sizeA_p(2, 'S', 4);
   LCD_pixel_write_sizeA_p(2, 'T', 5);
   LCD_pixel_write_sizeA_p(2, 'E', 6);
   LCD_pixel_write_sizeA_p(2, 'R', 6);*/



/*   LCD_pixel_write_sizeA_p(5, 'K', 1);
    LCD_pixel_write_sizeA_p(5, 'i', 2);
    LCD_pixel_write_sizeA_p(5, 'm', 3);

    LCD_pixel_write_sizeA_p(5, 'H', 10);
    LCD_pixel_write_sizeA_p(5, 'y', 11);
    LCD_pixel_write_sizeA_p(5, 'u', 12);
    LCD_pixel_write_sizeA_p(5, 'n', 13);
    LCD_pixel_write_sizeA_p(5, 'j', 14);
    LCD_pixel_write_sizeA_p(5, 'u', 15);*/


    //LCD_pixel_write_sizeA_p(5, 0x50, 17);


  //  MAL_LCD_InitSeq();
/*
  uint8_t test_bit = 0x01;
  uint8_t test_bit2 = 0x01;


  for(int sk = 0; sk < 8; sk++)
  {
	  MAL_LCD_SetData(sk,0x00);
  }

  uint8_t toggle = 0;


  uint8_t testData=0x30;*/

 // LCD_control2(6,&LCDtext);

   //uint8_t toggle = 0;

  uint32_t val = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


/*	  LCD_SetText_DEC(0,val);
	  val++;

	  if(val > 4095)
		  val = 0;

	  HAL_Delay(100);*/

	  MAL_X_TouchExtender_ADC_Process();
/*
	  if(toggle)
	  {
		  toggle = 0;
	  LCD_pixel_write_sizeA_p(2, 'M', 1);
	   LCD_pixel_write_sizeA_p(2, 'O', 2);
	   LCD_pixel_write_sizeA_p(2, 'N', 3);
	   LCD_pixel_write_sizeA_p(2, 'S', 4);
	   LCD_pixel_write_sizeA_p(2, 'T', 5);
	   LCD_pixel_write_sizeA_p(2, 'E', 6);
	   LCD_pixel_write_sizeA_p(2, 'R', 6);

		  LCD_pixel_write_sizeA_p(3, ' ', 1);
	   LCD_pixel_write_sizeA_p(3, ' ', 2);
	   LCD_pixel_write_sizeA_p(3, ' ', 3);
	   LCD_pixel_write_sizeA_p(3, ' ', 4);
	   LCD_pixel_write_sizeA_p(3, ' ', 5);
	   LCD_pixel_write_sizeA_p(3, ' ', 6);
	   LCD_pixel_write_sizeA_p(3, ' ', 6);
	  }
	  else
	  {
		  toggle = 1;
		  LCD_pixel_write_sizeA_p(2, ' ', 1);
		   LCD_pixel_write_sizeA_p(2, ' ', 2);
		   LCD_pixel_write_sizeA_p(2, ' ', 3);
		   LCD_pixel_write_sizeA_p(2, ' ', 4);
		   LCD_pixel_write_sizeA_p(2, ' ', 5);
		   LCD_pixel_write_sizeA_p(2, ' ', 6);
		   LCD_pixel_write_sizeA_p(2, ' ', 6);


		  LCD_pixel_write_sizeA_p(3, 'M', 1);
	   LCD_pixel_write_sizeA_p(3, 'O', 2);
	   LCD_pixel_write_sizeA_p(3, 'N', 3);
	   LCD_pixel_write_sizeA_p(3, 'S', 4);
	   LCD_pixel_write_sizeA_p(3, 'T', 5);
	   LCD_pixel_write_sizeA_p(3, 'E', 6);
	   LCD_pixel_write_sizeA_p(3, 'R', 6);
	  }



	  MAL_LED_BackLight_Control(1, LED_WHITE);
	  MAL_LED_BackLight_Control(2, LED_WHITE);
	  MAL_LED_BackLight_Control(3, LED_WHITE);
	  MAL_LED_BackLight_Control(4, LED_WHITE);
	  MAL_LED_BackLight_Control(5, LED_WHITE);
	  MAL_LED_BackLight_Control(6, LED_WHITE);
	  MAL_LED_BackLight_Control(7, LED_WHITE);
	  MAL_LED_BackLight_Control(8, LED_WHITE);

		MAL_LED_Refresh();

		MAL_HC595_MIDI_SendTrigger();

	  HAL_Delay(100);

	  MAL_LED_Wheel_Control(1, test_cnt);

	  Slide_control(0, test_cnt*100);
	  MAL_LED_BackLight_Control(1, test_cnt);
	  MAL_LED_BarGauge_Control(1, test_cnt);
	  MAL_LED_Wheel_Control(1, test_cnt);
	  MAL_LED_Button_Control(1, test_cnt/2 , 0);
	  MAL_LED_Button_Control(5, test_cnt/2 , 0);

	  test_cnt++;
	  if(test_cnt > 8)
		  test_cnt = 0;

	  Slide_control(1, test_cnt*100);
	  MAL_LED_BackLight_Control(2, test_cnt);
	  MAL_LED_BarGauge_Control(2, test_cnt);
	  MAL_LED_Wheel_Control(2, test_cnt);
	  	  MAL_LED_Button_Control(2, test_cnt/2 , 0);
	  	MAL_LED_Button_Control(6, test_cnt/2 , 0);
	  test_cnt++;
	  	  if(test_cnt > 8)
	  		  test_cnt = 0;

	  Slide_control(2, test_cnt*100);
	  MAL_LED_BackLight_Control(3, test_cnt);
	  MAL_LED_BarGauge_Control(3, test_cnt);
	  MAL_LED_Wheel_Control(3, test_cnt);
	  	  MAL_LED_Button_Control(3, test_cnt/2 , 0);
	  	MAL_LED_Button_Control(7, test_cnt/2 , 0);
	  test_cnt++;
	  	  if(test_cnt > 8)
	  		  test_cnt = 0;

	  Slide_control(3, test_cnt*100);
	  MAL_LED_BackLight_Control(4, test_cnt);
	  MAL_LED_BarGauge_Control(4, test_cnt);
	  MAL_LED_Wheel_Control(4, test_cnt);
	  	  MAL_LED_Button_Control(4, test_cnt/2 , 0);
	  	MAL_LED_Button_Control(8, test_cnt/2 , 0);
	  test_cnt++;
	  	  if(test_cnt > 8)
	  		  test_cnt = 0;

	  Slide_control(4, test_cnt*100);
	  MAL_LED_BackLight_Control(5, test_cnt);
	  MAL_LED_BarGauge_Control(5, test_cnt);
	  MAL_LED_Wheel_Control(5, test_cnt);
	  	  MAL_LED_Button_Control(1, test_cnt/2 , 1);
	  	MAL_LED_Button_Control(5, test_cnt/2 , 1);
	  test_cnt++;
	  	  if(test_cnt > 8)
	  		  test_cnt = 0;

	  Slide_control(5, test_cnt*100);
	  MAL_LED_BackLight_Control(6, test_cnt);
	  MAL_LED_BarGauge_Control(6, test_cnt);
	  MAL_LED_Wheel_Control(6, test_cnt);
	  	  	  MAL_LED_Button_Control(2, test_cnt/2 , 1);
	  	  	MAL_LED_Button_Control(6, test_cnt/2 , 1);
	  test_cnt++;
	  	  if(test_cnt > 8)
	  		  test_cnt = 0;

	  Slide_control(6, test_cnt*100);
	  MAL_LED_BackLight_Control(7, test_cnt);
	  MAL_LED_BarGauge_Control(7, test_cnt);
	  MAL_LED_Wheel_Control(7, test_cnt);
	  	  	  MAL_LED_Button_Control(3, test_cnt/2 , 1);
	  	  	MAL_LED_Button_Control(7, test_cnt/2 , 1);
	  test_cnt++;
	  	  if(test_cnt > 8)
	  		  test_cnt = 0;

	  Slide_control(7, test_cnt*100);
	  MAL_LED_BackLight_Control(8, test_cnt);
	  MAL_LED_BarGauge_Control(8, test_cnt);
	  MAL_LED_Wheel_Control(8, test_cnt);
	  	  	  MAL_LED_Button_Control(4, test_cnt/2 , 1);
	  	  	MAL_LED_Button_Control(8, test_cnt/2 , 1);
	  test_cnt++;
	  	  if(test_cnt > 8)
	  		  test_cnt = 0;


	MAL_LED_Refresh();
	MAL_HC165_MIDI_ReadTrigger();
	MAL_HC595_MIDI_SendTrigger();
	HAL_Delay(40);*/

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the Systick interrupt time
  */
  __HAL_RCC_PLLI2S_ENABLE();
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 89;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1799;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
  //HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
  //HAL_TIM_Base_Start_IT(&htim3);
  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 1799;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LCD_DAT_2_Pin|LCD_DAT_3_Pin|LCD_DAT_4_Pin|LCD_DAT_5_Pin
                          |LCD_DAT_6_Pin|LCD_DAT_7_Pin|LCD_SEL_A0_Pin|LCD_SEL_A1_Pin
                          |LCD_SEL_A2_Pin|LCD_SEL_EN_Pin|LCD_CMD_Pin|LCD_CLK_Pin
                          |LCD_DAT_0_Pin|LCD_DAT_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, HC595_LCD_BTN_DATA_Pin|HC595_BAR_DATA_Pin|HC595_COMMON_CLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, HC595_COMMON_LATCH_Pin|HC595_WHEEL_DATA_Pin|HC595_WHEEL_LATCH_Pin|HC595_WHEEL_CLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(HC595_ALL_ENABLE_GPIO_Port, HC595_ALL_ENABLE_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, HC165_WHEEL_PL_Pin|HC165_WHEEL_CLK_Pin|HC165_BTN_PL_Pin|HC165_BTN_CLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD_DAT_2_Pin LCD_DAT_3_Pin LCD_DAT_4_Pin LCD_DAT_5_Pin
                           LCD_DAT_6_Pin LCD_DAT_7_Pin LCD_SEL_A0_Pin LCD_SEL_A1_Pin
                           LCD_SEL_A2_Pin LCD_SEL_EN_Pin LCD_CMD_Pin LCD_CLK_Pin
                           LCD_DAT_0_Pin LCD_DAT_1_Pin */
  GPIO_InitStruct.Pin = LCD_DAT_2_Pin|LCD_DAT_3_Pin|LCD_DAT_4_Pin|LCD_DAT_5_Pin
                          |LCD_DAT_6_Pin|LCD_DAT_7_Pin|LCD_SEL_A0_Pin|LCD_SEL_A1_Pin
                          |LCD_SEL_A2_Pin|LCD_SEL_EN_Pin|LCD_CMD_Pin|LCD_CLK_Pin
                          |LCD_DAT_0_Pin|LCD_DAT_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : HC595_LCD_BTN_DATA_Pin HC595_BAR_DATA_Pin HC595_COMMON_CLK_Pin HC595_ALL_ENABLE_Pin */
  GPIO_InitStruct.Pin = HC595_LCD_BTN_DATA_Pin|HC595_BAR_DATA_Pin|HC595_COMMON_CLK_Pin|HC595_ALL_ENABLE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : HC595_COMMON_LATCH_Pin HC595_WHEEL_DATA_Pin HC595_WHEEL_LATCH_Pin HC595_WHEEL_CLK_Pin */
  GPIO_InitStruct.Pin = HC595_COMMON_LATCH_Pin|HC595_WHEEL_DATA_Pin|HC595_WHEEL_LATCH_Pin|HC595_WHEEL_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : HC165_WHEEL_PL_Pin HC165_WHEEL_CLK_Pin HC165_BTN_PL_Pin HC165_BTN_CLK_Pin */
  GPIO_InitStruct.Pin = HC165_WHEEL_PL_Pin|HC165_WHEEL_CLK_Pin|HC165_BTN_PL_Pin|HC165_BTN_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : HC165_WHEEL_DATA_Pin HC165_BTN_DATA_Pin */
  GPIO_InitStruct.Pin = HC165_WHEEL_DATA_Pin|HC165_BTN_DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
