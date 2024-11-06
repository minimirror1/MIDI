/*
 * can_app_board.c
 *
 *  Created on: Nov 17, 2021
 *      Author: shin
 */
#include "main.h"
#include "can_datalink.h"

//==========================================================================CAN_INFORMATION_ 0x0201
//CAN_INFORMATION_REQ 0x0000-------------------------------------------------------------
//Tx
//Rx
void CAN_COM_Information_RxReq(CAN_Header_TypeDef *pHeader, uint8_t *pdata) {

	CAN_COM_Information_TxRsp(pHeader, pdata);
}
//CAN_INFORMATION_RSP 0x0000-------------------------------------------------------------
//Tx
void CAN_COM_Information_TxRsp(CAN_Header_TypeDef *pHeader, uint8_t *pdata)
{
	CAN_Header_TypeDef txHeader = { 0, };

	uint8_t buff[sizeof(CAN_COM_InformationRsp_TypeDef)] = { 0, };
	CAN_COM_InformationRsp_TypeDef *data = (CAN_COM_InformationRsp_TypeDef*) buff;

	txHeader.srcId = 1;
	txHeader.tarId = pHeader->srcId;
	txHeader.cmd = CAN_INFORMATION_RSP;

	char str[] = FW_VER_STR;
	char *verStr = strtok(str, ".");

	data->majorVer = *verStr - 0x30;
	verStr = strtok(NULL, ".");
	data->minorVer = *verStr - 0x30;
	verStr = strtok(NULL, "v");
	data->buildVer = *verStr - 0x30;

	data->boardType = BOARD_TYPE;

	MAL_CAN_SendAddQueue_ExtData(&mcan1, txHeader.Header, buff, sizeof(CAN_COM_InformationRsp_TypeDef));
}
//Rx
//=================================================================================================



//========================================================================CAN_BOOT_ALM_EVENT 0x0201
//CAN_BOOT_ALM_EVENT_REQ 0x0000-------------------------------------------------------------
//Tx
void CAN_App_BootAlm_Event_TxReq(void) {
	CAN_Header_TypeDef txHeader = { 0, };

	uint8_t buff[sizeof(CAN_BOOT_ALM_EventRsp_TypeDef)] = { 0, };
	CAN_BOOT_ALM_EventRsp_TypeDef *data = (CAN_BOOT_ALM_EventRsp_TypeDef*) buff;

	txHeader.srcId = my_can_id;
	txHeader.tarId = CAN_MASTER_ID;
	txHeader.cmd = CAN_BOOT_ALM_EVENT_REQ;

	char str[] = FW_VER_STR;
	char *verStr = strtok(str, ".");

	data->majorVer = *verStr - 0x30;
	verStr = strtok(NULL, ".");
	data->minorVer = *verStr - 0x30;
	verStr = strtok(NULL, "v");
	data->buildVer = *verStr - 0x30;

	data->boardType = BOARD_TYPE;

	MAL_CAN_SendAddQueue_ExtData(&mcan1, txHeader.Header, buff, sizeof(CAN_COM_InformationRsp_TypeDef));
}
//Rx
//CAN_BOOT_ALM_EVENT_RSP 0x0000-------------------------------------------------------------
//Tx
//Rx
//=================================================================================================

