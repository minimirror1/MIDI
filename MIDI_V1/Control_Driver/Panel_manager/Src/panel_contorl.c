/*
 * panel_contorl.c
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

void check_longKey_SettingPreview(void)//1번 로터리 버튼
{
	if(LongKeyWheel[7].fLongKey)
	{
		View_Changer(VIEW_1_SETTING_PREVIEW);
	}
}

void panel_longKey(void)
{
	check_longKey_SettingPreview();
}

void panel_wheel_Led_rot(uint8_t num, uint8_t cntClear)
{
	static uint32_t t_wheel_led[8];
	static uint8_t wheel_val[8] = {0,};
	static uint8_t f_toggle[8] = {0,};

	if(num > 8)
		return;
	if(cntClear == 1)
	{
		for(int i = 0; i < 8 ; i++)
		{
			f_toggle[i] = 0;
			wheel_val[i] = 0;
		}

		return;
	}

	if(MAL_NonStopDelay(&t_wheel_led[num], 70) == 1)
	{
		MAL_LED_Wheel_Control(num, wheel_val[num]);

		if(f_toggle[num] == 0)
		{
			wheel_val[num]++;
			if(wheel_val[num] >= 13)
			{
				f_toggle[num] = 1;
			}
		}
		else
		{
			wheel_val[num]--;
			if (wheel_val[num] <= 0)
			{
				f_toggle[num] = 0;
			}
		}

	}
}






