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

#include "app_pid_init_cmd.h"
#include "app_pid_midi_cmd.h"
#include "prtc_data_pid_midi.h"

extern uint8_t my_can_id;

Comm_Page_TypeDef com_page = { 0, };
Comm_Axle_TypeDef com_axle = { 0, };
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
void app_rx_midi_sub_pid_nick_name_h_ctl(uint8_t num, prtc_header_t *pPh, uint8_t *pData) {
	prtc_data_ctl_midi_nick_name_h_t *data = (prtc_data_ctl_midi_nick_name_h_t*) pData;

	com_axle.axleInfo[data->motor_num].axle_num = data->motor_num;
	memcpy(&com_axle.axleInfo[data->motor_num].nick_name[0], &data->nick_name[0], 6);

}
void app_rx_midi_sub_pid_nick_name_l_ctl(uint8_t num, prtc_header_t *pPh, uint8_t *pData) {
	prtc_data_ctl_midi_nick_name_l_t *data = (prtc_data_ctl_midi_nick_name_l_t*) pData;

	com_axle.axleInfo[data->motor_num].axle_num = data->motor_num;
	memcpy(&com_axle.axleInfo[data->motor_num].nick_name[6], &data->nick_name[0], 4);
}
void app_rx_midi_sub_pid_range_data_ctl(uint8_t num, prtc_header_t *pPh, uint8_t *pData) {
	//prtc_data_ctl_midi_range_data_t
	prtc_data_ctl_midi_range_data_t *data = (prtc_data_ctl_midi_range_data_t*) pData;

	if (data->set_page_num < AXLE_SET_PAGE)
	{
		com_axle.axleInfo[data->motor_num].setPage[data->set_page_num].max = data->max;
		com_axle.axleInfo[data->motor_num].setPage[data->set_page_num].min = data->min;
	}
}
//-------------------------------------------------------------------
void app_rx_midi_sub_pid_page_ctl(uint8_t num, prtc_header_t *pPh, uint8_t *pData) {
	prtc_data_ctl_midi_page_t *data = (prtc_data_ctl_midi_page_t*) pData;

	//pPh->sub_id --;
	if (pPh->sub_id < 8)
	{
		com_page.pageInfo[data->page].pageNum = data->page;
		com_page.pageInfo[data->page].slot_axle[pPh->sub_id].axleNum = data->motor_num;
		com_page.pageInfo[data->page].slot_axle[pPh->sub_id].setPageNum = data->set_page_num;
	}
}

//=============================================================================
