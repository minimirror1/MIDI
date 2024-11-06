/*
 * can_app_jms.h
 *
 *  Created on: Jan 25, 2022
 *      Author: shin
 */

#ifndef CAN_PARSING_INC_CAN_APP_JMS_H_
#define CAN_PARSING_INC_CAN_APP_JMS_H_


//can jms command---------------------------------------------------------------------------------
#define JMS_POSI_DATA_REQ			0x0101

//-------------------------------------------------------------------------------------------------


#pragma pack(1)

//JMS_POSI_DATA_REQ 0x0101----------------------------------------------------------
typedef struct{
    uint16_t posi;
}CAN_JMM_JMS_POSI_DATA_Typedef;

#pragma pack()


void MAL_CAN_JMS_HandleMatching(MAL_CAN_HandleTypeDef *mcan);

//==========================================================================JMS_POSI_DATA_REQ 0x0100
//JMS_POSI_DATA_REQ 0x0100----------------------------------------------------------
//Tx
void CAN_App_JMS_POSI_DATA_TxReq(uint16_t posi);
//Rx
void CAN_App_JMS_POSI_DATA_RxReq(uint8_t canid, uint16_t posi);//week
void CAN_COM_JMS_POSI_DATA_RxReq(CAN_Header_TypeDef *pHeader, uint8_t *pdata);
//JMS_POSI_DATA_REP 0x0100----------------------------------------------------------
//Tx
//Rx
//=================================================================================================


#endif /* CAN_PARSING_INC_CAN_APP_JMS_H_ */
