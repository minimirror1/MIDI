/*
 * view_2_settingMenu.c
 *
 *  Created on: 2021. 3. 29.
 *      Author: shin
 */


#include "main.h"

#include "HC595_MIDI.h"
#include "HC595_MIDI_Control.h"

#include "HC165_MIDI.h"
#include "HC165_MIDI_wheel.h"
#include "HC165_MIDI_btn.h"

#include "X_Touch_Extender_ADC.h"
#include "X_Touch_Extender_MotorAdc_packet.h"
#include "LCD_MIDI.h"
#include "LCD_MIDI_Control.h"
#include "non_stop_delay_main.h"

#include "panel_manager.h"
#include "panel_view.h"
#include "panel_control.h"
#include "panel_page.h"
#include "panel_slide.h"

#include "long_key.h"


extern LongKey_TypeDef LongKeyWheel[8];
extern uint8_t f_v0_first;

uint8_t MenuSelect(void)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		if(LongKeyWheel[i].fPress == 1)
			return i;
	}
	return 0xff;
}
void View_2_SettingMenu(void)
{
	static uint8_t f_toggle = 1;
	static uint8_t f_release = 0;
	static uint8_t toggleLed = 0;
	static uint32_t t_SetLed;

	if (f_toggle == 1)
	{
		f_toggle = 0;
		f_v0_first = 1; //view 0  초기값

		LCD_Write_String(0, 1, "Axle", sizeof("Axle"));
		LCD_Write_String(0, 2, "Change", sizeof("Change"));

		LCD_Write_String(1, 1, "Page", sizeof("Page"));
		LCD_Write_String(1, 2, "Change", sizeof("Change"));

		LCD_Write_String(2, 1, "Slide", sizeof("Slide"));
		LCD_Write_String(2, 2, "Setting", sizeof("Setting"));

		LCD_Write_String(7, 1, "Device", sizeof("Device"));
		LCD_Write_String(7, 2, "Setting", sizeof("Setting"));


	}

	if (LongKeyWheel[7].fLongKey == 0)
	{
		f_release = 1;
	}

	if(f_release)
	{
		switch (MenuSelect())
		{
			case 0:
				View_Changer(VIEW_3_AXLE_CHANGE);
				f_toggle = 1;
				f_release = 0;
				break;
			case 1:
				View_Changer(VIEW_4_PAGE_CHANGE);
				f_toggle = 1;
				f_release = 0;
				break;
			case 2:
				View_Changer(VIEW_6_SLIDE_SETTING);
				f_toggle = 1;
				f_release = 0;
				break;
			case 3:
				f_toggle = 1;
				f_release = 0;
				break;
			case 4:
				f_toggle = 1;
				f_release = 0;
				break;
			case 5:
				f_toggle = 1;
				f_release = 0;
				break;
			case 6:
				f_toggle = 1;
				f_release = 0;
				break;
			case 7:
				View_Changer(VIEW_5_DEVICE_SETTING);
				f_toggle = 1;
				f_release = 0;
				break;
			default:

				break;
		}
	}

	if(MAL_NonStopDelay(&t_SetLed, 500) == 1)
	{
		toggleLed ^= 1;
		if(toggleLed == 1)
		{
			MAL_LED_Wheel_Control(0, 13);
			MAL_LED_Wheel_Control(1, 13);
			MAL_LED_Wheel_Control(2, 13);
			MAL_LED_Wheel_Control(7, 13);
		}
		else
		{
			MAL_LED_Wheel_Control(0, 0);
			MAL_LED_Wheel_Control(1, 0);
			MAL_LED_Wheel_Control(2, 0);
			MAL_LED_Wheel_Control(7, 0);
		}

	}
}
