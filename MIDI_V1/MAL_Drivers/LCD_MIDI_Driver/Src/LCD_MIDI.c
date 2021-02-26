/*
 * LCD_MIDI.c
 *
 *  Created on: Feb 5, 2021
 *      Author: shin
 */


#include "main.h"
#include "string.h"
#include "LCD_MIDI.h"



LCD_Handle_TypeDef	hlcd;
extern TIM_HandleTypeDef htim1;


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


}

//=======================================================================
void MAL_LCD_IoSetData(uint8_t data)
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
	}
	return ret;
}
//------------------------------------------------------------------------------

void MAL_LCD_IoSetAddress(uint8_t selNum)
{
	uint32_t outTemp = hlcd.pinout.ParaSel.GPIO->ODR;

	outTemp &= ~hlcd.pinout.ParaSel.mask;
	outTemp |= (selNum << hlcd.pinout.ParaData.shift) & hlcd.pinout.ParaSel.mask;

	hlcd.pinout.ParaSel.GPIO->ODR = outTemp;
}

//==============================================================================
void MAL_LCD_Sel_Address(void)
{
	MAL_LCD_IoSetAddress(hlcd.buff.selNum);
}

void MAL_LCD_CMD_Ctr(void)
{
	if(hlcd.buff.cmd_en)
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


	switch(hlcd.ctr.seq_num)
	{
	case 0:
		MAL_LCD_Sel_Address();
		MAL_LCD_CMD_Ctr();
		hlcd.ctr.seq_num = 1;
		break;

	case 1:
		hlcd.pinout.LCD_SEL_EN.GPIO->ODR &= ~hlcd.pinout.LCD_SEL_EN.Pin;
		hlcd.ctr.seq_num = 2;
		break;

	case 2:

		if (MAL_LCD_SendDataSequnce(hlcd.buff.data[hlcd.buff.send_cnt]))
		{
			hlcd.buff.send_cnt++;
			if(hlcd.buff.send_cnt > hlcd.buff.send_size)
			{
				hlcd.buff.send_cnt = 0;
				hlcd.ctr.seq_num = 3;
			}
		}
		break;

	case 3:
		hlcd.pinout.LCD_SEL_EN.GPIO->ODR |= hlcd.pinout.LCD_SEL_EN.Pin;
		hlcd.buff.send_cnt = 0;
		hlcd.ctr.seq_num = 0;
		hlcd.ctr.status = LCD_MIDI_STOP;
		HAL_TIM_Base_Stop_IT(hlcd.htim);
		break;
	}

}



//=============================================================================



void MAL_LCD_MIDI_SendTrigger(void)
{
	if(hlcd.ctr.status != LCD_MIDI_STOP)
		return;


	hlcd.ctr.status = LCD_MIDI_RUN;
	hlcd.ctr.seq_num = 0;
	hlcd.buff.send_cnt = 0;

	HAL_TIM_Base_Start_IT(hlcd.htim);
}

uint8_t MAL_LCD_MIDI_AddQueue(uint8_t selNum, uint8_t cmd_en, uint8_t *data, uint8_t size)
{
	if(hlcd.ctr.status != LCD_MIDI_STOP)
		return HAL_BUSY;//

	hlcd.buff.selNum = selNum;
	hlcd.buff.cmd_en = cmd_en;
	hlcd.buff.send_size = size;

	if(size < LCD_BUFF_SIZE)
	{
		memcpy(hlcd.buff.data,data,size);
	}
	else
	{
		return HAL_ERROR;
	}
	return HAL_OK;//
}


//==============================================================================

void MAL_LCD_DATA_TEST(uint8_t value)
{
	uint32_t outTemp = hlcd.pinout.ParaData.GPIO->ODR;

	outTemp &= ~hlcd.pinout.ParaData.mask;
	outTemp |= value & hlcd.pinout.ParaData.mask;

	hlcd.pinout.ParaData.GPIO->ODR = outTemp;
}

void MAL_LCD_SEL_TEST(uint8_t value)
{
	uint32_t outTemp = hlcd.pinout.ParaSel.GPIO->ODR;

	outTemp &= ~hlcd.pinout.ParaSel.mask;
	outTemp |= (value << hlcd.pinout.ParaData.shift) & hlcd.pinout.ParaSel.mask;

	hlcd.pinout.ParaSel.GPIO->ODR = outTemp;


	if(value == 0x01)	//EN
		hlcd.pinout.LCD_SEL_EN.GPIO->ODR ^= hlcd.pinout.LCD_SEL_EN.Pin;
	else if(value == 0x02)//CD
		hlcd.pinout.LCD_CMD.GPIO->ODR ^= hlcd.pinout.LCD_CMD.Pin;
	else if(value == 0x04)//CLK
		hlcd.pinout.LCD_CLK.GPIO->ODR ^= hlcd.pinout.LCD_CLK.Pin;

}









