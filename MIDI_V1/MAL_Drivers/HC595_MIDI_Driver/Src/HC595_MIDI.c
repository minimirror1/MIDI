/*
 * HC595_MIDI.c
 *
 *  Created on: Feb 2, 2021
 *      Author: shin
 */

#include "main.h"
#include "string.h"
#include "HC595_MIDI.h"

HC595_Wheel_ConfigTypeDef hc595_wheel = {0,};
HC595_BAR_LCD_BTN_ConfigTypeDef hc595_bar_lcd_btn = {0,};

extern TIM_HandleTypeDef htim3;



void MAL_HC595_MIDI_SendTrigger(void)
{
/*	if (hc595_wheel.send_status != HC595_MIDI_STOP)
		return;
	if (hc595_bar_lcd_btn.send_status != HC595_MIDI_STOP)
		return;*/

	hc595_wheel.io_count = 0;
	hc595_bar_lcd_btn.io_count = 0;

	hc595_wheel.clk_toggle = 1;
	hc595_bar_lcd_btn.clk_toggle = 1;

	hc595_wheel.send_status = HC595_MIDI_RUN;
	hc595_bar_lcd_btn.send_status = HC595_MIDI_RUN;

	hc595_wheel.send_seq = 0;
	hc595_bar_lcd_btn.send_seq = 0;


	//HAL_TIM_Base_Start_IT(hc595_wheel.htim);
	//HAL_TIM_Base_Start_IT(hc595_bar_lcd_btn.htim); //wheel과 같은 tim3
}

void MAL_HC595_MIDI_Wheel_WritePin(uint32_t pinNum, GPIO_PinState PinStatus)
{
	if(pinNum < HC595_WHEEL_IO_COUNT)
	{
		hc595_wheel.ioData[pinNum] = PinStatus;
	}
}

void MAL_HC595_MIDI_Bar_WritePin(uint32_t pinNum, GPIO_PinState PinStatus)
{
	if(pinNum < HC595_BAR_IO_COUNT)
	{
		hc595_bar_lcd_btn.ioData_bar[pinNum] = PinStatus;
	}
}


void MAL_HC595_MIDI_LCD_BTN_WritePin(uint32_t pinNum, GPIO_PinState PinStatus)//todo : lcd와 btn 분리  lcd는 색입력받게 분리
{
	if(pinNum < HC595_BAR_IO_COUNT)
	{
		hc595_bar_lcd_btn.ioData_lcdBtn[pinNum] = PinStatus;
	}
}

void MAL_HC595_MIDI_All_Off(void)
{
	//출력 초기화
	memset(hc595_wheel.ioData, 0x01,HC595_WHEEL_IO_COUNT);
	memset(hc595_bar_lcd_btn.ioData_bar, 0x01,HC595_BAR_IO_COUNT);	//LATCH CLK 공통으로 더 많은 쪽의 버퍼개수 사용
	memset(hc595_bar_lcd_btn.ioData_lcdBtn, 0x01,HC595_BAR_IO_COUNT);
}



//=============================================================================
//드라이버 함수

//HC595 초기화 : GPIO, timer 설정
void MAL_HC595_MIDI_Init(void)
{
	hc595_wheel.htim = &htim3;
	hc595_bar_lcd_btn.htim = &htim3;

	hc595_wheel.send_status = HC595_MIDI_STOP;
	hc595_bar_lcd_btn.send_status = HC595_MIDI_STOP;

	//HC595 wheel LED = 104개
	hc595_wheel.initIo_count = HC595_WHEEL_IO_COUNT;
	hc595_wheel.CLK_GPIO = HC595_WHEEL_CLK_GPIO_Port;
	hc595_wheel.CLK_GPIO_Pin = HC595_WHEEL_CLK_Pin;
	hc595_wheel.DATA_GPIO = HC595_WHEEL_DATA_GPIO_Port;
	hc595_wheel.DATA_GPIO_Pin = HC595_WHEEL_DATA_Pin;
	hc595_wheel.LATCH_GPIO = HC595_WHEEL_LATCH_GPIO_Port;
	hc595_wheel.LATCH_GPIO_Pin = HC595_WHEEL_LATCH_Pin;

	//HC595 bar, lcd_btn
	hc595_bar_lcd_btn.CLK_GPIO = HC595_COMMON_CLK_GPIO_Port;
	hc595_bar_lcd_btn.CLK_GPIO_Pin = HC595_COMMON_CLK_Pin;
	hc595_bar_lcd_btn.LATCH_GPIO = HC595_COMMON_LATCH_GPIO_Port;
	hc595_bar_lcd_btn.LATCH_GPIO_Pin = HC595_COMMON_LATCH_Pin;

	//HC595 lcd_btn = 56개
	hc595_bar_lcd_btn.bar_initIo_count = HC595_BAR_IO_COUNT;
	hc595_bar_lcd_btn.LCD_BTN_DATA_GPIO = HC595_LCD_BTN_DATA_GPIO_Port;
	hc595_bar_lcd_btn.LCD_BTN_DATA_GPIO_Pin = HC595_LCD_BTN_DATA_Pin;

	//HC595 bar, lcd_btn = 64개
	hc595_bar_lcd_btn.lcdbtn_initIo_count = HC595_LCD_BTN_IO_COUNT;
	hc595_bar_lcd_btn.BAR_DATA_GPIO = HC595_BAR_DATA_GPIO_Port;
	hc595_bar_lcd_btn.BAR_DATA_GPIO_Pin = HC595_BAR_DATA_Pin;

	//출력 초기화
	memset(hc595_wheel.ioData, 0x01,HC595_WHEEL_IO_COUNT);
	memset(hc595_bar_lcd_btn.ioData_bar, 0x01,HC595_BAR_IO_COUNT);	//LATCH CLK 공통으로 더 많은 쪽의 버퍼개수 사용
	memset(hc595_bar_lcd_btn.ioData_lcdBtn, 0x01,HC595_BAR_IO_COUNT);

	MAL_HC595_MIDI_SendTrigger();

	HAL_TIM_Base_Start_IT(&htim3);

}


void MAL_HC595_Wheel_Sequence(void)
{
	switch(hc595_wheel.send_seq){
		case 0:
			hc595_wheel.LATCH_GPIO->ODR &= ~hc595_wheel.LATCH_GPIO_Pin;
			hc595_wheel.send_seq = 1;
			break;

		case 1:
			hc595_wheel.LATCH_GPIO->ODR |= hc595_wheel.LATCH_GPIO_Pin;
			hc595_wheel.send_seq = 2;
			break;

		case 2:
			hc595_wheel.LATCH_GPIO->ODR &= ~hc595_wheel.LATCH_GPIO_Pin;
			hc595_wheel.send_seq = 3;
			break;

		case 3:
			if (hc595_wheel.clk_toggle) {
				hc595_wheel.clk_toggle = 0;

				hc595_wheel.CLK_GPIO->ODR &= ~hc595_wheel.CLK_GPIO_Pin;

				if (hc595_wheel.ioData[hc595_wheel.io_count]) {
					hc595_wheel.DATA_GPIO->ODR |= hc595_wheel.DATA_GPIO_Pin;
				} else {
					hc595_wheel.DATA_GPIO->ODR &= ~hc595_wheel.DATA_GPIO_Pin;
				}
			} else {
				hc595_wheel.clk_toggle = 1;

				hc595_wheel.CLK_GPIO->ODR |= hc595_wheel.CLK_GPIO_Pin;

				hc595_wheel.io_count++;
				if (hc595_wheel.io_count == HC595_WHEEL_IO_COUNT) {
					hc595_wheel.send_seq = 4;
				}
			}

			break;
		case 4:
			hc595_wheel.LATCH_GPIO->ODR &= ~hc595_wheel.LATCH_GPIO_Pin;
			hc595_wheel.CLK_GPIO->ODR &= ~hc595_wheel.CLK_GPIO_Pin;

			hc595_wheel.send_seq = 5;
			break;
		case 5:
			hc595_wheel.LATCH_GPIO->ODR |= hc595_wheel.LATCH_GPIO_Pin;
			hc595_wheel.send_seq = 6;
			break;
		case 6:
			hc595_wheel.LATCH_GPIO->ODR &= ~hc595_wheel.LATCH_GPIO_Pin;
			hc595_wheel.send_status = HC595_MIDI_STOP;
			hc595_wheel.send_seq = 7;
			//HAL_TIM_Base_Stop_IT(hc595_wheel.htim);
			break;

		default:
			break;
		}
}

void MAL_HC595_BAR_LCDBTN_Sequence(void)
{
	switch(hc595_bar_lcd_btn.send_seq){
		case 0:
			hc595_bar_lcd_btn.LATCH_GPIO->ODR &= ~hc595_bar_lcd_btn.LATCH_GPIO_Pin;
			hc595_bar_lcd_btn.send_seq = 1;
			break;

		case 1:
			hc595_bar_lcd_btn.LATCH_GPIO->ODR |= hc595_bar_lcd_btn.LATCH_GPIO_Pin;
			hc595_bar_lcd_btn.send_seq = 2;
			break;

		case 2:
			hc595_bar_lcd_btn.LATCH_GPIO->ODR &= ~hc595_bar_lcd_btn.LATCH_GPIO_Pin;
			hc595_bar_lcd_btn.send_seq = 3;
			break;

		case 3:
			if (hc595_bar_lcd_btn.clk_toggle) {
				hc595_bar_lcd_btn.clk_toggle = 0;

				hc595_bar_lcd_btn.CLK_GPIO->ODR &= ~hc595_bar_lcd_btn.CLK_GPIO_Pin;

				//bar data
				if (hc595_bar_lcd_btn.ioData_bar[hc595_bar_lcd_btn.io_count]) {
					hc595_bar_lcd_btn.BAR_DATA_GPIO->ODR |= hc595_bar_lcd_btn.BAR_DATA_GPIO_Pin;
				} else {
					hc595_bar_lcd_btn.BAR_DATA_GPIO->ODR &= ~hc595_bar_lcd_btn.BAR_DATA_GPIO_Pin;
				}

				//lcd_btn data
				if (hc595_bar_lcd_btn.ioData_lcdBtn[hc595_bar_lcd_btn.io_count]) {
					hc595_bar_lcd_btn.LCD_BTN_DATA_GPIO->ODR |= hc595_bar_lcd_btn.LCD_BTN_DATA_GPIO_Pin;
				} else {
					hc595_bar_lcd_btn.LCD_BTN_DATA_GPIO->ODR &= ~hc595_bar_lcd_btn.LCD_BTN_DATA_GPIO_Pin;
				}


			} else {
				hc595_bar_lcd_btn.clk_toggle = 1;

				hc595_bar_lcd_btn.CLK_GPIO->ODR |= hc595_bar_lcd_btn.CLK_GPIO_Pin;

				hc595_bar_lcd_btn.io_count++;
				if (hc595_bar_lcd_btn.io_count == HC595_BAR_IO_COUNT) {
					hc595_bar_lcd_btn.send_seq = 4;
				}
			}

			break;
		case 4:
			hc595_bar_lcd_btn.LATCH_GPIO->ODR &= ~hc595_bar_lcd_btn.LATCH_GPIO_Pin;
			hc595_bar_lcd_btn.CLK_GPIO->ODR &= ~hc595_bar_lcd_btn.CLK_GPIO_Pin;

			hc595_bar_lcd_btn.send_seq = 5;
			break;
		case 5:
			hc595_bar_lcd_btn.LATCH_GPIO->ODR |= hc595_bar_lcd_btn.LATCH_GPIO_Pin;
			hc595_bar_lcd_btn.send_seq = 6;
			break;
		case 6:
			hc595_bar_lcd_btn.LATCH_GPIO->ODR &= ~hc595_bar_lcd_btn.LATCH_GPIO_Pin;
			hc595_bar_lcd_btn.send_status = HC595_MIDI_STOP;
			hc595_bar_lcd_btn.send_seq = 7;
			//HAL_TIM_Base_Stop_IT(hc595_bar_lcd_btn.htim);
			break;
		default:
			break;

		}
}


void MAL_HC595_MIDI_TIM_Manager(void)
{
	MAL_HC595_Wheel_Sequence();
	MAL_HC595_BAR_LCDBTN_Sequence();

	if((hc595_wheel.send_status == HC595_MIDI_STOP)&&(hc595_bar_lcd_btn.send_status == HC595_MIDI_STOP))
		MAL_HC595_MIDI_SendTrigger();
}
