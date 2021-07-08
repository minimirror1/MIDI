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

			if (com_axle.axleInfo[rangeAxle].axle_num != 0)
			{
				LCD_SetText_AXLENUM_DEC(slot, com_axle.axleInfo[rangeAxle].axle_num);
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
						rotCnt[i] = V_6_NOW;

				}
				else if (wheel[i].status.f_rot == ROT_CCW)
				{
					rotCnt[i]--;
					if (rotCnt[i] == 0xFF)
						rotCnt[i] = V_6_APPLY;
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

				switch(rotCnt[i])
				{
					case V_6_NOW:
						Slide_control(i, 0);
						extenderPacket.adc[i] = 0;
						break;
					case V_6_MAP_MIN:
						Slide_control(i, com_axle.axleInfo[rangeAxle[i]].setPage[0].min);
						LCD_SetText_ADC_DEC(i, com_axle.axleInfo[rangeAxle[i]].setPage[0].min);
						extenderPacket.adc[i] = com_axle.axleInfo[rangeAxle[i]].setPage[0].min << ADC_SHIFT;
						break;
					case V_6_MAP_MAX:
						Slide_control(i, com_axle.axleInfo[rangeAxle[i]].setPage[0].max);
						LCD_SetText_ADC_DEC(i, com_axle.axleInfo[rangeAxle[i]].setPage[0].max);
						extenderPacket.adc[i] = com_axle.axleInfo[rangeAxle[i]].setPage[0].max << ADC_SHIFT;
						break;
					case V_6_RANGE:
						Slide_control(i, com_axle.axleInfo[rangeAxle[i]].setPage[0].range);
						LCD_SetText_ADC_DEC(i, com_axle.axleInfo[rangeAxle[i]].setPage[0].range);
						extenderPacket.adc[i] = com_axle.axleInfo[rangeAxle[i]].setPage[0].range << ADC_SHIFT;
						break;
					case V_6_APPLY:
						Slide_control(i, 0);
						extenderPacket.adc[i] = 0;
						break;
				}
			}
		}

		if(rotCnt[i] >= V_6_MAP_MIN)
		{


			switch(rotCnt[i])
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
				com_axle.axleInfo[rangeAxle[i]].setPage[0].min = settingTemp[i].min;
				com_axle.axleInfo[rangeAxle[i]].setPage[0].max = settingTemp[i].max;
				com_axle.axleInfo[rangeAxle[i]].setPage[0].range = settingTemp[i].range;

				app_tx_midi_sub_pid_range_data_ctl(
						0,
						0,
						my_can_id,
						MASTER_CAN_ID,
						CAN_SUB_ID_BROAD_CAST,
						rangeAxle[i],
						0,
						com_axle.axleInfo[rangeAxle[i]].setPage[0].range,
						com_axle.axleInfo[rangeAxle[i]].setPage[0].max,
						com_axle.axleInfo[rangeAxle[i]].setPage[0].min);
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
void View_6_Init(void)
{
	for(int i = 0; i < 8 ; i++)
	{
		rangeAxle[i] = com_page.pageInfo[page.changeNum].slot_axle[i].axleNum;
		rotCnt[i] = V_6_NOW;
		f_v6_rotChage[i] = 0;

		settingTemp[i].min = com_axle.axleInfo[rangeAxle[i]].setPage[0].min;
		settingTemp[i].max = com_axle.axleInfo[rangeAxle[i]].setPage[0].max;
		settingTemp[i].range = com_axle.axleInfo[rangeAxle[i]].setPage[0].range;
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
		}

	}
	Changea_Setting(rangeAxle, rotCnt);
	View_6_ChangeVal();

	SlideApplyManager();

	if (MAL_NonStopDelay(&t_SetLed, 500) == 1)
	{
		MAL_LED_Button_Control(7, LED_SELECT, toggleLed);
		MAL_LED_Button_Control(7, LED_MUTE, toggleLed);
		toggleLed ^= 1;
	}
}











