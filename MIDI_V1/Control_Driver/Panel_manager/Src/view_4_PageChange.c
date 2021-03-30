/*
 * view_4_PageChange.c
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

#include "long_key.h"

void View_4_PageChange(void)
{
	LCD_Write_String(1, 1, "View4", sizeof("View4"));
	LCD_Write_String(1, 2, "Change", sizeof("Change"));
}
