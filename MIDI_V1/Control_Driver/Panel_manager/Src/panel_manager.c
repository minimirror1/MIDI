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
#include "HC165_MIDI_btn.h"

#include "X_Touch_Extender_ADC.h"
#include "X_Touch_Extender_MotorAdc_packet.h"
#include "LCD_MIDI.h"
#include "LCD_MIDI_Control.h"
#include "non_stop_delay_main.h"


#include "panel_manager.h"
#include "panel_view.h"
#include "panel_control.h"

//LED
extern HC595_LED_GroupTypeDef led_group[MIDI_LED_GROUP_COUNT];

extern HC165_wheel_TypeDef wheel[8];
extern HC165_btn_TypeDef btn[8];

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;

PanelManager_TypeDef panel = {0,};

void Panel_Init(void)
{
	uint8_t column = 0;

	panel.view.nowView = VIEW_0_MAIN;
	panel.view.lastView = VIEW_0_MAIN;
	panel.view.viewFnc = View_0_Main;

	for (column = 0; column < 8; column++) {
		panel.interface[column].in.btn[0] = &btn[column].status[0].btn;
		panel.interface[column].in.btn[1] = &btn[column].status[1].btn;
		panel.interface[column].in.btn[2] = &btn[column].status[2].btn;
		panel.interface[column].in.btn[3] = &btn[column].status[3].btn;

		panel.interface[column].in.wheelBtn = &wheel[column].status.btn;
		panel.interface[column].in.wheelRot = &wheel[column].status.f_rot;

		panel.interface[column].in.slideAdc = &extenderPacket.adc[column];
		panel.interface[column].in.slideTouch = &extenderPacket.touch[column];


		panel.interface[column].out.btn[0] = &led_group[column].button.rec;
		panel.interface[column].out.btn[1] = &led_group[column].button.solo;
		panel.interface[column].out.btn[2] = &led_group[column].button.mute;
		panel.interface[column].out.btn[3] = &led_group[column].button.select;

		panel.interface[column].out.barGauge = &led_group[column].barGauge.value;
		panel.interface[column].out.wheelGauge = &led_group[column].wheelGauge.value;
	}
}



void Panel_Manager(void)
{
	View_Manager();

}




















