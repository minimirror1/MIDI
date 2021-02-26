/*
 * LCD_MIDI_Control.c
 *
 *  Created on: Feb 5, 2021
 *      Author: shin
 */


#include "main.h"
#include "string.h"
#include "LCD_MIDI.h"
#include "LCD_MIDI_Control.h"




void LCD_control(uint8_t selNum, uint8_t cmd, uint8_t pdata)
{
	uint8_t data[150] = { 0, };

	// cmd
	data[0] = cmd;
	data[1] = LCDcontrolStart0;
	data[2] = LCDcontrolStart1;
	MAL_LCD_MIDI_AddQueue(selNum, 1, data, 3);

	MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);

	// data
	for (int i = 0; i < 128; i++)
		data[i] = pdata;

	data[128] = 0x00;

	MAL_LCD_MIDI_AddQueue(selNum, 0, data, 128);

	MAL_LCD_MIDI_SendTrigger();
}



void LCD_control2(uint8_t selNum, LCDtextData_typedef *LCDtext)
{
	uint8_t data[150] = { 0, };
  for (int j=1; j<8; j++)
  {
    // cmd
	data[0] = 0xb0+j;
	data[1] = LCDcontrolStart0;
	data[2] = LCDcontrolStart1;

	MAL_LCD_MIDI_AddQueue(selNum, 1, data, 3);

	MAL_LCD_MIDI_SendTrigger();
	HAL_Delay(1);

    for(int i=0; i<128;i++)
    {
    	data[i] = LCDtext->data[i][j];
    }

    if(j == 4)
    {
    	for(int kw = 0; kw < 128; kw++)
    	{
    		data[kw] = 0xff;
    	}
    }

	MAL_LCD_MIDI_AddQueue(selNum, 0, data, 128);

	MAL_LCD_MIDI_SendTrigger();

	memset(data, 0x00, 128);
    HAL_Delay(5);
  }
}




void MAL_LCD_InitNum(uint8_t selNum)
{
	uint8_t data[150] = { 0, };

	data[0] = CMD0_1;
	data[1] = CMD0_2;
	data[2] = CMD0_3;
	data[3] = CMD0_4;
	data[4] = CMD0_5;
	data[5] = CMD0_6;
	data[6] = CMD0_7;
	data[7] = CMD0_8;
	data[8] = CMD0_9;
	data[9] = CMD0_10;
	data[10] = CMD0_11;
	data[11] = CMD0_12;

	MAL_LCD_MIDI_AddQueue(selNum, 1, data, 12);

	MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);

	data[0] = 0x81;
	data[1] = 0x18;
	data[2] = 0xA6;
	data[3] = 0xE3;

	MAL_LCD_MIDI_AddQueue(selNum, 1, data, 4);

	MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);

	data[0] = 0x81;
	data[1] = 0x18;
	data[2] = 0xA6;

	MAL_LCD_MIDI_AddQueue(selNum, 1, data, 4);

	MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);
}
void MAL_LCD_InitSeq(void)
{
	for(int i = 0; i < 8; i++)
	{
		MAL_LCD_InitNum(i);
	}
}

void MAL_LCD_SetData(uint8_t selNum,uint8_t data)
{
	for (int i = 0; i < 8; i++) {
		LCD_control(selNum, 0xB0 + i,data);
		HAL_Delay(0);
	}

	//MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);
}

void MAL_LCD_Control_test(void)
{
	uint8_t data[150] = { 0,};

	data[0] = CMD0_1;
	data[1] = CMD0_2;
	data[2] = CMD0_3;
	data[3] = CMD0_4;
	data[4] = CMD0_5;
	data[5] = CMD0_6;
	data[6] = CMD0_7;
	data[7] = CMD0_8;
	data[8] = CMD0_9;
	data[9] = CMD0_10;
	data[10] = CMD0_11;
	data[11] = CMD0_12;

	MAL_LCD_MIDI_AddQueue(0,1, data, 12);

	MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);

	data[0] = 0x81;
	data[1] = 0x18;
	data[2] = 0xA6;
	data[3] = 0xE3;

	MAL_LCD_MIDI_AddQueue(0,1, data, 4);

	MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);




	data[0] = 0x81;
	data[1] = 0x18;
	data[2] = 0xA6;

	MAL_LCD_MIDI_AddQueue(0,1, data, 4);

	MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);


	   for (int i = 0; i < 8; i++) {
		LCD_control(0, 0xB0 + i, 0xf0);
		HAL_Delay(0);
	}

	//MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);



}


void MAL_LCD_Control_test2(uint8_t selNum)
{

	uint8_t data[150] = { 0,};

	data[0] = CMD0_1;
	data[1] = CMD0_2;
	data[2] = CMD0_3;
	data[3] = CMD0_4;
	data[4] = CMD0_5;
	data[5] = CMD0_6;
	data[6] = CMD0_7;
	data[7] = CMD0_8;
	data[8] = CMD0_9;
	data[9] = CMD0_10;
	data[10] = CMD0_11;
	data[11] = CMD0_12;

	MAL_LCD_MIDI_AddQueue(selNum,1, data, 12);

	MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);

	data[0] = 0x81;
	data[1] = 0x18;
	data[2] = 0xA6;
	data[3] = 0xE3;

	MAL_LCD_MIDI_AddQueue(selNum,1, data, 4);

	MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);




	data[0] = 0x81;
	data[1] = 0x18;
	data[2] = 0xA6;

	MAL_LCD_MIDI_AddQueue(selNum,1, data, 4);

	MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);


	   for (int i = 0; i < 8; i++) {
		LCD_control(selNum, 0xB0 + i, 0x10);
		HAL_Delay(0);
	}

	//MAL_LCD_MIDI_SendTrigger();

	HAL_Delay(1);



}
