/*
 * can_app_midi.h
 *
 *  Created on: Nov 16, 2021
 *      Author: shin
 */

#ifndef CAN_PARSING_INC_CAN_APP_MIDI_H_
#define CAN_PARSING_INC_CAN_APP_MIDI_H_

#include "can_header.h"
#include "can_com.h"

//can midi command---------------------------------------------------------------------------------
#define CAN_MIDI_AXLE_INFO_REQ		0x0201
#define CAN_MIDI_AXLE_INFO_RSP		0x0201

#define CAN_MIDI_SLOT_ENABLE_REQ 	0x0202
#define CAN_MIDI_SLOT_ENABLE_RSP 	0x0202

#define CAN_MIDI_SLIDE_VAL_REQ 		0x0203

#define CAN_MIDI_PAGE_DOWNLOAD_REQ  0x0204
#define CAN_MIDI_PAGE_DOWNLOAD_RSP  0x0204

#define MIDI_MOTION_TIME_CLEAR_REQ 	0x0205
#define MIDI_MOTION_TIME_CLEAR_RSP 	0x0205
//-------------------------------------------------------------------------------------------------


#pragma pack(1)


//CAN_MIDI_AXLE_INFO_RSP 0x0201----------------------------------------------------------
typedef struct{
    uint8_t group_id;
    uint8_t motor_id;
    char name[10];
    uint16_t slide_range;
    uint16_t slide_min;
    uint16_t slide_max;
}PC_CAN_MIDI_ArrayAxleInfo_Typedef;

//CAN_MIDI_SLOT_ENABLE_REQ 0x0202--------------------------------------------------------
typedef struct{
    uint8_t group_id;
    uint8_t motor_id;
}PC_CAN_MIDI_SLOT_ENABLE_Req_Typedef;

//CAN_MIDI_SLOT_ENABLE_RSP 0x0202--------------------------------------------------------
typedef struct{
    uint8_t group_id;
    uint8_t motor_id;
    uint16_t value;
}PC_CAN_MIDI_SLOT_ENABLE_Rsp_Typedef;

//CAN_SLIDE_VAL_RSP	0x0203---------------------------------------------------------------
typedef struct{
    uint8_t group_id;
    uint8_t motor_id;
    uint32_t time;
    uint16_t value;
}PC_CAN_MIDI_SLIDE_VAL_RSP_Typedef;

//CAN_MIDI_PAGE_DOWNLOAD_RSP 0x0204------------------------------------------------------
typedef struct{
    uint8_t group_id;
    uint8_t motor_id;
}PC_CAN_MIDI_PAGE_DOWNLOAD_Slot_TypeDef;
typedef struct{
    uint8_t PageNum;
    PC_CAN_MIDI_PAGE_DOWNLOAD_Slot_TypeDef slot[8];
}PC_CAN_MIDI_PAGE_DOWNLOAD_Rsp_Typedef;
//---------------------------------------------------------------------------------------


#pragma pack()


void MAL_CAN_MIDI_HandleMatching(MAL_CAN_HandleTypeDef *mcan);
//=======================================================================CAN_MIDI_AXLE_INFO_ 0x0201
//CAN_MIDI_AXLE_INFO_REQ 0x0201----------------------------------------------------------
//Tx
void CAN_App_MIDI_AxleInfo_TxReq(void);
//Rx
//CAN_MIDI_AXLE_INFO_RSP 0x0201----------------------------------------------------------
//Tx
//Rx
void CAN_App_MIDI_AxleInfo_RxRsp(PC_CAN_MIDI_ArrayAxleInfo_Typedef *arrAxleInfo, uint32_t size);//week
void CAN_COM_MIDI_AxleInfo_RxRsp(CAN_Header_TypeDef *pHeader, uint8_t *pdata, uint32_t len);
//=================================================================================================

//=====================================================================CAN_MIDI_SLOT_ENABLE_ 0x0202
//CAN_MIDI_SLOT_ENABLE_REQ 0x0202--------------------------------------------------------
//Tx
void CAN_App_MIDI_SlotEnable_TxReq(uint8_t groupId, uint8_t motorId);
//Rx
//CAN_MIDI_SLOT_ENABLE_RSP 0x0202--------------------------------------------------------
//Tx
//Rx
void CAN_App_MIDI_SlotEnable_RxRsp(uint8_t group_id, uint8_t motor_id, uint16_t value);//week
void CAN_COM_MIDI_SlotEnable_RxRsp(CAN_Header_TypeDef *pHeader, uint8_t *pdata);
//=================================================================================================

//=======================================================================CAN_MIDI_SLIDE_VAL_ 0x0203
//CAN_MIDI_SLIDE_VAL_REQ 0x0203----------------------------------------------------------
//Tx
void CAN_App_MIDI_SlideDataSend_TxReq(uint8_t groupId, uint8_t motorId, uint32_t time, uint16_t value);
//Rx
//CAN_MIDI_SLIDE_VAL_RSP 0x0203----------------------------------------------------------
//Tx
//Rx
//=================================================================================================

//===================================================================CAN_MIDI_PAGE_DOWNLOAD_ 0x0204
//CAN_MIDI_PAGE_DOWNLOAD_REQ 0x0204------------------------------------------------------
//Tx
void CAN_App_MIDI_PageDownload_TxReq(void);
//Rx
//CAN_MIDI_PAGE_DOWNLOAD_RSP 0x0204------------------------------------------------------
//Tx
//Rx
void CAN_App_MIDI_PageDownload_RxRsp(uint8_t setPage, PC_CAN_MIDI_PAGE_DOWNLOAD_Rsp_Typedef *arrPageInfo, uint32_t size);//week
void CAN_COM_MIDI_PageDownload_RxRsp(CAN_Header_TypeDef *pHeader, uint8_t *pdata, uint32_t len);
//=================================================================================================

//===================================================================MIDI_MOTION_TIME_CLEAR_ 0x0205
//MIDI_MOTION_TIME_CLEAR_REQ 0x0205------------------------------------------------------
//Tx
//Rx
void CAN_App_MIDI_MotionTimeClear_RxReq(void);//week
void CAN_COM_MIDI_MotionTimeClear_RxReq(CAN_Header_TypeDef *pHeader, uint8_t *pdata);
//MIDI_MOTION_TIME_CLEAR_RSP 0x0205------------------------------------------------------
//Tx
void CAN_COM_MIDI_MotionTimeClear_TxRsp(CAN_Header_TypeDef *pHeader);
//Rx
//=================================================================================================



#endif /* CAN_PARSING_INC_CAN_APP_MIDI_H_ */

