/*
 * can_protocol.h
 *
 *  Created on: 2021. 10. 27.
 *      Author: shin
 */

#ifndef CAN_COM_INC_CAN_COMMAND_H_
#define CAN_COM_INC_CAN_COMMAND_H_



//include application layer//----------------------------------------------------------------------
#include "can_app_board.h"
#include "can_app_midi.h"
#include "can_app_jmm.h"
#include "can_app_jms.h"

#include "string.h"

//-------------------------------------------------------------------------------------------------

#define CAN_MASTER_ID	0
#define CAN_BROADCAST_ID    0xff

#define CMD_TYPE_REQ	0
#define CMD_TYPE_RSP	1




#pragma pack(1)
//=============================================================================
//stream
typedef enum{
    STREAM_WAIT = 0,
    STREAM_START,
    STREAM_DATA,
    STREAM_END
}ArqSequence_TypeDef;

typedef struct{
    uint16_t indexNum;
    uint8_t data[6];
}CAN_Stream_RxData_TypeDef;

typedef struct{
    uint16_t indexNum;
    uint8_t ack;    //nack 0,  ack 1
}CAN_Stream_TxData_TypeDef;

typedef struct{
	ArqSequence_TypeDef seq;

	uint32_t rxIndex;
	uint32_t okIndex;
	uint32_t nowIndex;
	uint32_t endIndex;

	uint16_t cmd;


	uint32_t nackCnt;

	uint32_t dataLen;
	uint8_t buff[1000];
}CAN_Stream_TypeDef;


//=============================================================================



#pragma pack()


#ifdef CAN1_ENABLE
extern MAL_CAN_HandleTypeDef mcan1;
#endif
#ifdef CAN2_ENABLE
extern MAL_CAN_HandleTypeDef mcan2;
#endif

void CAN_COM_Parsing(uint8_t canCh, CAN_RxHeaderTypeDef *header, uint8_t *pdata);

//can_app_midi


#endif /* CAN_COM_INC_CAN_COMMAND_H_ */
