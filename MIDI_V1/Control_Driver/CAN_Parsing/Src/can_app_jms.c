/*
 * can_app_jms.c
 *
 *  Created on: Jan 25, 2022
 *      Author: shin
 */
#include "main.h"
#include "can_datalink.h"

MAL_CAN_HandleTypeDef *jmsCAN;

void MAL_CAN_JMS_HandleMatching(MAL_CAN_HandleTypeDef *mcan)
{
	jmsCAN = mcan;
}



//==========================================================================JMS_POSI_DATA_REQ 0x0101
//JMS_POSI_DATA_REQ 0x0101----------------------------------------------------------
//Tx
void CAN_App_JMS_POSI_DATA_TxReq(uint16_t posi)
{
	CAN_Header_TypeDef txHeader = { 0, };
	uint8_t buff[sizeof(CAN_JMM_JMS_POSI_DATA_Typedef)] = {0,};

	CAN_JMM_JMS_POSI_DATA_Typedef *data = (CAN_JMM_JMS_POSI_DATA_Typedef *) buff;

	txHeader.srcId = my_can_id;
	txHeader.tarId = CAN_BROADCAST_ID;
	txHeader.cmd = JMS_POSI_DATA_REQ;
	txHeader.cmdType = CMD_TYPE_REQ;

	data->posi = posi;

	MAL_CAN_SendAddQueue_ExtData(jmsCAN, txHeader.Header, buff, sizeof(CAN_JMM_JMS_POSI_DATA_Typedef));
}
//Rx
__weak void CAN_App_JMS_POSI_DATA_RxReq(uint8_t canid, uint16_t posi)
{

}
void CAN_COM_JMS_POSI_DATA_RxReq(CAN_Header_TypeDef *pHeader, uint8_t *pdata)
{
	CAN_JMM_JMS_POSI_DATA_Typedef *rxData = (CAN_JMM_JMS_POSI_DATA_Typedef *)pdata;

	CAN_App_JMS_POSI_DATA_RxReq(pHeader->srcId, rxData->posi);
}
//JMS_POSI_DATA_RSP 0x0101----------------------------------------------------------
//Tx
//Rx
//=================================================================================================
