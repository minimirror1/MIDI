/*
 * LCD_MIDI_Control.c
 *
 *  Created on: Feb 5, 2021
 *      Author: shin
 */


#include "main.h"
#include "LCD_MIDI_Control.h"
#include "stdio.h"
#include "string.h"
#include "math.h"





void LCD_SetText_DEC(uint8_t lcdNum, uint32_t value)
{
	uint8_t digit = 0;
	uint32_t k = 0;
	char temp[10] = {0,};
	char asciiDat[10] = {0,};

	uint32_t n;

	//자릿수 구하기.
	n = value;
	while (n != 0) {
		n = n / 10;
		++digit;
	}

	k = 1;
	for(int i = 0; i < digit; i ++)
	{
		k*=10;
	}

	sprintf(temp, "%d", (int)value);

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

	//LCD_pixel_write_sizeA_p(lcdNum, ascii, No)
}
