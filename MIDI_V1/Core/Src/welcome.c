/*
 * welcome.c
 *
 *  Created on: 2021. 3. 9.
 *      Author: shin
 */
#include "main.h"

#include "HC595_MIDI.h"
#include "HC595_MIDI_Control.h"

#include "HC165_MIDI.h"
#include "HC165_MIDI_wheel.h"

#include "X_Touch_Extender_ADC.h"
#include "X_Touch_Extender_MotorAdc_packet.h"
#include "LCD_MIDI.h"
#include "LCD_MIDI_Control.h"
#include "non_stop_delay_main.h"
#include "welcome.h"

uint8_t welcome_seq = 0;

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;
extern HC165_wheel_TypeDef wheel[8];
uint32_t t_bootmode;




void welcome_bl(void)
{
	static uint8_t f_new = 1;
	static uint8_t stop = 1;	//반복횟수
	static uint8_t on_seq = 0;	//켜짐유지 번호
	static uint8_t on_led = 0;	//시프트 번호

	if (stop) {
		if (f_new) {
			f_new = 0;
			on_led = 8;
		}
		on_led--;
		MAL_LED_BackLight_Control(on_led, LED_WHITE);
		MAL_LED_BackLight_Control(on_led + 1, LED_BLACK);

		MAL_LED_Button_Control(on_led, LED_REC,0);
		MAL_LED_Button_Control(on_led, LED_SOLO,0);
		MAL_LED_Button_Control(on_led, LED_MUTE,0);
		MAL_LED_Button_Control(on_led, LED_SELECT,0);

		MAL_LED_Button_Control(on_led+1, LED_REC, 1);
		MAL_LED_Button_Control(on_led+1, LED_SOLO, 1);
		MAL_LED_Button_Control(on_led+1, LED_MUTE, 1);
		MAL_LED_Button_Control(on_led+1, LED_SELECT, 1);


		if (on_seq == on_led) {
			on_seq++;
			f_new = 1;
		}
		if (on_seq == 8) {
			stop = 0;
		}
	}
}

void welcome_opening(void) {
	uint8_t f_sine[8] = {0,};
	uint8_t sine_cnt = 0;

	uint8_t sine_shift = 0;


	uint8_t w = 0;
	uint8_t w_tog = 0;



	MAL_LCD_Set_EvLevel(0);
	//MAL_LCD_Set_Clear();
	MAL_LCD_Set_AllOn();
	HAL_Delay(100);

	for (int i = 0; i < 8; i++) {
		MAL_LED_BackLight_Control(i, LED_BLACK);
		Slide_control(i, 0);
	}



	MAL_LED_Refresh();
	MAL_HC595_MIDI_SendTrigger();
	MAL_HC165_MIDI_ReadTrigger();

	HAL_Delay(100);

	for(int k = 0; k < 63 ; k++)
	{
		MAL_LCD_Set_EvLevel(k);

		for (int a = 0; a < 8; a++) {
			MAL_LED_BarGauge_Control(a, w);
			MAL_LED_Wheel_Control(a, w);
		}

		if(w_tog == 0)
		{
			w++;
			if (w > 13) {
				w_tog = 1;
			}
		}
		else if(w_tog == 1)
		{
			w--;
			if(w == 0)
			{
				w_tog = 2;
			}
		}

		//
		welcome_bl();

		MAL_LED_Refresh();
		MAL_HC595_MIDI_SendTrigger();
		MAL_HC165_MIDI_ReadTrigger();
		HAL_Delay(30);
	}

	for(int qq = 0; qq < 8; qq++)
	{
		LCD_Pixel_wirte_logo(qq,'/');
	}
	HAL_Delay(30);
	for (int k = 63; k > 45; k--) {
		MAL_LCD_Set_EvLevel(k);
		HAL_Delay(100);
	}




	for (int j = 0; j < 255; j++) {


		sine_cnt++;

		sine_shift = 0;

		if (extenderPacket.touch[0] == 0x00) {

			if (welcome_wave[sine_cnt] == 0x00) {
				f_sine[0] = 1;
				Slide_control(0, 0);
			}
			if(f_sine[0] == 0)
			{
				Slide_control(0, 16 * welcome_wave[sine_cnt]);
			}

			//LCD_SetText_DEC(0, 16 * welcome_wave[sine_cnt]);
		} else {
			//LCD_SetText_DEC(0, extenderPacket.adc[0]);
		}

		sine_shift = 20 + sine_cnt;
		if (extenderPacket.touch[1] == 0x00) {
			if (welcome_wave[sine_shift] == 0x00) {
				f_sine[1] = 1;
				Slide_control(1, 0);
			}
			if (f_sine[1] == 0) {
				Slide_control(1, 16 * welcome_wave[sine_shift]);
			}
			//LCD_SetText_DEC(1, 16 * welcome_wave[sine_shift]);
		} else {
			//LCD_SetText_DEC(1, extenderPacket.adc[1]);
		}

		sine_shift += 20;
		if (extenderPacket.touch[2] == 0x00) {
			if (welcome_wave[sine_shift] == 0x00) {
				f_sine[2] = 1;
				Slide_control(2, 0);
			}
			if (f_sine[2] == 0) {
				Slide_control(2, 16 * welcome_wave[sine_shift]);
			}
			//LCD_SetText_DEC(2, 16 * welcome_wave[sine_shift]);
		} else {
			//LCD_SetText_DEC(2, extenderPacket.adc[2]);
		}

		sine_shift += 20;
		if (extenderPacket.touch[3] == 0x00) {
			if (welcome_wave[sine_shift] == 0x00) {
				f_sine[3] = 1;
				Slide_control(3, 0);
			}
			if (f_sine[3] == 0) {
				Slide_control(3, 16 * welcome_wave[sine_shift]);
			}
			//LCD_SetText_DEC(3, 16 * welcome_wave[sine_shift]);
		} else {
			//LCD_SetText_DEC(3, extenderPacket.adc[3]);
		}

		sine_shift += 20;
		if (extenderPacket.touch[4] == 0x00) {
			if (welcome_wave[sine_shift] == 0x00) {
				f_sine[4] = 1;
				Slide_control(4, 0);
			}
			if (f_sine[4] == 0) {
				Slide_control(4, 16 * welcome_wave[sine_shift]);
			}
			//LCD_SetText_DEC(4, 16 * welcome_wave[sine_shift]);
		} else {
			//LCD_SetText_DEC(4, extenderPacket.adc[4]);
		}

		sine_shift += 20;
		if (extenderPacket.touch[5] == 0x00) {
			if (welcome_wave[sine_shift] == 0x00) {
				f_sine[5] = 1;
				Slide_control(5, 0);
			}
			if (f_sine[5] == 0) {
				Slide_control(5, 16 * welcome_wave[sine_shift]);
			}
			//LCD_SetText_DEC(5, 16 * welcome_wave[sine_shift]);
		} else {
			//LCD_SetText_DEC(5, extenderPacket.adc[5]);
		}

		sine_shift += 20;
		if (extenderPacket.touch[6] == 0x00) {
			if (welcome_wave[sine_shift] == 0x00) {
				f_sine[6] = 1;
				Slide_control(6, 0);
			}
			if (f_sine[6] == 0) {
				Slide_control(6, 16 * welcome_wave[sine_shift]);
			}
			//LCD_SetText_DEC(6, 16 * welcome_wave[sine_shift]);
		} else {
			//LCD_SetText_DEC(6, extenderPacket.adc[6]);
		}

		sine_shift += 20;
		if (extenderPacket.touch[7] == 0x00) {
			if (welcome_wave[sine_shift] == 0x00) {
				f_sine[7] = 1;
				Slide_control(7, 0);
			}
			if (f_sine[7] == 0) {
				Slide_control(7, 16 * welcome_wave[sine_shift]);
			}
			//LCD_SetText_DEC(7, 16 * welcome_wave[sine_shift]);
		} else {
			//LCD_SetText_DEC(7, extenderPacket.adc[7]);
		}

		HAL_Delay(10);
	}

	HAL_Delay(100);
	LCD_Pixel_wirte_logo(0, ' ');
	LCD_Pixel_wirte_logo(1, 'G');
	LCD_Pixel_wirte_logo(2, 'E');
	LCD_Pixel_wirte_logo(3, 'N');
	LCD_Pixel_wirte_logo(4, 'T');
	LCD_Pixel_wirte_logo(5, 'L');
	LCD_Pixel_wirte_logo(6, 'E');
	LCD_Pixel_wirte_logo(7, ' ');

	for(int w1 = 0; w1 < 8; w1++)
	{
		MAL_LED_Button_Control(w1, LED_REC, 1);
		MAL_LED_Button_Control(w1, LED_SOLO, 1);
	}

	MAL_LED_Refresh();
	MAL_HC595_MIDI_SendTrigger();
	MAL_HC165_MIDI_ReadTrigger();

	HAL_Delay(1000);
	LCD_Pixel_wirte_logo(0, 'M');
	LCD_Pixel_wirte_logo(1, 'O');
	LCD_Pixel_wirte_logo(2, 'N');
	LCD_Pixel_wirte_logo(3, 'S');
	LCD_Pixel_wirte_logo(4, 'T');
	LCD_Pixel_wirte_logo(5, 'E');
	LCD_Pixel_wirte_logo(6, 'R');
	LCD_Pixel_wirte_logo(7, ' ');

	for(int w1 = 0; w1 < 8; w1++)
	{
		MAL_LED_Button_Control(w1, LED_MUTE, 1);
		MAL_LED_Button_Control(w1, LED_SELECT, 1);
	}

	MAL_LED_Refresh();
	MAL_HC595_MIDI_SendTrigger();
	MAL_HC165_MIDI_ReadTrigger();

	HAL_Delay(1000);

	MAL_LCD_Set_Clear();

	welcome_seq = 1;

	t_bootmode = MAL_SysTimer_GetTickCount();

}
uint8_t evlevel = 30;
void welcome_setting(void)
{
	static uint32_t t_set;


	//기본메세지
	if (MAL_NonStopDelay(&t_set, 50))
	{
		LCD_pixel_write_sizeA_p(0, 'C', 1);
		LCD_pixel_write_sizeA_p(0, 'A', 2);
		LCD_pixel_write_sizeA_p(0, 'N', 3);
		LCD_pixel_write_sizeA_p(0, '_', 4);
		LCD_pixel_write_sizeA_p(0, 'I', 5);
		LCD_pixel_write_sizeA_p(0, 'D', 6);


		LCD_pixel_write_sizeA_p(7, 'L', 1);
		LCD_pixel_write_sizeA_p(7, 'C', 2);
		LCD_pixel_write_sizeA_p(7, 'D', 3);
		LCD_pixel_write_sizeA_p(7, '_', 4);
		LCD_pixel_write_sizeA_p(7, 'B', 5);
		LCD_pixel_write_sizeA_p(7, 'L', 6);

		MAL_LCD_Set_EvLevel(evlevel);
		LCD_SetText_DEC(7, evlevel);
	}

	//lcd back light
	if(wheel[7].status.f_rot == ROT_CW)
	{
		wheel[7].status.f_rot = ROT_CLEAR;
		evlevel++;
	}
	else if(wheel[7].status.f_rot == ROT_CCW)
	{
		wheel[7].status.f_rot = ROT_CLEAR;
		evlevel--;
	}



	if (wheel[7].status.btn == 1) {
		welcome_seq = 9;

		for(int i = 0; i < 8; i++)
		{
			wheel[i].status.wheelCnt = 0;
		}
		MAL_LCD_Set_Clear();
	}

}
void welcome_bootmode(void) {

	volatile uint8_t f_boot = 0;

	MAL_HC165_MIDI_ReadTrigger();

	if(wheel[0].status.btn == 1)
	{
		f_boot = 1;
	}

	if (MAL_NonStopDelay(&t_bootmode, 1000)) {

		switch(f_boot)
		{
		case 0:
			welcome_seq = 9;
			break;
		case 1:
			welcome_seq = 2;
			break;
		}

	}
}

void welcome(void) {
	uint32_t t_boot = 0;
	while (1) {
		switch (welcome_seq) {
		case 0:
			welcome_opening();
			break;
		case 1:
			welcome_bootmode();
			break;
		case 2:
			welcome_setting();
			break;
		case 9:
			return;
			break;
		}
		if (MAL_NonStopDelay(&t_boot, 50))
		{
			MAL_LED_Refresh();

		}
		MAL_HC595_MIDI_SendTrigger();
		MAL_HC165_MIDI_ReadTrigger();
	}
}