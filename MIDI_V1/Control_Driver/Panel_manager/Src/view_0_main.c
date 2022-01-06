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
#include "panel_page.h"
#include "panel_slide.h"

#include "long_key.h"

#include "communication_info.h"

#include "filter_manager.h"

#include "app_pid_init_cmd.h"
#include "app_pid_midi_cmd.h"
#include "prtc_data_pid_midi.h"


extern PanelManager_TypeDef panel;

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;


extern Comm_Page_TypeDef com_page;
extern Comm_Axle_TypeDef com_axle;

extern Panel_Page_TypeDef page;

extern HC165_btn_TypeDef btn[8];
extern HC165_wheel_TypeDef wheel[8];

extern uint8_t my_can_id;

extern filter_TypeDef filter[8];

extern Slide_TypeDef slide_master;

uint8_t f_v0_first = 1;

uint8_t f_v0_enableToggle[8] = {0,};

void View_0_enable(void)
{
	for(int i = 0; i < 8; i++)
	{
		if (com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].listNum != 0)
		{
			if (btn[i].status[3].btn == 1)
			{
				if (f_v0_enableToggle[i] == 0)
				{
					f_v0_enableToggle[i] = 1;

					if (get_slide_slot_flag(i) == 1)
					{
						set_slide_slot_flag(i, 0);
						MAL_LED_Button_Control(i, 3, LED_OFF);
						Slide_control(i, 0);
						LCD_pixel_write_sizeA_p(i, ' ', 16);
						LCD_pixel_write_sizeA_p(i, 'O', 17);
						LCD_pixel_write_sizeA_p(i, 'F', 18);
						LCD_pixel_write_sizeA_p(i, 'F', 19);

					}
					else if (get_slide_slot_flag(i) == 0)
					{
/*						set_slide_slot_flag(i, 1);
						MAL_LED_Button_Control(i, 3, LED_ON);*/
						//상위에 모터위치를 요청하고  응답받으면 활성화 한다.
//						app_tx_midi_sub_pid_adc_rqt(
//								0,
//								1,
//								my_can_id,
//								0,
//								31,
//								com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].axle_num);
#ifdef PROTOCOL_DEF
						CAN_App_MIDI_SlotEnable_TxReq(
								com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].group_num,
								com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].motor_num);
#else
						app_tx_midi_sub_pid_adc_rqt(
																				0,
																				1,
																				my_can_id,
																				0,
																				0,
																				0,
																				com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].group_num,
																				com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].motor_num);
#endif

					}
				}
			}
			else
			{
				if (f_v0_enableToggle[i] == 1)
				{
					f_v0_enableToggle[i] = 0;
				}
			}
		}
	}
}

void View_0_enableRsp(uint8_t slot_id, uint16_t set_posi)
{
	if(slot_id > 8)
		return;

	//0.0.7v
	if(com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.min <= com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.max)
	{
		if((set_posi < com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.min)||( com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.max < set_posi))
		{
			slide_master.f_reMapOverPosi[slot_id] = SET;
			return;
		}
	}
	else
	{
		if((set_posi < com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.max)||( com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.min < set_posi))
		{
			slide_master.f_reMapOverPosi[slot_id] = SET;
			return;
		}
	}
	slide_master.f_reMapOverPosi[slot_id] = RESET;

	set_slide_slot_flag(slot_id, 1);
	MAL_LED_Button_Control(slot_id, 3, LED_ON);

/*	uint32_t posiMap = map(set_posi,TEST_OUT_MIN,TEST_OUT_MAX,0,2048);
	uint32_t posiTemp = posiMap << ADC_SHIFT;*/

	uint32_t posiMap = map(
			set_posi,
			com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.min,
			com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.max,
			0,
			com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.range);


	uint32_t posiTemp = posiMap << ADC_SHIFT;

/*	extenderPacket.adc[slot_id] = set_posi;

	filter[slot_id].filterData = set_posi;
	filter[slot_id].SmoothData = set_posi;

	Slide_control(slot_id, set_posi);
	LCD_SetText_ADC_DEC(slot_id, set_posi);*/

	extenderPacket.adc[slot_id] = posiTemp;

	filter[slot_id].filterData = posiTemp;
	filter[slot_id].SmoothData = posiTemp;

	//220106 활성화시
	*filter[slot_id].RawData = posiTemp;

	slide_master.oldAdc[slot_id] = posiTemp;


	//0.0.6v
	slide_master.enablePosi[slot_id] = set_posi;
	slide_master.f_enablePosi[slot_id] = SET;
	//slide_master.testPosi[slot_id] = posiMap;


	Slide_control(slot_id, posiMap);
	LCD_SetText_ADC_DEC(slot_id, map(
			posiTemp,
			0,
			com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.range << ADC_SHIFT,
			com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.min,
			com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].listNum].setPage.max));

}

//=============================================================================
/*float filterMap[14] = {
		1.0f,
		0.95f,
		0.9f,
		0.85f,
		0.8f,
		0.7f,
		0.6f,
		0.5f,
		0.4f,
		0.3f,
		0.2f,
		0.15f,
		0.1f,
		0.05f
};*/
float filterMap[14] = {
		1.0f,
		0.95f,
		0.9f,
		0.85f,
		0.8f,
		0.7f,
		0.6f,
		0.32f,
		0.16,
		0.08f,
		0.04f,
		0.02f,
		0.01f,
		0.005f
};

int16_t filterCnt[8] = {0,};
void View_0_filterValChange(void) {

	for(int i = 0; i < 8; i++)
	{
		if (wheel[i].status.f_rot != ROT_CLEAR)
		{
			if (wheel[i].status.f_rot == ROT_CW)
			{
				filterCnt[i]++;
				if(filterCnt[i] >= 13)
					filterCnt[i] = 13;
			}
			else if (wheel[i].status.f_rot == ROT_CCW)
			{
				filterCnt[i]--;
				if (filterCnt[i] < 0)
					filterCnt[i] = 0;
			}
			wheel[i].status.f_rot = ROT_CLEAR;

			MAL_LED_Wheel_Control(i,filterCnt[i]);
			filter[i].LPF_Beta = filterMap[filterCnt[i]];
		}
	}
}
//=============================================================================


void View_0_Main(void)//일반 조종화면
{

	if(f_v0_first == 1)
	{
		f_v0_first = 0;
		for(int k = 0; k < 8; k++)
		{
			LCD_SetText_ADC_DEC(k, filter[k].filterData);

			filterCnt[k] = 0;
			filter[k].LPF_Beta = filterMap[filterCnt[k]];
			MAL_LED_Wheel_Control(k,filterCnt[k]);

			slide_master.f_slotEnable[k] = RESET;
			f_v0_enableToggle[k] = 0;
		}

		slide_slot_clear();


	}
	View_0_filterValChange();
	View_0_enable();


	slide_tx_manager();



	panel_longKey();
	Page_Display();

}















