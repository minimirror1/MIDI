/*
 * LCD_MIDI.c
 *
 *  Created on: Feb 5, 2021
 *      Author: shin
 */


#include "main.h"
#include "string.h"
#include "LCD_MIDI_Control.h"
#include "LCD_MIDI.h"



LCD_Handle_TypeDef	hlcd = {0,};
extern TIM_HandleTypeDef htim1;

/*
const uint8_t cmd_set_0[12]= {CMD0_1,CMD0_2,CMD0_3,CMD0_4,CMD0_5,CMD0_6,CMD0_7,CMD0_8,CMD0_9,CMD0_10,CMD0_11,CMD0_12};
const uint8_t cmd_set_1[4] = {CMD1_1,CMD1_a,CMD1_3,CMD1_4};
const uint8_t cmd_set_2[4] = {CMD1_1,CMD1_b,CMD1_3,CMD1_4};
*/

const uint8_t cmd_init[12] = {
LCD_CMD_RESET,
LCD_CMD_POWER_CTR,
LCD_CMD_REGULATION_RATIO,
LCD_CMD_BIAS_SEL,
LCD_CMD_X,
LCD_CMD_SET_PAGE_ADDR,
LCD_CMD_SEG_DIR,
LCD_CMD_ALL_PIXEL_ON,
LCD_CMD_INV_DISPLAY,
LCD_CMD_COM_DIR,
LCD_CMD_SET_START_LINE,
LCD_CMD_DISPLAY_ON
};

const uint8_t set_col[2] = {
		LCD_CMD_SET_COL_0_LSB,
		LCD_CMD_SET_COL_0_MSB
};

const uint8_t set_inv[2] = {
		LCD_CMD_INV_DISPLAY,
		LCD_CMD_NOP
};

const uint8_t cmd_set_0[12];
const uint8_t cmd_set_1[4];
const uint8_t cmd_set_2[4];


void MAL_LCD_Init(void)
{

	hlcd.htim = &htim1;
	//==============================================================
	//D0 ~ D7
	hlcd.pinout.ParaData.GPIO = LCD_DAT_0_GPIO_Port;
	hlcd.pinout.ParaData.mask = 0x00FF;
	hlcd.pinout.ParaData.shift = 0;

	//A0 ~ A2
	hlcd.pinout.ParaSel.GPIO = LCD_SEL_A0_GPIO_Port;
	hlcd.pinout.ParaSel.mask = 0x0700;
	hlcd.pinout.ParaData.shift = 8;

	//SEL_EN
	hlcd.pinout.LCD_SEL_EN.GPIO = LCD_SEL_EN_GPIO_Port;
	hlcd.pinout.LCD_SEL_EN.Pin = LCD_SEL_EN_Pin;

	//CLK
	hlcd.pinout.LCD_CLK.GPIO = LCD_CLK_GPIO_Port;
	hlcd.pinout.LCD_CLK.Pin = LCD_CLK_Pin;

	//CMD
	hlcd.pinout.LCD_CMD.GPIO = LCD_CMD_GPIO_Port;
	hlcd.pinout.LCD_CMD.Pin = LCD_CMD_Pin;

	//==============================================================

	hlcd.ctr.status = LCD_MIDI_STOP;
	hlcd.ctr.seq_num = 0;

	for(int i = 0; i < 8 ; i++)
	{
		hlcd.lcd[i].ev_level = 45;

		for(int k = 0; k < 8; k++)
		{
			for (int j = 0; j < 128; j++) {
				hlcd.lcd[i].frame[k][j] = 0x00;
			}
		}

/*		for (int j = 0; j < 128; j++) {
			hlcd.lcd[i].frame[0][j] = 0xFF;
		}*/
	}




	HAL_TIM_Base_Start_IT(hlcd.htim);


}

//=======================================================================
static inline void MAL_LCD_IoSetData(uint8_t data)
{
	uint32_t outTemp = hlcd.pinout.ParaData.GPIO->ODR;

	outTemp &= ~hlcd.pinout.ParaData.mask;
	outTemp |= data & hlcd.pinout.ParaData.mask;

	hlcd.pinout.ParaData.GPIO->ODR = outTemp;
}

uint8_t MAL_LCD_SendDataSequnce(uint8_t data)
{
	static uint8_t seq_num = 0;
	uint8_t ret = 0;

	switch(seq_num)
	{
	case 0:
		hlcd.pinout.LCD_CLK.GPIO->ODR |= hlcd.pinout.LCD_CLK.Pin;
		MAL_LCD_IoSetData(data);
		seq_num = 1;
		break;
	case 1:
		hlcd.pinout.LCD_CLK.GPIO->ODR &= ~hlcd.pinout.LCD_CLK.Pin;
		seq_num = 0;
		ret = 1;
		break;
	default :
		seq_num = 0;
		break;
	}


/*	switch(seq_num)
	{
	case 0:
		hlcd.pinout.LCD_CLK.GPIO->ODR &= ~hlcd.pinout.LCD_CLK.Pin;
		seq_num = 1;
		break;
	case 1:
		MAL_LCD_IoSetData(data);
		seq_num = 2;
		break;
	case 2:
		hlcd.pinout.LCD_CLK.GPIO->ODR |= hlcd.pinout.LCD_CLK.Pin;
		seq_num = 3;
		break;
	case 3:
		hlcd.pinout.LCD_CLK.GPIO->ODR &= ~hlcd.pinout.LCD_CLK.Pin;
		seq_num = 0;
		ret = 1;
		break;
	default :
		seq_num = 0;
		break;
	}*/
	return ret;
}
//------------------------------------------------------------------------------

static inline void MAL_LCD_Sel_Address(uint8_t selNum)
{
	uint32_t outTemp = hlcd.pinout.ParaSel.GPIO->ODR;

	outTemp &= ~hlcd.pinout.ParaSel.mask;
	outTemp |= (selNum << hlcd.pinout.ParaData.shift) & hlcd.pinout.ParaSel.mask;

	hlcd.pinout.ParaSel.GPIO->ODR = outTemp;
}

//==============================================================================

void MAL_LCD_CMD_Ctr(uint8_t cmd_mode)
{
	if(cmd_mode)
	{
		hlcd.pinout.LCD_CMD.GPIO->ODR &= ~hlcd.pinout.LCD_CMD.Pin;
	}
	else
	{
		hlcd.pinout.LCD_CMD.GPIO->ODR |= hlcd.pinout.LCD_CMD.Pin;
	}
}

void MAL_LCD_MIDI_TIM_Manager(void)
{
	switch (hlcd.ctr.seq_num) {
		//============================================================================================
	case 0:
		MAL_LCD_Sel_Address(hlcd.initLcdNum);
		MAL_LCD_CMD_Ctr(LCD_IO_CMD);
		hlcd.ctr.seq_num = 1;
		break;
	case 1:
		hlcd.pinout.LCD_SEL_EN.GPIO->ODR &= ~hlcd.pinout.LCD_SEL_EN.Pin;
		hlcd.ctr.seq_num = 2;
		break;

	case 2:

		if (MAL_LCD_SendDataSequnce(cmd_init[hlcd.lcd[hlcd.initLcdNum].send_cnt])) {
			hlcd.lcd[hlcd.initLcdNum].send_cnt++;
			if (hlcd.lcd[hlcd.initLcdNum].send_cnt >= 12) {
				hlcd.lcd[hlcd.initLcdNum].send_cnt = 0;
				hlcd.ctr.seq_num = 3;
			}
		}
		break;

		//밝기 제어
	case 3:
		if (MAL_LCD_SendDataSequnce(LCD_CMD_SET_EV)) {
			hlcd.lcd[hlcd.initLcdNum].ev_level &= LCD_CMD_SET_EV_VAL_MASK;
			hlcd.ctr.seq_num = 4;
		}
		break;

	case 4:

		if (MAL_LCD_SendDataSequnce(hlcd.lcd[hlcd.initLcdNum].ev_level)) {
				hlcd.ctr.seq_num = 5;
		}
		break;
		//====================
	case 5:
		if (MAL_LCD_SendDataSequnce(set_inv[hlcd.lcd[hlcd.initLcdNum].send_cnt])) {
			hlcd.lcd[hlcd.initLcdNum].send_cnt++;
			if (hlcd.lcd[hlcd.initLcdNum].send_cnt >= 2) {
				hlcd.lcd[hlcd.initLcdNum].send_cnt = 0;
				hlcd.ctr.seq_num = 6;
				hlcd.lcd[hlcd.initLcdNum].send_page = 0xB0;
				hlcd.lcd[hlcd.initLcdNum].send_page_num = 0;
			}
		}
		break;
	case 6:
		MAL_LCD_CMD_Ctr(LCD_IO_CMD);
		hlcd.ctr.seq_num = 7;
		break;

	case 7:

		if (MAL_LCD_SendDataSequnce(hlcd.lcd[hlcd.initLcdNum].send_page)) {
			hlcd.ctr.seq_num = 8;
			hlcd.lcd[hlcd.initLcdNum].send_cnt = 0;
		}
		break;

	case 8:
		if (MAL_LCD_SendDataSequnce(set_col[hlcd.lcd[hlcd.initLcdNum].send_cnt])) {
			hlcd.lcd[hlcd.initLcdNum].send_cnt++;
			if (hlcd.lcd[hlcd.initLcdNum].send_cnt >= 2) {
				hlcd.lcd[hlcd.initLcdNum].send_cnt = 0;
				hlcd.ctr.seq_num = 9;
			}
		}
		break;
	case 9:
		MAL_LCD_CMD_Ctr(LCD_IO_DATA);
		hlcd.ctr.seq_num = 10;
		break;

	case 10:


		if (MAL_LCD_SendDataSequnce(hlcd.lcd[hlcd.initLcdNum].frame[hlcd.lcd[hlcd.initLcdNum].send_page_num][hlcd.lcd[hlcd.initLcdNum].send_cnt])) {
			hlcd.lcd[hlcd.initLcdNum].send_cnt++;
			if (hlcd.lcd[hlcd.initLcdNum].send_cnt >= LCD_BUFF_SIZE) {
				hlcd.lcd[hlcd.initLcdNum].send_cnt = 0;

				hlcd.lcd[hlcd.initLcdNum].send_page++;
				hlcd.lcd[hlcd.initLcdNum].send_page_num++;

				if(hlcd.lcd[hlcd.initLcdNum].send_page_num >= LCD_PAGE_SIZE)
				{
					hlcd.lcd[hlcd.initLcdNum].send_page = 0xB0;
					hlcd.lcd[hlcd.initLcdNum].send_page_num = 0;
					hlcd.ctr.seq_num = 11;
				}
				else
				{
					hlcd.ctr.seq_num = 6;
				}
			}
		}
		break;

	case 11:

		hlcd.initLcdNum++;
		if(hlcd.initLcdNum >= 8)
		{
			hlcd.initLcdNum = 0;
		}

		hlcd.ctr.seq_num = 0;

		break;

	}

}




void MAL_LCD_MIDI_ALL_Init(void)
{
	switch (hlcd.ctr.seq_num) {
	//============================================================================================
	case 0:
		MAL_LCD_Sel_Address(hlcd.initLcdNum);
		MAL_LCD_CMD_Ctr(LCD_IO_CMD);
		hlcd.ctr.seq_num = 1;
		break;

	case 1:
		hlcd.pinout.LCD_SEL_EN.GPIO->ODR &= ~hlcd.pinout.LCD_SEL_EN.Pin;
		hlcd.ctr.seq_num = 2;
		break;

	case 2:

		if (MAL_LCD_SendDataSequnce(cmd_set_0[hlcd.lcd[hlcd.initLcdNum].send_cnt])) {
			hlcd.lcd[hlcd.initLcdNum].send_cnt++;
			if (hlcd.lcd[hlcd.initLcdNum].send_cnt > 12) {
				hlcd.lcd[hlcd.initLcdNum].send_cnt = 0;
				hlcd.ctr.seq_num = 3;
			}
		}
		break;

	case 3:
		hlcd.pinout.LCD_SEL_EN.GPIO->ODR |= hlcd.pinout.LCD_SEL_EN.Pin;
		hlcd.lcd[hlcd.initLcdNum].send_cnt = 0;
		hlcd.ctr.seq_num = 4;
		break;
	//============================================================================================
	case 4:
		MAL_LCD_Sel_Address(hlcd.initLcdNum);
		MAL_LCD_CMD_Ctr(LCD_IO_CMD);
		hlcd.ctr.seq_num = 5;
		break;

	case 5:
		hlcd.pinout.LCD_SEL_EN.GPIO->ODR &= ~hlcd.pinout.LCD_SEL_EN.Pin;
		hlcd.ctr.seq_num = 6;
		break;

	case 6:

		if (MAL_LCD_SendDataSequnce(cmd_set_1[hlcd.lcd[hlcd.initLcdNum].send_cnt])) {
			hlcd.lcd[hlcd.initLcdNum].send_cnt++;
			if (hlcd.lcd[hlcd.initLcdNum].send_cnt > 4) {
				hlcd.lcd[hlcd.initLcdNum].send_cnt = 0;
				hlcd.ctr.seq_num = 7;
			}
		}
		break;

	case 7:
		hlcd.pinout.LCD_SEL_EN.GPIO->ODR |= hlcd.pinout.LCD_SEL_EN.Pin;
		hlcd.lcd[hlcd.initLcdNum].send_cnt = 0;
		hlcd.ctr.seq_num = 8;
		break;
		//===================================================================================

	case 8:
		MAL_LCD_Sel_Address(hlcd.initLcdNum);
		MAL_LCD_CMD_Ctr(LCD_IO_CMD);
		hlcd.ctr.seq_num = 9;
		break;

	case 9:
		hlcd.pinout.LCD_SEL_EN.GPIO->ODR &= ~hlcd.pinout.LCD_SEL_EN.Pin;
		hlcd.ctr.seq_num = 10;
		break;

	case 10:

		if (MAL_LCD_SendDataSequnce(cmd_set_2[hlcd.lcd[hlcd.initLcdNum].send_cnt])) {
			hlcd.lcd[hlcd.initLcdNum].send_cnt++;
			if (hlcd.lcd[hlcd.initLcdNum].send_cnt > 4) {
				hlcd.lcd[hlcd.initLcdNum].send_cnt = 0;
				hlcd.ctr.seq_num = 11;
			}
		}
		break;

	case 11:
		hlcd.pinout.LCD_SEL_EN.GPIO->ODR |= hlcd.pinout.LCD_SEL_EN.Pin;
		hlcd.lcd[hlcd.initLcdNum].send_cnt = 0;
		hlcd.ctr.seq_num = 0;

		hlcd.initLcdNum++;

		if(hlcd.initLcdNum >= 8)
		{
			hlcd.f_init = 1;
			hlcd.initLcdNum = 0;

/*			hlcd.ctr.status = LCD_MIDI_STOP;
			HAL_TIM_Base_Stop_IT(hlcd.htim);	*/
		}
		break;
	}
}














