/*
 * panel_slide.c
 *
 *  Created on: 2021. 4. 2.
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
#include "panel_slide.h"

#include "long_key.h"

#include "communication_info.h"

#include "app_pid_midi_cmd.h"

extern Panel_Page_TypeDef page;
extern PanelManager_TypeDef panel;

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;

extern Comm_Page_TypeDef com_page;
extern Comm_Axle_TypeDef com_axle;

extern uint8_t my_can_id;


Slide_TypeDef slide_master = {0,};

void slide_slot_clear(void)
{
	for(int i = 0; i < 8; i++)
	{
		slide_master.f_slotEnable[i] = RESET;
		MAL_LED_Button_Control(i, 3, LED_OFF);
	}


}

void set_slide_slot_flag(uint8_t slotNum, uint8_t status)
{
	if(slotNum >8)
		return;

	if(status == SET)
	{
		slide_master.f_slotEnable[slotNum] = status;
	}
	else
	{
		slide_master.f_slotEnable[slotNum] = RESET;
	}
}

uint8_t get_slide_slot_flag(uint8_t slotNum)
{
	if(slotNum >8)
			return 0xff;

	return slide_master.f_slotEnable[slotNum];
}

uint8_t slide_id_check(uint8_t motor_id)
{
	for(int i = 0; i < 8; i++)
	{
		if(motor_id == com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].axle_num)
		{
			return i;
		}
	}
	return 0xff;
}

void slide_value_tx(void)
{
	//슬라이드에서 손땠을때 위치는?? 어떻게 처리하는가
	for(int i = 0; i < 8; i++)
	{

		if(slide_master.f_slotEnable[i] == RESET)// enable 일때만 동작함
		{
			MAL_LED_BackLight_Control(i, LED_WHITE);

		}
		else
		{


			if (com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].axle_num != 0)
			{

				if (slide_master.oldAdc[i] != extenderPacket.adc[i])
				{
					if (MAL_NonStopDelay(&slide_master.t_txTime[i], 20) == 1)
					{
						MAL_LED_BackLight_Control(i, LED_CYAN);
						slide_master.oldAdc[i] = extenderPacket.adc[i];
						//canprotocol
						app_tx_midi_sub_pid_adc_ctl(0, 0, my_can_id, MASTER_CAN_ID, CAN_SUB_ID_BROAD_CAST,
								com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].axle_num, extenderPacket.adc[i]);
						LCD_SetText_ADC_DEC(i, extenderPacket.adc[i]);

						slide_master.t_motorPosi[i] = HAL_GetTick();
					}
				}
				else if (slide_master.f_motorPosi[i] == 1)
				{
					MAL_LED_BackLight_Control(i, LED_YELLOW);
					slide_master.f_motorPosi[i] = 0;
					Slide_control(i, slide_master.motorPosi[i]);

					LCD_SetText_ADC_DEC(i, slide_master.motorPosi[i]);
					slide_master.t_txTime[i] = HAL_GetTick();
					slide_master.t_motorPosi[i] = HAL_GetTick();
				}
			}

			if (MAL_NonStopDelay(&slide_master.t_motorPosi[i], 25) == 1)
								MAL_LED_BackLight_Control(i, LED_WHITE);

#if 0
			if (extenderPacket.touch[i] == 0x00)
			{

				if (slide_master.f_motorPosi[i] == 1)
				{
					MAL_LED_BackLight_Control(i, LED_YELLOW);
					slide_master.f_motorPosi[i] = 0;
					Slide_control(i, slide_master.motorPosi[i]);

					LCD_SetText_ADC_DEC(i, slide_master.motorPosi[i]);
				}
				else
				{
					if (MAL_NonStopDelay(&slide_master.t_motorPosi[i], 25) == 1)
						MAL_LED_BackLight_Control(i, LED_WHITE);
				}

				slide_master.t_txTime[i] = HAL_GetTick();
			}
			else
			{
				if (com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].axle_num != 0)
				{
					MAL_LED_BackLight_Control(i, LED_CYAN);
					if (slide_master.oldAdc[i] != extenderPacket.adc[i])
					{
						if (MAL_NonStopDelay(&slide_master.t_txTime[i], 20) == 1)
						{
							slide_master.oldAdc[i] = extenderPacket.adc[i];
							//canprotocol
							app_tx_midi_sub_pid_adc_ctl(0, 0, my_can_id, MASTER_CAN_ID, CAN_SUB_ID_BROAD_CAST,
									com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].axle_num, extenderPacket.adc[i]);
							LCD_SetText_ADC_DEC(i, extenderPacket.adc[i]);
						}
					}
				}
			}
#endif
		}
	}
}

void slide_tx_manager(void)
{

	switch(panel.view.nowView)
	{
		case VIEW_0_MAIN:
			slide_value_tx();
			break;
			//=====================================
		case VIEW_1_SETTING_PREVIEW:
		case VIEW_2_SETTING_MENU:
		case VIEW_3_AXLE_CHANGE:
		case VIEW_4_PAGE_CHANGE:
		case VIEW_LAST_NUM:
		default:
			break;
	}
}























