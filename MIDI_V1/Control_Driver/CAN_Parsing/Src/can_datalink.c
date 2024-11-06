/*
 * can_protocol.c
 *
 *  Created on: 2021. 10. 27.
 *      Author: shin
 */


#include "main.h"



//#include "communication_info.h"

#include "can_datalink.h"

#ifdef PROTOCOL_DEF


CAN_Stream_TypeDef stream1;
extern uint8_t my_can_id;

//extern Comm_Page_TypeDef com_page;
//extern Comm_Axle_TypeDef com_axle;


//command classification---------------------------------------------------------------------------
void CAN_COM_Data(uint8_t canCh, CAN_Header_TypeDef  *pHeader, uint8_t *pdata,uint32_t len)
{
	if (pHeader->cmdType == CMD_TYPE_REQ)
	{
		switch (pHeader->cmd)
		{
//Board----------------------------------------------------------------------------------
			case CAN_INFORMATION_REQ:
				CAN_COM_Information_RxReq(pHeader, pdata);
				break;

//MIDI-----------------------------------------------------------------------------------
#if (BOARD_TYPE == 1)
			case MIDI_MOTION_TIME_CLEAR_REQ:
				CAN_COM_MIDI_MotionTimeClear_RxReq(pHeader, pdata);
				break;
#endif
//JMS------------------------------------------------------------------------------------
#if (BOARD_TYPE == 2)
			case JMS_POSI_DATA_REQ:
				//CAN_COM_Can2Bypass_CanRxBypass(pHeader, pdata, len);
				CAN_COM_JMS_POSI_DATA_RxReq(pHeader, pdata);
				break;
			/*default :
				CAN_COM_Can2Bypass_CanRxBypass(pHeader, pdata, len);
				break;*/

#endif
		}
	}
	else if (pHeader->cmdType == CMD_TYPE_RSP)
	{
		switch (pHeader->cmd)
		{
//Board----------------------------------------------------------------------------------
			case CAN_INFORMATION_RSP:
				break;

//MIDI-----------------------------------------------------------------------------------
#if (BOARD_TYPE == 1)
			case CAN_MIDI_SLOT_ENABLE_RSP:
				CAN_COM_MIDI_SlotEnable_RxRsp(pHeader, pdata);
				break;
			case CAN_MIDI_AXLE_INFO_RSP:
				CAN_COM_MIDI_AxleInfo_RxRsp(pHeader, pdata, len);
				break;
			case CAN_MIDI_PAGE_DOWNLOAD_RSP:
				CAN_COM_MIDI_PageDownload_RxRsp(pHeader, pdata, len);
				break;
#endif
		}
	}
}
//-------------------------------------------------------------------------------------------------

void CAN_COM_RxStream(uint8_t canCh, CAN_Header_TypeDef *rxHeader, uint8_t *pdata, uint8_t dlc) {



	CAN_Header_TypeDef txHeader = { 0, };

	uint8_t buff[sizeof(CAN_COM_InformationRsp_TypeDef)] = { 0, };
	CAN_Stream_TxData_TypeDef *pData = (CAN_Stream_TxData_TypeDef*)buff;

	CAN_Stream_RxData_TypeDef *data = (CAN_Stream_RxData_TypeDef*)pdata;


	stream1.rxIndex = data->indexNum;

	if(data->indexNum == 0)
	{
		stream1.seq = STREAM_START;

		stream1.nowIndex = 1;

		uint16_t *endIndex = (uint16_t *)data->data;

		stream1.endIndex = *endIndex;
		stream1.cmd = rxHeader->cmd;

		txHeader.srcId = 1;
		txHeader.tarId = rxHeader->srcId;
		txHeader.cmd = stream1.cmd;
		txHeader.stream = 1;

		pData->indexNum = stream1.nowIndex;
		pData->ack = 1;

		stream1.nackCnt = 0;
	}
	else
	{
		if(data->indexNum == stream1.nowIndex)
		{
			memcpy(&stream1.buff[(stream1.nowIndex-1)*6], data->data , 6);

			if(data->indexNum == stream1.endIndex)
			{
				stream1.dataLen = (stream1.endIndex-1)*6;
				stream1.dataLen += dlc;

				CAN_COM_Data(canCh,rxHeader,stream1.buff,stream1.dataLen);

			}
			stream1.seq = STREAM_DATA;
			stream1.nowIndex = data->indexNum + 1;//다음 데이터 요청

			txHeader.srcId = 1;
			txHeader.tarId = rxHeader->srcId;
			txHeader.cmd = stream1.cmd;
			txHeader.stream = 1;

			pData->indexNum = stream1.nowIndex;
			pData->ack = 1; //ack
		}
		else
		{
			stream1.nackCnt++;

			txHeader.srcId = 1;
			txHeader.tarId = rxHeader->srcId;
			txHeader.cmd = stream1.cmd;
			txHeader.stream = 1;

			pData->indexNum = stream1.nowIndex;
			pData->ack = 0; //nack
		}
	}

	MAL_CAN_SendAddQueue_ExtData(&mcan1, txHeader.Header, buff, sizeof(CAN_COM_InformationRsp_TypeDef));

}


void CAN_COM_Parsing(uint8_t canCh, CAN_RxHeaderTypeDef *header, uint8_t *pdata) {

	CAN_Header_TypeDef *pHeader = (CAN_Header_TypeDef*) &header->ExtId;

	if((pHeader->tarId == my_can_id)||(pHeader->tarId == CAN_BROADCAST_ID))
	{

		if (pHeader->stream == 1)
		{
			CAN_COM_RxStream(canCh, pHeader, pdata, header->DLC);
			return;
		}
		else
		{
			CAN_COM_Data(canCh, pHeader,pdata,header->DLC);
		}
	}
}

#endif
