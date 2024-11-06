/*
 * can_app_jmm.c
 *
 *  Created on: Jan 25, 2022
 *      Author: shin
 */
#include "main.h"
#if (BOARD_TYPE==2)
#include "can_datalink.h"
#include "uart_datalink_parsing.h"

MAL_CAN_HandleTypeDef *jmmCAN;
void MAL_CAN_JMM_HandleMatching(MAL_CAN_HandleTypeDef *mcan)
{
	jmmCAN = mcan;
}

//==========================================================================CAN_JMM_INFO_REQ 0x0100
//CAN_JMM_INFO_REQ 0x0100----------------------------------------------------------
//Tx
void CAN_App_JMM_INFO_TxReq(void)
{
	CAN_Header_TypeDef txHeader = { 0, };
	uint8_t buff[1] = {0,};


	txHeader.srcId = my_can_id;
	txHeader.tarId = CAN_BROADCAST_ID;
	txHeader.cmd = CAN_JMM_INFO_REQ;
	txHeader.cmdType = CMD_TYPE_REQ;

	MAL_CAN_SendAddQueue_ExtData(jmmCAN, txHeader.Header, buff, 0);
}
//Rx
//CAN_JMM_INFO_RSP 0x0100----------------------------------------------------------
//Tx
//Rx
//=================================================================================================

//jmm can -> lcd

void CAN_COM_Can2Bypass_CanRxBypass(CAN_Header_TypeDef *header,uint8_t *pdata, uint8_t dlc)
{

	uint8_t buff[sizeof(UART_CAN_Header_TypeDef)+8] = {0,};

	UART_CAN_Header_TypeDef *pheader = (UART_CAN_Header_TypeDef*)buff;

	pheader->canCh = 1;//can2
	pheader->canHeader.Header = header->Header;

	if(dlc <=8)
		memcpy(pheader->payload, pdata,dlc);


	UART_App_CAN2_Bypass_RecvData_TxReq(buff,sizeof(UART_CAN_Header_TypeDef)+dlc);
}
#endif
