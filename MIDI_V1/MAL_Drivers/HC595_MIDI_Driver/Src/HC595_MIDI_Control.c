/*
 * HC595_MIDI_Control.c
 *
 *  Created on: Feb 2, 2021
 *      Author: shin
 */

#include "main.h"
#include "HC595_MIDI.h"
#include "HC595_MIDI_Control.h"



HC595_LED_GroupTypeDef led_group[MIDI_LED_GROUP_COUNT] = {0,};

void MAL_LED_Control_Init(void)
{
	for(int i = 0; i < MIDI_LED_GROUP_COUNT ;  i++)
	{
		led_group[i].backLight.r = LED_OFF;
		led_group[i].backLight.g = LED_OFF;
		led_group[i].backLight.b = LED_OFF;

		led_group[i].button.rec = LED_OFF;
		led_group[i].button.solo = LED_OFF;
		led_group[i].button.mute = LED_OFF;
		led_group[i].button.select = LED_OFF;

		led_group[i].barGauge.value = 0;
	}
}


void MAL_LED_Wheel_Control(uint8_t ch, uint8_t value)
{
	if(ch >= MIDI_LED_GROUP_COUNT)
		return;

	if(value > 13)
		value = 13;

	led_group[ch].wheelGauge.value = value;
}


void MAL_LED_BackLight_Control(uint8_t ch, HC595_LED_BacklightTypeDef color )
{
	if(ch >= MIDI_LED_GROUP_COUNT)
			return;

	led_group[ch].backLight.color = color;

	switch (led_group[ch].backLight.color) {
	case LED_BLACK://R:X,G:X,B:X
		led_group[ch].backLight.r = LED_OFF;
		led_group[ch].backLight.g = LED_OFF;
		led_group[ch].backLight.b = LED_OFF;
		break;
	case LED_RED://R:O,G:X,B:X
		led_group[ch].backLight.r = LED_ON;
		led_group[ch].backLight.g = LED_OFF;
		led_group[ch].backLight.b = LED_OFF;
		break;
	case LED_GREEN://R:X,G:O,B:X
		led_group[ch].backLight.r = LED_OFF;
		led_group[ch].backLight.g = LED_ON;
		led_group[ch].backLight.b = LED_OFF;
		break;
	case LED_BLUE://R:X,G:X,B:O
		led_group[ch].backLight.r = LED_OFF;
		led_group[ch].backLight.g = LED_OFF;
		led_group[ch].backLight.b = LED_ON;
		break;
	case LED_MAGENTA://R:O,G:X,B:O
		led_group[ch].backLight.r = LED_ON;
		led_group[ch].backLight.g = LED_OFF;
		led_group[ch].backLight.b = LED_ON;
		break;
	case LED_YELLOW://R:O,G:O,B:X
		led_group[ch].backLight.r = LED_ON;
		led_group[ch].backLight.g = LED_ON;
		led_group[ch].backLight.b = LED_OFF;
		break;
	case LED_CYAN://R:X,G:O,B:O
		led_group[ch].backLight.r = LED_OFF;
		led_group[ch].backLight.g = LED_ON;
		led_group[ch].backLight.b = LED_ON;
		break;
	case LED_WHITE://R:O,G:O,B:O
		led_group[ch].backLight.r = LED_ON;
		led_group[ch].backLight.g = LED_ON;
		led_group[ch].backLight.b = LED_ON;
		break;
	}
}

void MAL_LED_BarGauge_Control(uint8_t ch, uint8_t value)
{
	if(ch >= MIDI_LED_GROUP_COUNT)
			return;

	if(value >= 8)
		value = 8;

	led_group[ch].barGauge.value = value;
}

void MAL_LED_Button_Control(uint8_t ch, HC595_LED_ButtonTypeDef btn, HC595_LED_StatusTypeDef status)
{
	if(ch >= MIDI_LED_GROUP_COUNT)
			return;

	switch(btn)
	{
	case LED_REC:
		led_group[ch].button.rec = status;
		break;

	case LED_SOLO:
		led_group[ch].button.solo = status;
		break;

	case LED_MUTE:
		led_group[ch].button.mute = status;
		break;

	case LED_SELECT:
		led_group[ch].button.select = status;
		break;
	}
}
//=================================================================================================

//void MAL_HC595_MIDI_Wheel_WritePin(uint32_t pinNum, GPIO_PinState PinStatus)
//void MAL_HC595_MIDI_Bar_WritePin(uint32_t pinNum, GPIO_PinState PinStatus)
//void MAL_HC595_MIDI_LCD_BTN_WritePin(uint32_t pinNum, GPIO_PinState PinStatus)//todo : lcd와 btn 분리  lcd는 색입력받게 분리


void MAL_LED_Wheel_Refresh(void)
{
	uint8_t gauge = 0;
	uint8_t calc_on_range_start;//시작
	uint8_t calc_on_range_end;//끝
	uint8_t calc_off_range_start;//시작
	uint8_t calc_off_range_end;//끝

	//todo :  입력할때 변환하는것으로 변경
	for(int i = 0; i < MIDI_LED_GROUP_COUNT ;  i++)
	{
		gauge = led_group[i].wheelGauge.value;

		calc_on_range_start = (HC595_WHEEL_IO_COUNT - 1) - (i * 13);	//104-1 번째부터 led상태를 채운다.
		calc_on_range_end = calc_on_range_start - (gauge - 1);

		//led on
		for(int j = calc_on_range_start; j >= calc_on_range_end; j-- )
		{
			MAL_HC595_MIDI_Wheel_WritePin(j,LED_ON);
		}

		//led off
		if(gauge < 13)
		{
			calc_off_range_start = calc_on_range_end - 1;
			calc_off_range_end = calc_on_range_start - (13 - 1);
			for (int k = calc_off_range_start; k >= calc_off_range_end; k--) {
				MAL_HC595_MIDI_Wheel_WritePin(k, LED_OFF);
			}
		}
	}
}


void MAL_LED_BackLight_Refresh(void)
{
	//uint32_t bl_endNum = 9;	// 9 ~ 32
	//uint32_t bl_startNum = 32;

	uint32_t bl_count = 31;
	for (int i = 0; i < MIDI_LED_GROUP_COUNT; i++) {
		MAL_HC595_MIDI_LCD_BTN_WritePin(bl_count, led_group[i].backLight.b);
		bl_count--;
		MAL_HC595_MIDI_LCD_BTN_WritePin(bl_count, led_group[i].backLight.g);
		bl_count--;
		MAL_HC595_MIDI_LCD_BTN_WritePin(bl_count, led_group[i].backLight.r);
		bl_count--;

	}
}


void MAL_LED_Button_Refresh(void)
{
	uint32_t btn_count = 63;
	for (int i = 0; i < MIDI_LED_GROUP_COUNT; i++) {
		MAL_HC595_MIDI_LCD_BTN_WritePin(btn_count, led_group[i].button.rec);
		btn_count--;
		MAL_HC595_MIDI_LCD_BTN_WritePin(btn_count, led_group[i].button.solo);
		btn_count--;
		MAL_HC595_MIDI_LCD_BTN_WritePin(btn_count, led_group[i].button.mute);
		btn_count--;
		MAL_HC595_MIDI_LCD_BTN_WritePin(btn_count, led_group[i].button.select);
		btn_count--;
	}
}

void MAL_LED_BarGauge_Refresh(void)
{
	uint8_t gauge = 0;
	uint8_t calc_on_range_start;	//시작
	uint8_t calc_on_range_end;	//끝
	uint8_t calc_off_range_start;	//시작
	uint8_t calc_off_range_end;	//끝

	//todo :  입력할때 변환하는것으로 변경
	for (int i = 0; i < MIDI_LED_GROUP_COUNT; i++) {
		gauge = 8 - led_group[i].barGauge.value; // 거꾸로 뺀다

		//=====
		calc_on_range_start = (HC595_BAR_IO_COUNT - 1) - (i * 8);	//104-1 번째부터 led상태를 채운다.
		calc_on_range_end = calc_on_range_start - (gauge - 1);

		//led on
		for(int j = calc_on_range_start; j >= calc_on_range_end; j-- )
		{
			MAL_HC595_MIDI_Bar_WritePin(j,LED_OFF);
		}

		//led off
		if(gauge < 8)
		{
			calc_off_range_start = calc_on_range_end - 1;
			calc_off_range_end = calc_on_range_start - (8 - 1);
			for (int k = calc_off_range_start; k >= calc_off_range_end; k--) {
				MAL_HC595_MIDI_Bar_WritePin(k, LED_ON);
			}
		}
	}
}



void MAL_LED_Refresh(void)
{
	MAL_LED_Wheel_Refresh();
	MAL_LED_BackLight_Refresh();
	MAL_LED_Button_Refresh();
	MAL_LED_BarGauge_Refresh();

}

//사용예시

#if 0


/*	  MAL_HC595_MIDI_Wheel_WritePin(test_cnt, GPIO_PIN_RESET);
	  MAL_HC595_MIDI_Bar_WritePin(test_cnt, GPIO_PIN_RESET);
	  MAL_HC595_MIDI_LCD_BTN_WritePin(test_cnt, GPIO_PIN_RESET);*/


/*	  MAL_LED_Wheel_Control(1,test_cnt1);

	  MAL_LED_Wheel_Control(2,test_cnt1);

	  MAL_LED_Wheel_Control(3,test_cnt1);

	  MAL_LED_Wheel_Control(4,test_cnt1);

	  MAL_LED_Wheel_Control(5,test_cnt1);

	  MAL_LED_Wheel_Control(6,test_cnt1);

	  MAL_LED_Wheel_Control(7,test_cnt1);

	  MAL_LED_Wheel_Control(8,test_cnt1);

	  test_cnt1++;
	  if(test_cnt1 >13)
		  test_cnt1 = 0;
		  */

	  MAL_LED_Wheel_Control(1,test_cnt1++);
	  if(test_cnt1 >8)
	  		  test_cnt1 = 0;

	  MAL_LED_Wheel_Control(2,test_cnt1++);
	  if(test_cnt1 >8)
	  		  test_cnt1 = 0;

	  MAL_LED_Wheel_Control(3,test_cnt1++);
	  if(test_cnt1 >8)
	  		  test_cnt1 = 0;

	  MAL_LED_Wheel_Control(4,test_cnt1++);
	  if(test_cnt1 >8)
	  		  test_cnt1 = 0;

	  MAL_LED_Wheel_Control(5,test_cnt1++);
	  if(test_cnt1 >8)
	  		  test_cnt1 = 0;

	  MAL_LED_Wheel_Control(6,test_cnt1++);
	  if(test_cnt1 >8)
	  		  test_cnt1 = 0;

	  MAL_LED_Wheel_Control(7,test_cnt1++);
	  if(test_cnt1 >8)
	  		  test_cnt1 = 0;

	  MAL_LED_Wheel_Control(8,test_cnt1++);

	  if(test_cnt1 >8)
		  test_cnt1 = 0;



		MAL_LED_BackLight_Control(1, LED_BLACK);
		MAL_LED_BackLight_Control(2, LED_RED);
		MAL_LED_BackLight_Control(3, LED_GREEN);
		MAL_LED_BackLight_Control(4, LED_BLUE);
		MAL_LED_BackLight_Control(5, LED_MAGENTA);
		MAL_LED_BackLight_Control(6, LED_YELLOW);
		MAL_LED_BackLight_Control(7, LED_CYAN);
		MAL_LED_BackLight_Control(8, LED_WHITE);

		MAL_LED_Button_Control(1, LED_REC, LED_ON);
		MAL_LED_Button_Control(2, LED_SOLO, LED_ON);
		MAL_LED_Button_Control(3, LED_MUTE, LED_ON);
		MAL_LED_Button_Control(4, LED_SELECT, LED_ON);

		MAL_LED_Button_Control(1, LED_SELECT, LED_ON);
		MAL_LED_Button_Control(2, LED_MUTE, LED_ON);
		MAL_LED_Button_Control(3, LED_SOLO, LED_ON);
		MAL_LED_Button_Control(4, LED_REC, LED_ON);

		MAL_LED_Button_Control(5, LED_REC, LED_ON);
		MAL_LED_Button_Control(6, LED_SOLO, LED_ON);
		MAL_LED_Button_Control(7, LED_MUTE, LED_ON);
		MAL_LED_Button_Control(8, LED_SELECT, LED_ON);

		MAL_LED_Button_Control(5, LED_SELECT, LED_ON);
		MAL_LED_Button_Control(6, LED_MUTE, LED_ON);
		MAL_LED_Button_Control(7, LED_SOLO, LED_ON);
		MAL_LED_Button_Control(8, LED_REC, LED_ON);



		MAL_LED_BarGauge_Control(1, test_cnt3++);
		if(test_cnt3 > 8)
				  test_cnt3 = 0;
		MAL_LED_BarGauge_Control(2, test_cnt3++);
		if(test_cnt3 > 8)
				  test_cnt3 = 0;
		MAL_LED_BarGauge_Control(3, test_cnt3++);
		if(test_cnt3 > 8)
				  test_cnt3 = 0;
		MAL_LED_BarGauge_Control(4, test_cnt3++);
		if(test_cnt3 > 8)
				  test_cnt3 = 0;
		MAL_LED_BarGauge_Control(5, test_cnt3++);
		if(test_cnt3 > 8)
				  test_cnt3 = 0;
		MAL_LED_BarGauge_Control(6, test_cnt3++);
		if(test_cnt3 > 8)
				  test_cnt3 = 0;
		MAL_LED_BarGauge_Control(7, test_cnt3++);
		if(test_cnt3 > 8)
				  test_cnt3 = 0;
		MAL_LED_BarGauge_Control(8, test_cnt3++);
		if(test_cnt3 > 8)
				  test_cnt3 = 0;
	 //MAL_HC595_MIDI_LCD_BTN_WritePin(31, 0);

	  MAL_LED_Refresh();

/*	  test_cnt1++;
	  if(test_cnt1 >13)
		  test_cnt1 = 0;*/

	  test_cnt2++;
	  if(test_cnt2 >13)
		  test_cnt2 = 0;


	  MAL_HC595_MIDI_SendTrigger();
	  HAL_Delay(100);
#endif












