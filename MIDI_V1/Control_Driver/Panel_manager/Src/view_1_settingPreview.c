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

#include "long_key.h"

extern LongKey_TypeDef LongKeyWheel[8];

void View_1_SettingPreview(void)
{
	static uint8_t f_toggle = 1;

	if(f_toggle == 1)
	{
		f_toggle = 0;

		LCD_Write_String(0, 1, "Axle", sizeof("Axle"));
		LCD_Write_String(0, 2, "Change", sizeof("Change"));

		LCD_Write_String(1, 1, "Page", sizeof("Page"));
		LCD_Write_String(1, 2, "Change", sizeof("Change"));

		LCD_Write_String(7, 1, "Device", sizeof("Device"));
		LCD_Write_String(7, 2, "Setting", sizeof("Setting"));
	}


	if(LongKeyWheel[0].fLongKey)
	{
		if (LongKeyWheel[0].PressTime < 1000) {
			MAL_LED_BarGauge_Control(0, 2);
		} else if (LongKeyWheel[0].PressTime < 1500) {
			MAL_LED_BarGauge_Control(0, 4);
		} else if (LongKeyWheel[0].PressTime < 2000) {
			MAL_LED_BarGauge_Control(0, 6);
		} else if (LongKeyWheel[0].PressTime < 2500) {
			MAL_LED_BarGauge_Control(0, 8);
		}
	}
	else{
		f_toggle = 1;
		View_Undo();
	}
}
