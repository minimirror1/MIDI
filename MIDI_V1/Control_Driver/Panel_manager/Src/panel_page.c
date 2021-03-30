/*
 * panel_page.c
 *
 *  Created on: 2021. 3. 30.
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

#include "communication_info.h"

extern PanelManager_TypeDef panel;

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;

extern Comm_Page_TypeDef com_page;
extern Comm_Axle_TypeDef com_axle;

Panel_Page_TypeDef page = {0,};

void Set_Page(uint8_t pageNum)
{
	page.f_change = SET;
	page.changeNum = pageNum;
}
void Page_Display(void) {
	if (page.f_change == SET)
	{
		page.f_change = RESET;
		for (int i = 0; i < 8; i++)
		{

			if (com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].nick_name != 0)
				LCD_Write_String(i, 1, com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].nick_name, 10);

			if (com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].axle_num != 0)
			{
				LCD_SetText_AXLENUM_DEC(i, com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].axle_num);
				LCD_pixel_write_sizeA_p(i, '|', 14);
			}

		}
	}
}
