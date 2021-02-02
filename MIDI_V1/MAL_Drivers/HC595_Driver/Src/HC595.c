/*
 * HC595.c
 *
 *  Created on: Feb 1, 2021
 *      Author: shin
 */

#include "main.h"
#include "HC595.h"


HC595_ManagerTypeDef HC595_Manager = {0,};

void MAL_HC595_Init(HC595_HandleTypeDef *HC595,	HC595_ConfigTypeDef *sConfig)
{
	HC595_Manager.HC595[HC595_Manager.handle_cnt] = HC595;
	HC595_Manager.handle_cnt++;

	HC595->config.htim = sConfig->htim;
	HC595->config.io_count = sConfig->io_count;

	HC595->config.CLK_GPIO = sConfig->CLK_GPIO;
	HC595->config.CLK_GPIO_Pin = sConfig->CLK_GPIO_Pin;

	HC595->config.DATA_GPIO= sConfig->DATA_GPIO;
	HC595->config.DATA_GPIO_Pin = sConfig->DATA_GPIO_Pin;

	HC595->config.LATCH_GPIO = sConfig->LATCH_GPIO;
	HC595->config.LATCH_GPIO_Pin = sConfig->LATCH_GPIO_Pin;

	for(int i = 0; i < HC595->config.io_count ; i++)
	{
		HC595->control.io_data[i] = sConfig->gpio_default_out;
	}
}

void MAL_HC595_SendTrigger(HC595_HandleTypeDef *HC595)
{
	if (HC595->control.send_status == HC595_RUN) {
		return;
	}

	HC595->config.LATCH_GPIO->ODR &= ~HC595->config.LATCH_GPIO_Pin;
	HC595->config.CLK_GPIO->ODR &= ~HC595->config.CLK_GPIO_Pin;
	HC595->config.DATA_GPIO->ODR &= ~HC595->config.DATA_GPIO_Pin;

	HC595->control.io_count = 0;
	HC595->control.clk_toggle = 1;
	HC595->control.send_status = HC595_STOP;
	HC595->control.send_seq = 0;
	HAL_TIM_Base_Start_IT(HC595->config.htim);
}

void MAL_HC595_WritePin(HC595_HandleTypeDef *HC595, uint32_t pinNum, GPIO_PinState PinStatus)
{
	if(pinNum < MAX_HC595_IO_CNT)
	{
		HC595->control.io_data[pinNum] = PinStatus;
	}
}

void MAL_HC595_Sequence(HC595_HandleTypeDef *HC595)
{
	switch(HC595->control.send_seq){
		case 0:
			HC595->config.LATCH_GPIO->ODR &= ~HC595->config.LATCH_GPIO_Pin;
			HC595->control.send_seq = 1;
			break;

		case 1:
			HC595->config.LATCH_GPIO->ODR |= HC595->config.LATCH_GPIO_Pin;
			HC595->control.send_seq = 2;
			break;

		case 2:
			HC595->config.LATCH_GPIO->ODR &= ~HC595->config.LATCH_GPIO_Pin;
			HC595->control.send_seq = 3;
			break;

		case 3:
			if (HC595->control.clk_toggle) {
				HC595->control.clk_toggle = 0;

				HC595->config.CLK_GPIO->ODR &= ~HC595->config.CLK_GPIO_Pin;

				if (HC595->control.io_data[HC595->control.io_count]) {
					HC595->config.DATA_GPIO->ODR |= HC595->config.DATA_GPIO_Pin;
				} else {
					HC595->config.DATA_GPIO->ODR &= ~HC595->config.DATA_GPIO_Pin;
				}
			} else {
				HC595->control.clk_toggle = 1;

				HC595->config.CLK_GPIO->ODR |= HC595->config.CLK_GPIO_Pin;

				HC595->control.io_count++;
				if (HC595->control.io_count == HC595->config.io_count) {
					HC595->control.send_seq = 4;
				}
			}

			break;
		case 4:
			HC595->config.LATCH_GPIO->ODR &= ~HC595->config.LATCH_GPIO_Pin;
			HC595->config.CLK_GPIO->ODR &= ~HC595->config.CLK_GPIO_Pin;

			HC595->control.send_seq = 5;
			break;
		case 5:
			HC595->config.LATCH_GPIO->ODR |= HC595->config.LATCH_GPIO_Pin;
			HC595->control.send_seq = 6;
			break;
		case 6:
			HC595->config.LATCH_GPIO->ODR &= ~HC595->config.LATCH_GPIO_Pin;
			HC595->control.send_status = HC595_STOP;
			HAL_TIM_Base_Stop_IT(HC595->config.htim);
			break;

		}
}

void MAL_HC595_TIM_Manager(void)
{
	for(int i = 0; i < HC595_Manager.handle_cnt ; i++)
	{
		MAL_HC595_Sequence(HC595_Manager.HC595[i]);
	}
}

/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	MAL_HC595_TIM_Manager();
}*/
