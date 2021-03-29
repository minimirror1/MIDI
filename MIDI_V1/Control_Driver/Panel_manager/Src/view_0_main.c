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

#include "communication_info.h"


extern PanelManager_TypeDef panel;

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;

extern Comm_Page_TypeDef com_page;
extern Comm_Axle_TypeDef com_axle;



void Change_Page(uint8_t pageNum)
{
	for(int i = 0; i<8; i++)
	{

		if(com_axle.axleInfo[com_page.pageInfo[pageNum].slot_axle[i].axleNum].nick_name != 0)
			LCD_Write_String(i, 1, com_axle.axleInfo[com_page.pageInfo[pageNum].slot_axle[i].axleNum].nick_name, 10);
	}
}


void View_0_Main(void)//일반 조종화면
{

	static uint32_t t_test;

	static uint32_t t_adc;



	if (MAL_NonStopDelay(&t_test, 3000) == 1)
		{
			Change_Page(0);
		}

	if (MAL_NonStopDelay(&t_adc, 50) == 1)
	{
		LCD_SetText_DEC(0, extenderPacket.adc[0]);
		LCD_SetText_DEC(1, extenderPacket.adc[1]);
		LCD_SetText_DEC(2, extenderPacket.adc[2]);
		LCD_SetText_DEC(3, extenderPacket.adc[3]);
		LCD_SetText_DEC(4, extenderPacket.adc[4]);
		LCD_SetText_DEC(5, extenderPacket.adc[5]);
		LCD_SetText_DEC(6, extenderPacket.adc[6]);
		LCD_SetText_DEC(7, extenderPacket.adc[7]);
	}

}















