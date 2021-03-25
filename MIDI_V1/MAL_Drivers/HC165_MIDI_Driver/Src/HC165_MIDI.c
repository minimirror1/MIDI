/*
 * HC165_MIDI.c
 *
 *  Created on: Feb 2, 2021
 *      Author: shin
 */

#include "main.h"
#include "string.h"
#include "HC165_MIDI.h"
#include "HC165_MIDI_wheel.h"

/*HC165_WHEEL_ConfigTypeDef	hc165_wheel = {0,};
 HC165_BUTTON_ConfigTypeDef	hc165_button = {0,};*/
HC165_ConfigTypeDef hc165_wheel = { 0, };
HC165_ConfigTypeDef hc165_button = { 0, };
uint8_t wheelIoData[HC165_WHEEL_IOCOUNT+1] = { 0, };
uint8_t buttonIoData[HC165_BUTTON_IOCOUNT+1] = { 0, };

extern TIM_HandleTypeDef htim4;

void MAL_HC165_MIDI_ReadTrigger(void)
{
	if (hc165_wheel.read_status != HC165_MIDI_STOP)
		return;
	if (hc165_button.read_status != HC165_MIDI_STOP)
		return;

	hc165_wheel.io_count = 0;
	hc165_button.io_count = 0;

	hc165_wheel.clk_toggle = 1;
	hc165_button.clk_toggle = 1;

	hc165_wheel.read_status = HC165_MIDI_RUN;
	hc165_button.read_status = HC165_MIDI_RUN;

	hc165_wheel.send_seq = 0;
	hc165_button.send_seq = 0;


	HAL_TIM_Base_Start_IT(hc165_wheel.htim);


	//HAL_TIM_Base_Start_IT(hc165_button.htim); //wheel과 같은 tim4

/*	if (hc165_button.read_status != HC165_MIDI_STOP)
		return;

	hc165_button.io_count = 0;

	hc165_button.clk_toggle = 1;

	hc165_button.read_status = HC165_MIDI_RUN;

	hc165_button.send_seq = 0;

	HAL_TIM_Base_Start_IT(hc165_button.htim);*/
}

void MAL_HC165_MIDI_Init(void) {
	//===================wheel
	hc165_wheel.htim = &htim4;
	//-----------
	hc165_wheel.CLK_GPIO = 		HC165_WHEEL_CLK_GPIO_Port;
	hc165_wheel.CLK_GPIO_Pin = 	HC165_WHEEL_CLK_Pin;

	hc165_wheel.DATA_GPIO = 	HC165_WHEEL_DATA_GPIO_Port;
	hc165_wheel.DATA_GPIO_Pin = HC165_WHEEL_DATA_Pin;

	hc165_wheel.PL_GPIO = 		HC165_WHEEL_PL_GPIO_Port;
	hc165_wheel.PL_GPIO_Pin = 	HC165_WHEEL_PL_Pin;
	//-----------
	hc165_wheel.initIo_count = HC165_WHEEL_IOCOUNT;
	hc165_wheel.io_count = 0;
	hc165_wheel.read_status = HC165_MIDI_STOP;
	hc165_wheel.send_seq = 0;
	hc165_wheel.clk_toggle = 1;
	hc165_wheel.ioData = &wheelIoData[0];


	HC165_MIDI_wheel_Mapping();
	//memset(hc165_wheel.ioData,0x00,HC165_WHEEL_IOCOUNT);

	//===================button
	hc165_button.htim = &htim4;
	//-----------
	hc165_button.CLK_GPIO = 		HC165_BTN_CLK_GPIO_Port;
	hc165_button.CLK_GPIO_Pin = 	HC165_BTN_CLK_Pin;

	hc165_button.DATA_GPIO = 		HC165_BTN_DATA_GPIO_Port;
	hc165_button.DATA_GPIO_Pin = 	HC165_BTN_DATA_Pin;

	hc165_button.PL_GPIO = 			HC165_BTN_PL_GPIO_Port;
	hc165_button.PL_GPIO_Pin = 		HC165_BTN_PL_Pin;
	//-----------
	hc165_button.initIo_count = HC165_BUTTON_IOCOUNT;
	hc165_button.io_count = 0;
	hc165_button.read_status = HC165_MIDI_STOP;
	hc165_button.send_seq = 0;
	hc165_button.clk_toggle = 1;
	hc165_button.ioData = &buttonIoData[0];

	HC165_MIDI_btn_Mapping();


	//memset(hc165_button.ioData, 0x00, HC165_BUTTON_IOCOUNT);
}

void MAL_HC165_Sequence_btn(HC165_ConfigTypeDef *hc165_handle) {
	switch (hc165_handle->send_seq) {
	case 0:
		hc165_handle->CLK_GPIO->ODR &= ~hc165_handle->CLK_GPIO_Pin;
		hc165_handle->PL_GPIO->ODR |= hc165_handle->PL_GPIO_Pin;
		hc165_handle->send_seq = 1;
		break;

	case 1:
		hc165_handle->PL_GPIO->ODR &= ~hc165_handle->PL_GPIO_Pin;
		hc165_handle->send_seq = 2;
		break;

	case 2:
		hc165_handle->PL_GPIO->ODR |= hc165_handle->PL_GPIO_Pin;

		hc165_handle->send_seq = 3;
		break;
	case 3:
		hc165_handle->io_count = 0;
		if ((hc165_handle->DATA_GPIO->IDR & hc165_handle->DATA_GPIO_Pin)!= (uint32_t) GPIO_PIN_RESET) {
			hc165_handle->ioData[0] = 1;
		} else {
			hc165_handle->ioData[0] = 0;
		}
		hc165_handle->io_count++;
		hc165_handle->send_seq = 4;

		break;

	case 4:

		if (hc165_handle->clk_toggle) {
			hc165_handle->clk_toggle = 0;

			hc165_handle->CLK_GPIO->ODR |= hc165_handle->CLK_GPIO_Pin;

		} else {
			hc165_handle->clk_toggle = 1;
			hc165_handle->CLK_GPIO->ODR &= ~hc165_handle->CLK_GPIO_Pin;

			if ((hc165_handle->DATA_GPIO->IDR & hc165_handle->DATA_GPIO_Pin)!= (uint32_t) GPIO_PIN_RESET) {
				hc165_handle->ioData[hc165_handle->io_count] = 1;
			} else {
				hc165_handle->ioData[hc165_handle->io_count] = 0;
			}
			hc165_handle->io_count++;
			if (hc165_handle->io_count >= hc165_handle->initIo_count) {
				hc165_handle->io_count = 0;
				hc165_handle->send_seq = 5;
			}
		}

		break;
	case 5:
		hc165_handle->PL_GPIO->ODR |= hc165_handle->PL_GPIO_Pin;
		hc165_handle->CLK_GPIO->ODR &= ~hc165_handle->CLK_GPIO_Pin;
		HC165_MIDI_btn_EventProcses();
		hc165_handle->read_status = HC165_MIDI_STOP;
		hc165_handle->send_seq = 6;
		break;
	default:
		break;
	}
}

void MAL_HC165_Sequence_wheel(HC165_ConfigTypeDef *hc165_handle) {
	switch (hc165_handle->send_seq) {
	case 0:
		hc165_handle->CLK_GPIO->ODR &= ~hc165_handle->CLK_GPIO_Pin;
		hc165_handle->PL_GPIO->ODR |= hc165_handle->PL_GPIO_Pin;
		hc165_handle->send_seq = 1;
		break;

	case 1:
		hc165_handle->PL_GPIO->ODR &= ~hc165_handle->PL_GPIO_Pin;
		hc165_handle->send_seq = 2;
		break;

	case 2:
		hc165_handle->PL_GPIO->ODR |= hc165_handle->PL_GPIO_Pin;

		hc165_handle->send_seq = 3;
		break;
	case 3:
		hc165_handle->io_count = 0;
		if ((hc165_handle->DATA_GPIO->IDR & hc165_handle->DATA_GPIO_Pin)!= (uint32_t) GPIO_PIN_RESET) {
			hc165_handle->ioData[0] = 1;
		} else {
			hc165_handle->ioData[0] = 0;
		}
		hc165_handle->io_count++;
		hc165_handle->send_seq = 4;

		break;

	case 4:

		if (hc165_handle->clk_toggle) {
			hc165_handle->clk_toggle = 0;

			hc165_handle->CLK_GPIO->ODR |= hc165_handle->CLK_GPIO_Pin;

		} else {
			hc165_handle->clk_toggle = 1;
			hc165_handle->CLK_GPIO->ODR &= ~hc165_handle->CLK_GPIO_Pin;

			if ((hc165_handle->DATA_GPIO->IDR & hc165_handle->DATA_GPIO_Pin)!= (uint32_t) GPIO_PIN_RESET) {
				hc165_handle->ioData[hc165_handle->io_count] = 1;
			} else {
				hc165_handle->ioData[hc165_handle->io_count] = 0;
			}
			hc165_handle->io_count++;
			if (hc165_handle->io_count >= hc165_handle->initIo_count) {
				hc165_handle->io_count = 0;
				hc165_handle->send_seq = 5;
			}
		}

		break;
	case 5:
		hc165_handle->PL_GPIO->ODR |= hc165_handle->PL_GPIO_Pin;
		hc165_handle->CLK_GPIO->ODR &= ~hc165_handle->CLK_GPIO_Pin;
		HC165_MIDI_wheel_EventProcses();
		hc165_handle->read_status = HC165_MIDI_STOP;
		hc165_handle->send_seq = 6;
		break;
	default:
		break;
	}
}

void MAL_HC165_MIDI_TIM_Manager(void) {

	MAL_HC165_Sequence_btn(&hc165_button);
	MAL_HC165_Sequence_wheel(&hc165_wheel);


	if((hc165_wheel.read_status == HC165_MIDI_STOP)&&(hc165_button.read_status == HC165_MIDI_STOP))
	{
		HAL_TIM_Base_Stop_IT(hc165_button.htim);
	}

/*	MAL_HC165_Sequence(&hc165_button);

	if(hc165_button.read_status == HC165_MIDI_STOP)
	{
		HAL_TIM_Base_Stop_IT(hc165_button.htim);
	}*/

}
