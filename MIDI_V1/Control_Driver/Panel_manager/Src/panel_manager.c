/*
 * panel_manager.c
 *
 *  Created on: 2021. 3. 23.
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


#include "panel_manager.h"


PanelManager_TypeDef panel = {0,};

void Panel_Init(void)
{
	//panel.interface.in.btn[0] =

}
