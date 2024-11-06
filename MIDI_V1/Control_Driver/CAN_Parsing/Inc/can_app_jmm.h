/*
 * can_app_jmm.h
 *
 *  Created on: Jan 25, 2022
 *      Author: shin
 */

#ifndef CAN_PARSING_INC_CAN_APP_JMM_H_
#define CAN_PARSING_INC_CAN_APP_JMM_H_

//can jmm command---------------------------------------------------------------------------------
#define CAN_JMM_INFO_REQ			0x0100
#define CAN_JMM_INFO_RSP			0x0100

//-------------------------------------------------------------------------------------------------


#pragma pack(1)

//CAN_JMM_INFO_RSP 0x0100----------------------------------------------------------
typedef struct{
    uint8_t jms_id;
}CAN_JMM_JMS_ID_Typedef;

#pragma pack()

void MAL_CAN_JMM_HandleMatching(MAL_CAN_HandleTypeDef *mcan);

//==========================================================================CAN_JMM_INFO_REQ 0x0100
//CAN_JMM_INFO_REQ 0x0100----------------------------------------------------------
//Tx
void CAN_App_JMM_INFO_TxReq(void);
//Rx
//CAN_JMM_INFO_RSP 0x0100----------------------------------------------------------
//Tx
//Rx
//=================================================================================================

void CAN_COM_Can2Bypass_CanRxBypass(CAN_Header_TypeDef *header,uint8_t *pdata, uint8_t dlc);

#endif /* CAN_PARSING_INC_CAN_APP_JMM_H_ */
