/*
 * view_3_axleChange.c
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
#include "panel_slide.h"

#include "long_key.h"

#include "communication_info.h"

#include "app_pid_midi_cmd.h"

extern Panel_Page_TypeDef page;

extern Comm_Page_TypeDef com_page;
extern Comm_Axle_TypeDef com_axle;

extern HC165_wheel_TypeDef wheel[8];
extern HC165_btn_TypeDef btn[8];

uint8_t tempPageNum;
uint8_t tempAxleSlot[8] = { 0, };

uint8_t f_changeAxleSlot[8] = { 0, };

uint8_t changeSlotCnt[8] = { 0, };

uint8_t f_axleChange = SET;

uint8_t f_v3_first = 1;

void now_AxleNumber_Copy(void) {
	tempPageNum = page.changeNum;

	for (int i = 0; i < 8; i++)
	{
		tempAxleSlot[i] = com_page.pageInfo[page.changeNum].slot_axle[i].axleNum;

		f_changeAxleSlot[i] = com_page.pageInfo[page.changeNum].slot_axle[i].axleNum;
	}
}

void ChangeAxle_Display(void) {
	if (f_axleChange == SET)
	{
		f_axleChange = RESET;
		for (int i = 0; i < 8; i++)
		{
			if (com_axle.axleInfo[tempAxleSlot[i]].axle_num != 0)
			{
				LCD_SetText_AXLENUM_DEC(i, com_axle.axleInfo[tempAxleSlot[i]].axle_num);
				LCD_Write_String(i, 1, com_axle.axleInfo[tempAxleSlot[i]].nick_name, 10);
				LCD_pixel_write_sizeA_p(i, '|', 14);
			}
			else
			{
				LCD_Write_String(i, 1, "          ", 10);
				LCD_Write_String(i, 2, "    ", 4);
			}
			LCD_SetText_ADC_DEC(i, tempPageNum);
			LCD_pixel_write_sizeA_p(i, 'P', 16);
		}
	}
}

void Change_Axle(void) {

	for (int i = 0; i < 8; i++)
	{
		if (wheel[i].status.f_rot != ROT_CLEAR)
		{
			if (wheel[i].status.f_rot == ROT_CW)
			{
				changeSlotCnt[i]++;
				if (changeSlotCnt[i] > com_axle.list.cnt)
					changeSlotCnt[i] = 0;

				if (com_axle.list.pAxleInfo[changeSlotCnt[i]]->axle_num != 0)
				{
					for (int j = 0; j < 8; j++)
					{
						if (com_axle.list.pAxleInfo[changeSlotCnt[i]]->axle_num == tempAxleSlot[j])
						{
							changeSlotCnt[i]++;
							if (changeSlotCnt[i] > com_axle.list.cnt)
								changeSlotCnt[i] = 0;

							/*if(com_axle.list.pAxleInfo[changeSlotCnt[i]]->axle_num == tempAxleSlot[j])
							 changeSlotCnt[i]++;*/
						}
					}
				}

			}
			else if (wheel[i].status.f_rot == ROT_CCW)
			{
				changeSlotCnt[i]--;
				if (changeSlotCnt[i] == 0xff)
					changeSlotCnt[i] = com_axle.list.cnt;

				if (com_axle.list.pAxleInfo[changeSlotCnt[i]]->axle_num != 0)
				{
					for (int j = 0; j < 8; j++)
					{
						if (com_axle.list.pAxleInfo[changeSlotCnt[i]]->axle_num == tempAxleSlot[j])
						{
							changeSlotCnt[i]--;
							if (changeSlotCnt[i] == 0xff)
								changeSlotCnt[i] = com_axle.list.cnt;

							/*if(com_axle.list.pAxleInfo[changeSlotCnt[i]]->axle_num == tempAxleSlot[j])
							 changeSlotCnt[i]--;*/
						}
					}
				}
			}

			tempAxleSlot[i] = com_axle.list.pAxleInfo[changeSlotCnt[i]]->axle_num;



			wheel[i].status.f_rot = ROT_CLEAR;
			f_axleChange = SET;
		}
	}
}

uint8_t f_v3_cancel = 0;
uint8_t f_v3_apply = 0;
void AxleApplyManager(void) {
	if (btn[7].status[2].btn == 1) //취소
	{
		if (f_v3_cancel == 0)
			f_v3_cancel = 1;
	}
	else
	{
		if (f_v3_cancel == 1)
			f_v3_cancel = 2;
	}

	if (btn[7].status[3].btn == 1) //적용
	{
		if (f_v3_apply == 0)
			f_v3_apply = 1;
	}
	else
	{
		if (f_v3_apply == 1)
			f_v3_apply = 2;
	}

	if (f_v3_apply == 2)
	{
		f_v3_apply = 0;
		f_v3_cancel = 0;

		f_v3_first = 1;

		for (int i = 0; i < 8; i++)
		{
			com_page.pageInfo[tempPageNum].slot_axle[i].axleNum = tempAxleSlot[i];

			if (f_changeAxleSlot[i] != tempAxleSlot[i])
			{ //canprotocol
				app_tx_midi_sub_pid_page_ctl(0, 0, my_can_id, MASTER_CAN_ID, CAN_SUB_ID_BROAD_CAST, tempPageNum, i, tempAxleSlot[i],
						com_page.pageInfo[tempPageNum].slot_axle[i].setPageNum);
			}
		}

		View_Changer(VIEW_0_MAIN);

	}
	else if (f_v3_cancel == 2)
	{
		f_v3_apply = 0;
		f_v3_cancel = 0;

		View_Changer(VIEW_0_MAIN);
		f_v3_first = 1;

	}

#if 0
	if(btn[7].status[2].btn == 1)//취소
	{
		View_Changer(VIEW_0_MAIN);
		f_v3_first = 1;

	}
	else if(btn[7].status[3].btn == 1)//적용
	{
		f_v3_first = 1;

		for (int i = 0; i < 8; i++)
		{
			com_page.pageInfo[tempPageNum].slot_axle[i].axleNum = tempAxleSlot[i];

			if(f_changeAxleSlot[i] != tempAxleSlot[i])
			{//canprotocol
				app_tx_midi_sub_pid_page_ctl(0, 0, my_can_id, MASTER_CAN_ID, CAN_SUB_ID_BROAD_CAST,tempPageNum , i, tempAxleSlot[i], com_page.pageInfo[tempPageNum].slot_axle[i].setPageNum);
			}
		}

		View_Changer(VIEW_0_MAIN);

	}
#endif
}

void View_3_AxleChange(void) {
	static uint8_t toggleLed = 0;
	static uint32_t t_SetLed;

	if (f_v3_first == 1)
	{
		f_v3_first = 0;

		now_AxleNumber_Copy();
		f_axleChange = SET;
		panel_wheel_Led_rot(7, 1);

	}
	Change_Axle();
	ChangeAxle_Display();
	AxleApplyManager();

	if (MAL_NonStopDelay(&t_SetLed, 500) == 1)
	{
		MAL_LED_Button_Control(7, LED_SELECT, toggleLed);
		MAL_LED_Button_Control(7, LED_MUTE, toggleLed);
		toggleLed ^= 1;
	}

	for (int i = 0; i < 8; i++)
		panel_wheel_Led_rot(i, 0);

}

