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
	if(LongKeyWheel[0].fLongKey)
	{
		View_Changer(VIEW_1_SETTING_PREVIEW);
	}
}

void panel_longKey(void)
{
	check_longKey_SettingPreview();
}