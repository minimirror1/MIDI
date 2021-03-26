/*
 * view_0_main.c
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


extern PanelManager_TypeDef panel;




void View_0_Main(void)
{
	static uint32_t t_test;
	static uint8_t cnt = 0;


}
