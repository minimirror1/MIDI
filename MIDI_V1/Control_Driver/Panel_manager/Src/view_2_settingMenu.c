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

#include "long_key.h"


extern LongKey_TypeDef LongKeyWheel[8];


uint8_t MenuSelect(void)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		if(LongKeyWheel[i].fLongKey == 1)
			return i;
	}
	return 0xff;
}
void View_2_SettingMenu(void)
{
	static uint8_t f_toggle = 1;

	if (f_toggle == 1)
	{
		f_toggle = 0;

		LCD_Write_String(0, 1, "Axle", sizeof("Axle"));
		LCD_Write_String(0, 2, "Change", sizeof("Change"));

		LCD_Write_String(1, 1, "Page", sizeof("Page"));
		LCD_Write_String(1, 2, "Change", sizeof("Change"));

		LCD_Write_String(7, 1, "Device", sizeof("Device"));
		LCD_Write_String(7, 2, "Setting", sizeof("Setting"));
	}


	switch(MenuSelect())
	{
		case 0:
			View_Changer(VIEW_3_AXLE_CHANGE);
			break;
		case 1:
			View_Changer(VIEW_4_PAGE_CHANGE);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		default:
			break;
	}

}
