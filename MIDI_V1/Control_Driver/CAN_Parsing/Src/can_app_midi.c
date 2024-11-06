/*
 * can_app_midi.c
 *
 *  Created on: Nov 16, 2021
 *      Author: shin
 */
#include "main.h"
#include "can_datalink.h"

MAL_CAN_HandleTypeDef *midiCAN;
void MAL_CAN_MIDI_HandleMatching(MAL_CAN_HandleTypeDef *mcan)
{
	midiCAN = mcan;
}

//=======================================================================CAN_MIDI_AXLE_INFO_ 0x0201
//CAN_MIDI_AXLE_INFO_REQ 0x0201----------------------------------------------------------
//Tx
void CAN_App_MIDI_AxleInfo_TxReq(void)
{
	CAN_Header_TypeDef txHeader = { 0, };
	uint8_t buff[1] = {0,};


	txHeader.srcId = my_can_id;
	txHeader.tarId = CAN_MASTER_ID;
	txHeader.cmd = CAN_MIDI_AXLE_INFO_REQ;
	txHeader.cmdType = CMD_TYPE_REQ;

	MAL_CAN_SendAddQueue_ExtData(midiCAN, txHeader.Header, buff, 0);
}
//Rx
//CAN_MIDI_AXLE_INFO_RSP 0x0201----------------------------------------------------------
//Tx
//Rx
__weak void CAN_App_MIDI_AxleInfo_RxRsp(PC_CAN_MIDI_ArrayAxleInfo_Typedef *arrAxleInfo, uint32_t size)
{

}
void CAN_COM_MIDI_AxleInfo_RxRsp(CAN_Header_TypeDef *pHeader, uint8_t *pdata, uint32_t len)
{
	uint32_t arrayIndex = len/sizeof(PC_CAN_MIDI_ArrayAxleInfo_Typedef);

	CAN_App_MIDI_AxleInfo_RxRsp((PC_CAN_MIDI_ArrayAxleInfo_Typedef *)pdata, arrayIndex);
}
//=================================================================================================




//=====================================================================CAN_MIDI_SLOT_ENABLE_ 0x0202
//CAN_MIDI_SLOT_ENABLE_REQ 0x0202--------------------------------------------------------
//Tx
void CAN_App_MIDI_SlotEnable_TxReq(uint8_t groupId, uint8_t motorId)
{
	CAN_Header_TypeDef txHeader = { 0, };
	uint8_t buff[sizeof(PC_CAN_MIDI_SLOT_ENABLE_Req_Typedef)] = {0,};
	PC_CAN_MIDI_SLOT_ENABLE_Req_Typedef *data = (PC_CAN_MIDI_SLOT_ENABLE_Req_Typedef *)buff;

	txHeader.srcId = my_can_id;
	txHeader.tarId = CAN_MASTER_ID;
	txHeader.cmd = CAN_MIDI_SLOT_ENABLE_REQ;
	txHeader.cmdType = CMD_TYPE_REQ;

	data->group_id = groupId;
	data->motor_id = motorId;

	MAL_CAN_SendAddQueue_ExtData(midiCAN, txHeader.Header, buff, sizeof(PC_CAN_MIDI_SLOT_ENABLE_Req_Typedef));
}
//Rx

//CAN_MIDI_SLOT_ENABLE_RSP 0x0202--------------------------------------------------------
//Tx
//Rx
__weak void CAN_App_MIDI_SlotEnable_RxRsp(uint8_t group_id, uint8_t motor_id, uint16_t value)
{

}
void CAN_COM_MIDI_SlotEnable_RxRsp(CAN_Header_TypeDef *pHeader, uint8_t *pdata){
	PC_CAN_MIDI_SLOT_ENABLE_Rsp_Typedef *rxData = (PC_CAN_MIDI_SLOT_ENABLE_Rsp_Typedef *)pdata;

	CAN_App_MIDI_SlotEnable_RxRsp(rxData->group_id,rxData->motor_id,rxData->value);
}
//=================================================================================================




//=======================================================================CAN_MIDI_SLIDE_VAL_ 0x0203
//CAN_MIDI_SLIDE_VAL_REQ 0x0203----------------------------------------------------------
//Tx
void CAN_App_MIDI_SlideDataSend_TxReq(uint8_t groupId, uint8_t motorId, uint32_t time, uint16_t value)
{
	CAN_Header_TypeDef txHeader = { 0, };
	uint8_t buff[sizeof(PC_CAN_MIDI_SLIDE_VAL_RSP_Typedef)] = {0,};
	PC_CAN_MIDI_SLIDE_VAL_RSP_Typedef *data = (PC_CAN_MIDI_SLIDE_VAL_RSP_Typedef *)buff;

	txHeader.srcId = my_can_id;
	txHeader.tarId = CAN_MASTER_ID;
	txHeader.cmd = CAN_MIDI_SLIDE_VAL_REQ;
	txHeader.cmdType = CMD_TYPE_REQ;

	data->group_id = groupId;
	data->motor_id = motorId;
	data->time = time;
	data->value = value;

	MAL_CAN_SendAddQueue_ExtData(midiCAN, txHeader.Header, buff, sizeof(PC_CAN_MIDI_SLIDE_VAL_RSP_Typedef));
}
//Rx
//CAN_MIDI_SLIDE_VAL_RSP 0x0203----------------------------------------------------------
//Tx
//Rx
//=================================================================================================


//===================================================================CAN_MIDI_PAGE_DOWNLOAD_ 0x0204
//CAN_MIDI_PAGE_DOWNLOAD_REQ 0x0204------------------------------------------------------
//Tx
void CAN_App_MIDI_PageDownload_TxReq(void)
{
	CAN_Header_TypeDef txHeader = { 0, };
	uint8_t buff[1] = {0,};

	txHeader.srcId = my_can_id;
	txHeader.tarId = CAN_MASTER_ID;
	txHeader.cmd = CAN_MIDI_PAGE_DOWNLOAD_REQ;
	txHeader.cmdType = CMD_TYPE_REQ;

	MAL_CAN_SendAddQueue_ExtData(midiCAN, txHeader.Header, buff, 0);
}
//Rx
//CAN_MIDI_PAGE_DOWNLOAD_RSP 0x0204------------------------------------------------------
//Tx
//Rx
__weak void CAN_App_MIDI_PageDownload_RxRsp(uint8_t setPage, PC_CAN_MIDI_PAGE_DOWNLOAD_Rsp_Typedef *arrPageInfo, uint32_t size)
{

}
void CAN_COM_MIDI_PageDownload_RxRsp(CAN_Header_TypeDef *pHeader, uint8_t *pdata, uint32_t len)
{
	if(len == 0)
		return;

	uint32_t arrayIndex = (len-1)/sizeof(PC_CAN_MIDI_PAGE_DOWNLOAD_Rsp_Typedef);

	CAN_App_MIDI_PageDownload_RxRsp(pdata[0],(PC_CAN_MIDI_PAGE_DOWNLOAD_Rsp_Typedef*) &pdata[1], arrayIndex);
}
//=================================================================================================

//===================================================================MIDI_MOTION_TIME_CLEAR_ 0x0205
//MIDI_MOTION_TIME_CLEAR_REQ 0x0205------------------------------------------------------
//Tx
//Rx
__weak void CAN_App_MIDI_MotionTimeClear_RxReq(void)
{

}
void CAN_COM_MIDI_MotionTimeClear_RxReq(CAN_Header_TypeDef *pHeader, uint8_t *pdata)
{
	CAN_App_MIDI_MotionTimeClear_RxReq();
	CAN_COM_MIDI_MotionTimeClear_TxRsp(pHeader);
}
//MIDI_MOTION_TIME_CLEAR_RSP 0x0205------------------------------------------------------
//Tx
void CAN_COM_MIDI_MotionTimeClear_TxRsp(CAN_Header_TypeDef *pHeader)
{
	CAN_Header_TypeDef txHeader = { 0, };
	uint8_t buff[1] = { 0, };

	txHeader.srcId = my_can_id;
	txHeader.tarId = CAN_MASTER_ID;
	txHeader.cmd = MIDI_MOTION_TIME_CLEAR_RSP;
	txHeader.cmdType = CMD_TYPE_RSP;

	MAL_CAN_SendAddQueue_ExtData(midiCAN, txHeader.Header, buff, 0);
}
//Rx
//=================================================================================================
