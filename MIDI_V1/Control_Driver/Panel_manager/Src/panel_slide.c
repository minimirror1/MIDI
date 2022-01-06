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

#include "filter_manager.h"

#include "app_pid_midi_cmd.h"

#ifdef PROTOCOL_DEF
#include "can_datalink.h"
#endif



extern Panel_Page_TypeDef page;
extern PanelManager_TypeDef panel;

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;

extern Comm_Page_TypeDef com_page;
extern Comm_Axle_TypeDef com_axle;

extern uint8_t my_can_id;

extern filter_TypeDef filter[8];


Slide_TypeDef slide_master = {0,};

uint32_t motionTick = 0;

#define ENABLE_GAP		200

void Motion_Tick(void)
{
	motionTick++;
}
void Motion_Tick_Clear(void)
{
	motionTick = 0;
}
uint32_t Motion_GetTickCount(void)
{
	return motionTick;
}

void slide_slot_clear(void)
{
	for(int i = 0; i < 8; i++)
	{
		slide_master.f_slotEnable[i] = RESET;
		MAL_LED_Button_Control(i, 3, LED_OFF);
		Slide_control(i, 0);
		LCD_pixel_write_sizeA_p(i, ' ', 16);
		LCD_pixel_write_sizeA_p(i, 'O', 17);
		LCD_pixel_write_sizeA_p(i, 'F', 18);
		LCD_pixel_write_sizeA_p(i, 'F', 19);
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
		if(motor_id == com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].motor_num)
		{
			return i;
		}
	}
	return 0xff;
}

uint8_t slide_id_check_group(uint8_t group_id, uint8_t motor_id)
{
	for(int i = 0; i < 8; i++)
	{
		if(group_id == com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].group_num)
		{
			if(motor_id == com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].motor_num)
				return i;
		}
	}
	return 0xff;
}


void slide_v0_value_tx(void)
{
	//슬라이드에서 손땠을때 위치는?? 어떻게 처리하는가
	for(int i = 0; i < 8; i++)
	{

		if(slide_master.f_slotEnable[i] == RESET)// enable 일때만 동작함
		{
			if(slide_master.f_reMapOverPosi[i] == SET)
			{
				MAL_LED_BackLight_Control(i, LED_RED);
			}
			else
			{
				MAL_LED_BackLight_Control(i, LED_WHITE);
			}
		}
		else
		{


			if (com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].listNum != 0)
			{
				if (slide_master.oldAdc[i] != filter[i].filterData)
				{
					if (MAL_NonStopDelay(&slide_master.t_txTime[i], 20) == 1)
					{
						//0.0.6v
						if(slide_master.f_enablePosi[i] == SET)
						{
							int32_t range = filter[i].filterData;
							slide_master.oldAdc[i] = filter[i].filterData;

							if(((slide_master.enablePosi[i]-ENABLE_GAP) <= range)&&(range <= (slide_master.enablePosi[i]+ENABLE_GAP)))
							{
								slide_master.f_enablePosi[i] = RESET;
							}
						}

						if(slide_master.f_enablePosi[i] == RESET)
						{

							MAL_LED_BackLight_Control(i, LED_CYAN);
							slide_master.oldAdc[i] = filter[i].filterData;
							//canprotocol
#ifdef PROTOCOL_DEF
							CAN_App_MIDI_SlideDataSend_TxReq(
									com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].group_num,
									com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].motor_num,
									Motion_GetTickCount(),
									filter[i].filterData);
#else
							app_tx_midi_sub_pid_adc_ctl(0, 0, my_can_id, MASTER_CAN_ID, 0, 0,
									com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].group_num,
									com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].motor_num,
									filter[i].filterData);
#endif

							LCD_SetText_ADC_DEC(i, filter[i].filterData);
						}

						slide_master.t_motorPosi[i] = HAL_GetTick();
					}
				}
				else if (slide_master.f_motorPosi[i] == 1)
				{
					MAL_LED_BackLight_Control(i, LED_YELLOW);
					slide_master.f_motorPosi[i] = 0;
					//Slide_control(i, slide_master.motorPosi[i]);
					Slide_control(i,
							map(
							slide_master.motorPosi[i],
							com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].setPage.min,
							com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].setPage.max,
							0,
							com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].setPage.range
							));


					LCD_SetText_ADC_DEC(i, slide_master.motorPosi[i]);
					slide_master.t_txTime[i] = HAL_GetTick();
					slide_master.t_motorPosi[i] = HAL_GetTick();
				}
			}

			if (MAL_NonStopDelay(&slide_master.t_motorPosi[i], 50) == 1)
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
				if (com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].motor_num != 0)
				{
					MAL_LED_BackLight_Control(i, LED_CYAN);
					if (slide_master.oldAdc[i] != filter[i].filterData)
					{
						if (MAL_NonStopDelay(&slide_master.t_txTime[i], 20) == 1)
						{
							slide_master.oldAdc[i] = filter[i].filterData;
							//canprotocol
							app_tx_midi_sub_pid_adc_ctl(0, 0, my_can_id, MASTER_CAN_ID, CAN_SUB_ID_BROAD_CAST,
									com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].motor_num, filter[i].filterData);
							LCD_SetText_ADC_DEC(i, filter[i].filterData);
						}
					}
				}
			}
#endif
		}
	}
}
void slide_v6_value_tx(void)
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


			if (com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].listNum != 0)
			{
				if (slide_master.oldAdc_v6[i] != extenderPacket.adc[i] >> ADC_SHIFT)
				{
					if (MAL_NonStopDelay(&slide_master.t_txTime[i], 20) == 1)
					{
						MAL_LED_BackLight_Control(i, LED_CYAN);
						slide_master.oldAdc_v6[i] = extenderPacket.adc[i] >> ADC_SHIFT;
						//canprotocol
						app_tx_midi_sub_pid_adc_ctl(0, 0, my_can_id, MASTER_CAN_ID, 0, 0,
								com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].group_num,
								com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].motor_num,
								slide_master.oldAdc_v6[i]);
						LCD_SetText_ADC_DEC(i, slide_master.oldAdc_v6[i]);

						slide_master.t_motorPosi[i] = HAL_GetTick();
					}
				}
				else if (slide_master.f_motorPosi[i] == 1)
				{
					MAL_LED_BackLight_Control(i, LED_YELLOW);
					slide_master.f_motorPosi[i] = 0;
					//Slide_control(i, slide_master.motorPosi[i]);
					Slide_control(i,slide_master.motorPosi[i]);// 맵핑전 슬라이드위치로


					LCD_SetText_ADC_DEC(i, slide_master.motorPosi[i]);
					slide_master.t_txTime[i] = HAL_GetTick();
					slide_master.t_motorPosi[i] = HAL_GetTick();
				}

			}

			if (MAL_NonStopDelay(&slide_master.t_motorPosi[i], 50) == 1)
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
				if (com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].motor_num != 0)
				{
					MAL_LED_BackLight_Control(i, LED_CYAN);
					if (slide_master.oldAdc[i] != filter[i].filterData)
					{
						if (MAL_NonStopDelay(&slide_master.t_txTime[i], 20) == 1)
						{
							slide_master.oldAdc[i] = filter[i].filterData;
							//canprotocol
							app_tx_midi_sub_pid_adc_ctl(0, 0, my_can_id, MASTER_CAN_ID, CAN_SUB_ID_BROAD_CAST,
									com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].motor_num, filter[i].filterData);
							LCD_SetText_ADC_DEC(i, filter[i].filterData);
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
			slide_v0_value_tx();
			break;
		case VIEW_6_SLIDE_SETTING:
			slide_v6_value_tx();
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























