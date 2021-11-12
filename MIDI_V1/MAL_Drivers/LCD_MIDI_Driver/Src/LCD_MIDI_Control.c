/*
 * LCD_MIDI_Control.c
 *
 *  Created on: Feb 5, 2021
 *      Author: shin
 */

#include "main.h"
#include "LCD_MIDI.h"
#include "LCD_MIDI_Control.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

extern LCD_Handle_TypeDef hlcd;

void MAL_LCD_Set_EvLevel(uint8_t val) {
	if (val >= 64)
		val = 63;

	for (int i = 0; i < 8; i++)
	{
		hlcd.lcd[i].ev_level = val;
	}
}

void MAL_LCD_Set_AllOn(void) {
	for (int k = 0; k < 8; k++)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 128; j++)
			{
				hlcd.lcd[k].frame[i][j] = 0xff;
			}
		}
	}
}
void MAL_LCD_Set_Clear(void) {
	LCD_Pixel_wirte_logo(0, ' ');
	LCD_Pixel_wirte_logo(1, ' ');
	LCD_Pixel_wirte_logo(2, ' ');
	LCD_Pixel_wirte_logo(3, ' ');
	LCD_Pixel_wirte_logo(4, ' ');
	LCD_Pixel_wirte_logo(5, ' ');
	LCD_Pixel_wirte_logo(6, ' ');
	LCD_Pixel_wirte_logo(7, ' ');
}
void LCD_SetText_AXLENUM_DEC(uint8_t lcdNum, uint8_t group_num,uint8_t motor_num) {

	char temp[10] = { 0, };
	sprintf(temp, "%d-%d", (int) group_num,  (int) motor_num);

	uint8_t len = strlen(temp);

	for(int i = 0; i < 4; i++)
	{
		if(i < len)
			LCD_pixel_write_sizeA_p(lcdNum, temp[i], 10 + i);
		else
			LCD_pixel_write_sizeA_p(lcdNum, ' ', 10 + i);
	}
	//	char temp[10] = { 0, };
	//	sprintf(temp, "%d", (int) axleNum);
	//
	//	if (axleNum < 10)
	//	{
	//		LCD_pixel_write_sizeA_p(lcdNum, temp[0], 10);
	//		LCD_pixel_write_sizeA_p(lcdNum, ' ', 11);
	//	}
	//	else if (axleNum < 100)
	//	{
	//		LCD_pixel_write_sizeA_p(lcdNum, temp[0], 10);
	//		LCD_pixel_write_sizeA_p(lcdNum, temp[1], 11);
	//	}
}

void LCD_SetText_ADC_DEC(uint8_t lcdNum, uint32_t value) {

	char temp[10] = { 0, };
	sprintf(temp, "%d", (int) value);

	if (value < 10)
	{

		LCD_pixel_write_sizeA_p(lcdNum, ' ', 16);
		LCD_pixel_write_sizeA_p(lcdNum, ' ', 17);
		LCD_pixel_write_sizeA_p(lcdNum, ' ', 18);
		LCD_pixel_write_sizeA_p(lcdNum, temp[0], 19);
	}
	else if (value < 100)
	{

		LCD_pixel_write_sizeA_p(lcdNum, ' ', 16);
		LCD_pixel_write_sizeA_p(lcdNum, ' ', 17);
		LCD_pixel_write_sizeA_p(lcdNum, temp[0], 18);
		LCD_pixel_write_sizeA_p(lcdNum, temp[1], 19);

	}
	else if (value < 1000)
	{

		LCD_pixel_write_sizeA_p(lcdNum, ' ', 16);
		LCD_pixel_write_sizeA_p(lcdNum, temp[0], 17);
		LCD_pixel_write_sizeA_p(lcdNum, temp[1], 18);
		LCD_pixel_write_sizeA_p(lcdNum, temp[2], 19);

	}
	else if (value < 10000)
	{

		LCD_pixel_write_sizeA_p(lcdNum, temp[0], 16);
		LCD_pixel_write_sizeA_p(lcdNum, temp[1], 17);
		LCD_pixel_write_sizeA_p(lcdNum, temp[2], 18);
		LCD_pixel_write_sizeA_p(lcdNum, temp[3], 19);

	}
	else if (value < 100000)
	{

	}

	//자리수이동
#if 0
	if (value < 10)
	{
		digit = 1;
		LCD_pixel_write_sizeA_p(lcdNum, ' ', 15);
		LCD_pixel_write_sizeA_p(lcdNum, ' ', 16);
		LCD_pixel_write_sizeA_p(lcdNum, ' ', 17);
		LCD_pixel_write_sizeA_p(lcdNum, temp[0], 18);
	}
	else if (value < 100)
	{
		digit = 2;
		LCD_pixel_write_sizeA_p(lcdNum, ' ', 15);
		LCD_pixel_write_sizeA_p(lcdNum, ' ', 16);
		LCD_pixel_write_sizeA_p(lcdNum, temp[0], 17);
		LCD_pixel_write_sizeA_p(lcdNum, temp[1], 18);

	}
	else if (value < 1000)
	{
		digit = 3;
		LCD_pixel_write_sizeA_p(lcdNum, ' ', 15);
		LCD_pixel_write_sizeA_p(lcdNum, temp[0], 16);
		LCD_pixel_write_sizeA_p(lcdNum, temp[1], 17);
		LCD_pixel_write_sizeA_p(lcdNum, temp[2], 18);

	}
	else if (value < 10000)
	{
		digit = 4;
		LCD_pixel_write_sizeA_p(lcdNum, temp[0], 15);
		LCD_pixel_write_sizeA_p(lcdNum, temp[1], 16);
		LCD_pixel_write_sizeA_p(lcdNum, temp[2], 17);
		LCD_pixel_write_sizeA_p(lcdNum, temp[3], 18);

	}
	else if (value < 100000)
	{
		digit = 5;
	}

#endif
#if 0
	uint8_t digit = 0;
	uint32_t k = 0;
	char temp[10] = {0,};
	//char asciiDat[10] = {0,};

	uint32_t n;

	//자릿수 구하기.
	n = value;
	while (n != 0) {
		n = n / 10;
		++digit;
	}

	if(value == 0)
		digit = 1;

	k = 1;
	for(int i = 0; i < digit; i ++)
	{
		k*=10;
	}



	//공백 만들기
	switch(digit)
	{
		case 1://17,18,19
			LCD_pixel_write_sizeA_p(lcdNum, ' ', 18);
			LCD_pixel_write_sizeA_p(lcdNum, ' ', 17);
			LCD_pixel_write_sizeA_p(lcdNum, ' ', 16);
			break;
		case 2://17,18
			LCD_pixel_write_sizeA_p(lcdNum, ' ', 17);
			LCD_pixel_write_sizeA_p(lcdNum, ' ', 16);
			break;
		case 3://17
			LCD_pixel_write_sizeA_p(lcdNum, ' ', 16);
			break;
	}


	for(int j = 0 ; j <= digit ; j++)
	{
		LCD_pixel_write_sizeA_p(lcdNum, temp[digit-1-j], 19-j);
	}

#endif
	//LCD_pixel_write_sizeA_p(lcdNum, ascii, No)
}
