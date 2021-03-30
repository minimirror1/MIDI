/*
 * view_1_settingPreview.c
 *
 *  Created on: 2021. 3. 25.
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

#include "long_key.h"

extern LongKey_TypeDef LongKeyWheel[8];

void View_1_SettingPreview(void) {
	static uint8_t f_toggle = 1;

	if (f_toggle == 1)
	{
		f_toggle = 0;

		LCD_Write_String(0, 1, "Setting", sizeof("Setting"));
		LCD_Write_String(0, 2, "Menu", sizeof("Menu"));


	}

	if (LongKeyWheel[0].fLongKey)
	{
		if (LongKeyWheel[0].PressTime < 700)
		{
			MAL_LED_BarGauge_Control(0, 2);
			LCD_pixel_write_sizeA_p(0, '.', 15);
		}
		else if (LongKeyWheel[0].PressTime < 1000)
		{
			MAL_LED_BarGauge_Control(0, 4);
			LCD_pixel_write_sizeA_p(0, '.', 16);
		}
		else if (LongKeyWheel[0].PressTime < 1300)
		{
			MAL_LED_BarGauge_Control(0, 6);
			LCD_pixel_write_sizeA_p(0, '.', 17);
		}
		else if (LongKeyWheel[0].PressTime < 1600)
		{
			MAL_LED_BarGauge_Control(0, 8);
			LCD_pixel_write_sizeA_p(0, '.', 18);

		}
		else if (LongKeyWheel[0].PressTime < 1900)
		{
			f_toggle = 1;
			View_Changer(VIEW_2_SETTING_MENU);
		}
	}
	else
	{
		f_toggle = 1;
		View_Undo();
	}
}
