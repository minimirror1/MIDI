/*
 * communication_manager.c
 *
 *  Created on: 2021. 3. 29.
 *      Author: shin
 */

#include "main.h"
#include "string.h"
#include "communication_manager.h"
#include "communication_info.h"
#ifndef PROTOCOL_DEF
#include "app_pid_init_cmd.h"
#include "app_pid_midi_cmd.h"
#include "prtc_data_pid_midi.h"
#else
#include "can_datalink.h"
#endif
#include "panel_page.h"
#include "panel_slide.h"
#include "panel_manager.h"

#include "filter_manager.h"

extern uint8_t my_can_id;

extern uint8_t f_change_Page;
extern uint8_t change_Page;

extern Slide_TypeDef slide_master;

extern uint8_t f_v0_first;

extern PanelManager_TypeDef panel;

Comm_Page_TypeDef com_page = { 0, };
Comm_Axle_TypeDef com_axle = { 0, };

extern Panel_Page_TypeDef page;



uint8_t getListNum(uint8_t group_id, uint8_t motor_id)
{
	uint8_t ret = 0xff;

	for (int i = 0; i <= com_axle.list.cnt; i++)
	{
		if (com_axle.list.pAxleInfo[i]->group_num == group_id) //group
		{
			if (com_axle.list.pAxleInfo[i]->motor_num == motor_id)
			{
				ret = com_axle.list.pAxleInfo[i]->listNum;
				return ret;
			}
		}
	}
	return ret;
}

#ifndef PROTOCOL_DEF
//=============================================================================
void app_rx_midi_sub_pid_exist_rqt(uint8_t num, prtc_header_t *pPh, uint8_t *pData) {
	app_tx_midi_sub_pid_exist_rsp(0, 1, my_can_id, pPh->souce_id, 0);


}

//=============================================================================

uint8_t reg_flag(uint8_t axleNum) {
	uint8_t buffNum;
	uint8_t bitNum;

	buffNum = axleNum / 32;
	bitNum = (axleNum - 1) - (buffNum * 32);

	com_axle.setFlag.flag[buffNum] |= 1 << bitNum;
}


//-------------------------------------------------------------------
void app_rx_midi_sub_pid_nick_name_h_ctl(uint8_t num, prtc_header_t *pPh, prtc_data_ctl_midi_nick_name_h_t *pData) {

	uint8_t f_newAxle = 1;

	//com_axle.axleInfo[pData->motor_num].motor_num = pData->motor_num;
	//memcpy(&com_axle.axleInfo[pData->motor_num].nick_name[0], &pData->nick_name[0], 6);

	//	//add page data
//	for (int i = 0; i < com_axle.list.cnt; i++)
//	{
//		if (com_axle.list.pAxleInfo[i]->group_num == pData->motor_num)//group
//		{
//			if (com_axle.list.pAxleInfo[i]->motor_num == pData->motor_num)
//			f_newAxle = 0;
//		}
//	}

	if(getListNum(pData->motor_id,pData->motor_sub_id) != 0xff)
	{
		f_newAxle = 0;
	}

	if(f_newAxle == 1)
	{
		//add axle data
		com_axle.axleInfo[com_axle.list.cnt].listNum = com_axle.list.cnt;

		com_axle.axleInfo[com_axle.list.cnt].motor_num = pData->motor_sub_id;
		com_axle.axleInfo[com_axle.list.cnt].group_num = pData->motor_id;

		com_axle.list.pAxleInfo[com_axle.list.cnt] = &com_axle.axleInfo[com_axle.list.cnt];
		memcpy(&com_axle.axleInfo[com_axle.list.cnt].nick_name[0], &pData->nick_name[0], 6);
		com_axle.list.cnt++;
	}


}
void app_rx_midi_sub_pid_nick_name_l_ctl(uint8_t num, prtc_header_t *pPh, prtc_data_ctl_midi_nick_name_l_t *pData) {
	//com_axle.axleInfo[pData->motor_num].motor_num = pData->motor_num;
	//memcpy(&com_axle.axleInfo[pData->motor_num].nick_name[6], &pData->nick_name[0], 4);

	uint8_t listnum = getListNum(pData->motor_id,pData->motor_sub_id);

	if(listnum != 0xff)
		memcpy(&com_axle.axleInfo[listnum].nick_name[6], &pData->nick_name[0], 4);
}

void app_rx_midi_sub_pid_range_data_ctl(uint8_t num, prtc_header_t *pPh, prtc_data_ctl_midi_range_data_t *pData) {
	//prtc_data_ctl_midi_range_data_t



//	com_axle.axleInfo[pData->motor_num].setPage[pData->set_page_num].range = pData->range;
//	com_axle.axleInfo[pData->motor_num].setPage[pData->set_page_num].max = pData->max;
//	com_axle.axleInfo[pData->motor_num].setPage[pData->set_page_num].min = pData->min;
	uint8_t listnum = getListNum(pData->motor_id,pData->motor_sub_id);

	if(listnum != 0xff)
	{
		com_axle.axleInfo[listnum].setPage.range = pData->range;
		com_axle.axleInfo[listnum].setPage.max = pData->max;
		com_axle.axleInfo[listnum].setPage.min = pData->min;
	}

}
//-------------------------------------------------------------------
void app_rx_midi_sub_pid_page_ctl(uint8_t num, prtc_header_t *pPh, prtc_data_ctl_midi_page_t *pData) {

	uint8_t f_newPage = 1;
	//data->slot_num --;
	if (pData->slot_num < 8)
	{
		uint8_t listnum = getListNum(pData->motor_id,pData->motor_sub_id);

		com_page.pageInfo[pData->page].pageNum = pData->page;
		com_page.pageInfo[pData->page].slot_axle[pData->slot_num].listNum = listnum;
		//com_page.pageInfo[pData->page].slot_axle.setPageNum = pData->set_page_num;

		//	//add page data
		for (int i = 0; i < com_page.list.cnt; i++)
		{
			if (com_page.list.pPageInfo[i]->pageNum == pData->page)
			{
				f_newPage = 0;
			}
		}
		if (f_newPage == 1)
		{
			com_page.pageInfo[pData->page].listNum = com_page.list.cnt;
			com_page.list.pPageInfo[com_page.list.cnt] = &com_page.pageInfo[pData->page];
			com_page.list.cnt++;
		}
	}
}


void app_rx_midi_sub_pid_last_page_ctl(uint8_t num, prtc_header_t *pPh, prtc_data_ctl_midi_last_page_t *pData)
{

	Set_Page(pData->last_page);

	f_v0_first = 1;//예외처리 : 녹화기 재부팅시 새로고침

}

//-------------------------------------------------------------------
void app_rx_midi_sub_pid_adc_ctl(uint8_t num, prtc_header_t *pPh,  prtc_data_ctl_midi_adc_t *pData)
{
	uint8_t slot_id = 0xFF;
	//slot_id = slide_id_check(pData->id);
	slot_id = slide_id_check_group(pData->motor_id, pData->motor_sub_id);

	if(slot_id != 0xFF)
	{
		slide_master.motorPosi[slot_id] = pData->adc_val;
/*		slide_master.motorPosi[slot_id] = map(
				pData->adc_val,
				com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].axleNum].setPage[0].min,
				com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[slot_id].axleNum].setPage[0].max);*/
		slide_master.f_motorPosi[slot_id] = 1;
		slide_master.t_motorPosi[slot_id] = HAL_GetTick();
	}

}

extern void View_0_enableRsp(uint8_t slot_id, uint16_t set_posi);
extern void View_6_enableRsp(uint8_t slot_id, uint16_t set_posi);
void app_rx_midi_sub_pid_adc_rsp(uint8_t num, prtc_header_t *pPh, prtc_data_rsp_midi_adc_t *pData)
{

	uint8_t slot_id = 0xFF;
	//slot_id = slide_id_check(pData->id);
	slot_id = slide_id_check_group(pData->motor_id, pData->motor_sub_id);

	if(slot_id != 0xFF)
	{
		switch(panel.view.nowView)
		{
			case VIEW_0_MAIN:
				View_0_enableRsp(slot_id, pData->adc_val);
				break;
			case VIEW_6_SLIDE_SETTING:
				View_6_enableRsp(slot_id, pData->adc_val);
				break;
		}
		//View_0_enableRsp(slot_id,map(pData->adc_val,500,6000,0,4095));
	}
}

//-----------------------------------------------------------------------------

//=============================================================================
#endif


#ifdef PROTOCOL_DEF

extern void View_0_enableRsp(uint8_t slot_id, uint16_t set_posi);
void CAN_App_MIDI_SlotEnable_RxRsp(uint8_t group_id, uint8_t motor_id, uint16_t value)
{
	uint8_t slot_id = 0xFF;
	slot_id = slide_id_check_group(group_id, motor_id);

	if(slot_id != 0xFF)
		View_0_enableRsp(slot_id, value);
}

void CAN_App_MIDI_AxleInfo_RxRsp(PC_CAN_MIDI_ArrayAxleInfo_Typedef *arrAxleInfo, uint32_t size)
{
	com_axle.list.cnt = 1;

	int j=0;
	for (uint16_t i = 0; i < size; i++)
	{

		com_axle.axleInfo[i].group_num = arrAxleInfo[i].group_id;
		com_axle.axleInfo[i].motor_num = arrAxleInfo[i].motor_id;
		memcpy(com_axle.axleInfo[i].nick_name, arrAxleInfo[i].name, 10);

		com_axle.axleInfo[i].setPage.range = arrAxleInfo[i].slide_range;
		com_axle.axleInfo[i].setPage.min = arrAxleInfo[i].slide_min;
		com_axle.axleInfo[i].setPage.max = arrAxleInfo[i].slide_max;

		com_axle.axleInfo[i].listNum = com_axle.list.cnt;
		com_axle.list.pAxleInfo[com_axle.list.cnt] = &com_axle.axleInfo[i];
		com_axle.list.cnt++;
	}
}

void CAN_App_MIDI_PageDownload_RxRsp(PC_CAN_MIDI_PAGE_DOWNLOAD_Rsp_Typedef *arrPageInfo, uint32_t size)
{
	com_page.list.cnt = 0;

	for(uint16_t i = 0; i < size ; i++)
	{
		com_page.pageInfo[arrPageInfo[i].PageNum].pageNum = arrPageInfo[i].PageNum;
		for(int j = 0; j < 8; j++)
		{
			uint8_t listnum = getListNum(arrPageInfo[i].slot[j].group_id,arrPageInfo[i].slot[j].motor_id);
			com_page.pageInfo[arrPageInfo[i].PageNum].slot_axle[j].listNum = listnum;
		}

		com_page.pageInfo[arrPageInfo[i].PageNum].listNum = com_page.list.cnt;
		com_page.list.pPageInfo[com_page.list.cnt] = &com_page.pageInfo[arrPageInfo[i].PageNum];
		com_page.list.cnt++;
	}
}





#endif
