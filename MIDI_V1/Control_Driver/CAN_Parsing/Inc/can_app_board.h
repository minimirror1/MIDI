/*
 * can_app_board.h
 *
 *  Created on: Nov 17, 2021
 *      Author: shin
 */

#ifndef CAN_PARSING_INC_CAN_APP_BOARD_H_
#define CAN_PARSING_INC_CAN_APP_BOARD_H_

#include "can_header.h"
#include "can_com.h"
//can board command--------------------------------------------------------------------------------
#define CAN_INFORMATION_REQ		0x0000
#define CAN_INFORMATION_RSP		0x0000

#define CAN_BOOT_ALM_EVENT_REQ	0x0001
#define CAN_BOOT_ALM_EVENT_RSP	0x0001
//-------------------------------------------------------------------------------------------------

#pragma pack(1)

#pragma pack()


#pragma pack(1)
//CAN_INFORMATION_RSP 	0x0000-----------------------------------------------------------
typedef struct {
	uint8_t majorVer;
	uint8_t minorVer;
	uint8_t buildVer;
	uint8_t boardType;
} CAN_COM_InformationRsp_TypeDef;

//CAN_BOOT_ALM_EVENT_RSP 0x0001----------------------------------------------------------
typedef struct {
	uint8_t majorVer;
	uint8_t minorVer;
	uint8_t buildVer;
	uint8_t boardType;
} CAN_BOOT_ALM_EventRsp_TypeDef;
#pragma pack(0)


//==========================================================================CAN_INFORMATION_ 0x0201
//CAN_INFORMATION_REQ 0x0000-------------------------------------------------------------
//Tx
//Rx
void CAN_COM_Information_RxReq(CAN_Header_TypeDef *pHeader, uint8_t *pdata);
//CAN_INFORMATION_RSP 0x0000-------------------------------------------------------------
//Tx
void CAN_COM_Information_TxRsp(CAN_Header_TypeDef *pHeader, uint8_t *pdata);
//Rx
//=================================================================================================



//========================================================================CAN_BOOT_ALM_EVENT 0x0201
//CAN_BOOT_ALM_EVENT_REQ 0x0000-------------------------------------------------------------
//Tx
void CAN_App_BootAlm_Event_TxReq(void);
//Rx
//CAN_BOOT_ALM_EVENT_RSP 0x0000-------------------------------------------------------------
//Tx
//Rx
//=================================================================================================



#endif /* CAN_PARSING_INC_CAN_APP_BOARD_H_ */
