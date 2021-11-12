/*
 * view_6_slideSetting.c
 *
 *  Created on: 2021. 7. 7.
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

#include "app_pid_init_cmd.h"
#include "app_pid_midi_cmd.h"
#include "prtc_data_pid_midi.h"


typedef enum
{
	V_6_NOW = 0,
	V_6_MAP_MIN,	//Down
	V_6_MAP_MAX,	//UP
	V_6_RANGE,
	V_6_APPLY,
	V_6_NUMBER
}View_6_Msg_StatusTypeDef;


extern Comm_Page_TypeDef com_page;
extern Comm_Axle_TypeDef com_axle;

extern Panel_Page_TypeDef page;

extern HC165_wheel_TypeDef wheel[8];

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;

extern HC165_btn_TypeDef btn[8];

extern filter_TypeDef filter[8];

extern Slide_TypeDef slide_master;


uint8_t f_v6_enableToggle[8] = {0,};
//-----------------------------------------------------------------------------

uint8_t f_v6_first = 1;

uint8_t rangeAxle[8] = {0,};	//설정변경할 모터 번호
uint8_t rotCnt[8] = {0,};		//설정모드 번호 now,  map_min, map_max, map_range, apply
uint8_t f_v6_rotChage[8] = {0,};	//휠 회전시 활성됨.
Comm_AxleInfo_SetPage_TypeDef settingTemp[8] = {0,};

//=============================================================================

//현재 슬롯에 할당된 축번호 불러오기
void View_6_AxleNumber_Copy(uint8_t *rangeAxle) {
	for (int i = 0; i < 8; i++)
	{

	}
}

//슬롯에 표시할 텍스트 설정
void View_6_SettingMsg(uint8_t slot, uint8_t rangeAxle, uint8_t msgNum)
{
	switch(msgNum)
	{
		case V_6_NOW:
			if (com_axle.axleInfo[rangeAxle].nick_name != 0)
				LCD_Write_String(slot, 1, com_axle.axleInfo[rangeAxle].nick_name, 10);

			if (com_axle.axleInfo[rangeAxle].listNum != 0)
			{
				LCD_SetText_AXLENUM_DEC(slot,
						com_axle.axleInfo[rangeAxle].group_num,
						com_axle.axleInfo[rangeAxle].motor_num);
				//LCD_pixel_write_sizeA_p(slot, '|', 14);
			}
			break;
		case V_6_MAP_MIN:
			LCD_Write_String(slot, 1, "ReMAP_MIN", sizeof("ReMAP_MIN"));
			break;
		case V_6_MAP_MAX:
			LCD_Write_String(slot, 1, "ReMAP_MAX", sizeof("ReMAP_MAX"));
			break;
		case V_6_RANGE:
			LCD_Write_String(slot, 1, "Range", sizeof("Range"));
			break;
		case V_6_APPLY:

			LCD_Write_String(slot, 1, "Apply", sizeof("Apply"));
			break;
	}

}

void Changea_Setting(uint8_t *rangeAxle, uint8_t *rotCnt) {
	for(int i = 0; i < 8 ; i++)
	{
		if(rangeAxle[i] != 0)	//슬롯에 할당된 축이 없으면 변화하지 않는다.
		{
			if (wheel[i].status.f_rot != ROT_CLEAR)
			{
				if (wheel[i].status.f_rot == ROT_CW)
				{
					rotCnt[i]++;
					if (rotCnt[i] > V_6_APPLY)
					{
						//rotCnt[i] = V_6_NOW;
						rotCnt[i] = V_6_APPLY;
					}

				}
				else if (wheel[i].status.f_rot == ROT_CCW)
				{
					rotCnt[i]--;
					if (rotCnt[i] == 0xFF)
						rotCnt[i] = V_6_NOW;
				}
				wheel[i].status.f_rot = ROT_CLEAR;

				MAL_LED_Wheel_Control(i, rotCnt[i]);

				LCD_Pixel_wirte_logo(i, ' ');
				LCD_CenterLine(i);
				View_6_SettingMsg(i, rangeAxle[i], rotCnt[i]);
				f_v6_rotChage[i] = SET;
			}
		}
	}
}

void View_6_ChangeVal(void)
{
	for (int i = 0; i < 8; i++)
	{
		if (rangeAxle[i] != 0)	//슬롯에 할당된 축이 없으면 변화하지 않는다.
		{
			if(f_v6_rotChage[i] == SET)
			{
				f_v6_rotChage[i] = RESET;

				slide_master.f_slotEnable[i] = RESET;
				MAL_LED_Button_Control(i, 3, LED_OFF);
				f_v6_enableToggle[i] = 0;

				switch(rotCnt[i])
				{
					case V_6_NOW:
						Slide_control(i, 0);
						extenderPacket.adc[i] = 0;
						break;
					case V_6_MAP_MIN:
						Slide_control(i, com_axle.axleInfo[rangeAxle[i]].setPage.min);
						LCD_SetText_ADC_DEC(i, com_axle.axleInfo[rangeAxle[i]].setPage.min);
						extenderPacket.adc[i] = com_axle.axleInfo[rangeAxle[i]].setPage.min << ADC_SHIFT;
						break;
					case V_6_MAP_MAX:
						Slide_control(i, com_axle.axleInfo[rangeAxle[i]].setPage.max);
						LCD_SetText_ADC_DEC(i, com_axle.axleInfo[rangeAxle[i]].setPage.max);
						extenderPacket.adc[i] = com_axle.axleInfo[rangeAxle[i]].setPage.max << ADC_SHIFT;
						break;
					case V_6_RANGE:
						Slide_control(i, com_axle.axleInfo[rangeAxle[i]].setPage.range);
						LCD_SetText_ADC_DEC(i, com_axle.axleInfo[rangeAxle[i]].setPage.range);
						extenderPacket.adc[i] = com_axle.axleInfo[rangeAxle[i]].setPage.range << ADC_SHIFT;
						break;
					case V_6_APPLY:
						Slide_control(i, 0);
						extenderPacket.adc[i] = 0;
						break;
				}
			}
		}

		if (rotCnt[i] >= V_6_MAP_MIN)
		{

			switch (rotCnt[i])
			{
				case V_6_NOW:
					break;
				case V_6_MAP_MIN:
					settingTemp[i].min = extenderPacket.adc[i] >> ADC_SHIFT;
					LCD_SetText_ADC_DEC(i, extenderPacket.adc[i] >> ADC_SHIFT);
					break;
				case V_6_MAP_MAX:
					settingTemp[i].max = extenderPacket.adc[i] >> ADC_SHIFT;
					LCD_SetText_ADC_DEC(i, extenderPacket.adc[i] >> ADC_SHIFT);
					break;
				case V_6_RANGE:
					settingTemp[i].range = extenderPacket.adc[i] >> ADC_SHIFT;
					LCD_SetText_ADC_DEC(i, extenderPacket.adc[i] >> ADC_SHIFT);
					break;
				case V_6_APPLY:
					break;
			}
		}

	}
}


uint8_t f_v6_cancel = 0;
uint8_t f_v6_apply = 0;
void SlideApplyManager(void) {

	if (btn[7].status[2].btn == 1) //취소
	{
		if (f_v6_cancel == 0)
			f_v6_cancel = 1;
	}
	else
	{
		if (f_v6_cancel == 1)
			f_v6_cancel = 2;
	}

	if (btn[7].status[3].btn == 1) //적용
	{
		if (f_v6_apply == 0)
			f_v6_apply = 1;
	}
	else
	{
		if (f_v6_apply == 1)
			f_v6_apply = 2;
	}

	if (f_v6_apply == 2)
	{
		f_v6_apply = 0;
		f_v6_cancel = 0;

		f_v6_first = 1;

		//page.changeNum = tempPageNum;

		//canprotocol
		//app_tx_midi_sub_pid_last_page_ctl(0, 0, my_can_id, MASTER_CAN_ID, CAN_SUB_ID_BROAD_CAST, page.changeNum);
		for(int i = 0; i < 8; i++)
		{
			if(rotCnt[i] == V_6_APPLY)
			{
				com_axle.axleInfo[rangeAxle[i]].setPage.min = settingTemp[i].min;
				com_axle.axleInfo[rangeAxle[i]].setPage.max = settingTemp[i].max;
				com_axle.axleInfo[rangeAxle[i]].setPage.range = settingTemp[i].range;

				app_tx_midi_sub_pid_range_data_ctl(
						0,
						0,
						my_can_id,
						MASTER_CAN_ID,
						CAN_SUB_ID_BROAD_CAST,
						rangeAxle[i],
						0,
						com_axle.axleInfo[rangeAxle[i]].setPage.range,
						com_axle.axleInfo[rangeAxle[i]].setPage.max,
						com_axle.axleInfo[rangeAxle[i]].setPage.min);
			}
		}

		View_Changer(VIEW_0_MAIN);

	}
	else if (f_v6_cancel == 2)
	{
		f_v6_apply = 0;
		f_v6_cancel = 0;

		View_Changer(VIEW_0_MAIN);
		f_v6_first = 1;

	}
}

void View_6_enableRsp(uint8_t slot_id, uint16_t set_posi)
{
	if(slot_id > 8)
		return;

	set_slide_slot_flag(slot_id, 1);
	MAL_LED_Button_Control(slot_id, 3, LED_ON);

	uint32_t posiMap = set_posi;

	uint32_t posiTemp = posiMap << ADC_SHIFT;

/*	extenderPacket.adc[slot_id] = set_posi;

	filter[slot_id].filterData = set_posi;
	filter[slot_id].SmoothData = set_posi;

	Slide_control(slot_id, set_posi);
	LCD_SetText_ADC_DEC(slot_id, set_posi);*/

	extenderPacket.adc[slot_id] = posiTemp;

	filter[slot_id].filterData = posiTemp;
	filter[slot_id].SmoothData = posiTemp;

	slide_master.oldAdc[slot_id] = posiTemp;

	Slide_control(slot_id, posiMap);
	LCD_SetText_ADC_DEC(slot_id, posiMap);

}
void View_6_enable(void)
{
	for(int i = 0; i < 8; i++)
	{
		if (com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].listNum != 0)
		{
			switch(rotCnt[i])
			{
				case V_6_MAP_MIN:
				case V_6_MAP_MAX:
					//if (btn[i].status[3].btn == 1)
					if (wheel[i].status.btn == 1)
					{
						if (f_v6_enableToggle[i] == 0)
						{
							f_v6_enableToggle[i] = 1;

							if (get_slide_slot_flag(i) == 1)
							{
								set_slide_slot_flag(i, 0);
								MAL_LED_Button_Control(i, 3, LED_OFF);
							}
							else if (get_slide_slot_flag(i) == 0)
							{
								/*						set_slide_slot_flag(i, 1);
								 MAL_LED_Button_Control(i, 3, LED_ON);*/
								//상위에 모터위치를 요청하고  응답받으면 활성화 한다.
								app_tx_midi_sub_pid_adc_rqt(0, 1, my_can_id, 0, 31,
										com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].group_num,
										com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].motor_num);
							}
						}
					}
					else
					{
						if (f_v6_enableToggle[i] == 1)
						{
							f_v6_enableToggle[i] = 0;
						}
					}
					break;
				case V_6_NOW:
				case V_6_RANGE:
				case V_6_APPLY:
					break;
			}
		}
	}
}

void View_6_Init(void)
{
	for(int i = 0; i < 8 ; i++)
	{
		rangeAxle[i] = com_page.pageInfo[page.changeNum].slot_axle[i].listNum;
		rotCnt[i] = V_6_NOW;
		f_v6_rotChage[i] = 0;

		settingTemp[i].min = com_axle.axleInfo[rangeAxle[i]].setPage.min;
		settingTemp[i].max = com_axle.axleInfo[rangeAxle[i]].setPage.max;
		settingTemp[i].range = com_axle.axleInfo[rangeAxle[i]].setPage.range;
	}
}

void View_6_SlideSetting(void)
{
	static uint8_t toggleLed = 0;
	static uint32_t t_SetLed;

	if(f_v6_first == 1)
	{
		f_v6_first = 0;

		//View_6_AxleNumber_Copy(rangeAxle);
		View_6_Init();

		for(int i = 0; i < 8 ; i++)
		{
			View_6_SettingMsg(i, rangeAxle[i], rotCnt[i]);

			set_slide_slot_flag(i, RESET);
			f_v6_enableToggle[i] = 0;
		}

	}
	Changea_Setting(rangeAxle, rotCnt);
	View_6_ChangeVal();
	View_6_enable();

	SlideApplyManager();

	slide_tx_manager();

	if (MAL_NonStopDelay(&t_SetLed, 500) == 1)
	{
		if (get_slide_slot_flag(7) == 1)
		{
			MAL_LED_Button_Control(7, LED_SELECT, LED_ON);
		}
		else
		{
			MAL_LED_Button_Control(7, LED_SELECT, toggleLed);
		}
		MAL_LED_Button_Control(7, LED_MUTE, toggleLed);
		toggleLed ^= 1;
	}
}











