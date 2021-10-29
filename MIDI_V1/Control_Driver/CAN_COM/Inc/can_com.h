/*
 * can_com.h
 *
 *  Created on: 2021. 10. 27.
 *      Author: shin
 */

#ifndef CAN_COM_INC_CAN_COM_H_
#define CAN_COM_INC_CAN_COM_H_


#define CAN_ADDR_REGIST_SIZE 2

#define MAL_CAN_QUEUE_SIZE	128


typedef enum __MAL_CAN_QueueStatus
{
	MAL_EMPTY,
	MAL_CONTAIN
}MAL_CAN_QueueStatus;

typedef enum __MAL_CAN_LEDControlTypeDef
{
	MAL_CAN_LED_DISABLE = 0,
	MAL_CAN_LED_ENABLE
}MAL_CAN_LEDControlTypeDef;

// tx queue
#pragma pack(1)
typedef struct __MAL_CAN_TxDataTypeDef
{
	CAN_TxHeaderTypeDef header;
	uint8_t data[8];
}MAL_CAN_TxDataTypeDef;
#pragma pack()
#pragma pack(1)
typedef struct __MAL_CAN_TxQueueTypeDef
{
	uint32_t 	front;
	uint32_t	rear;
	MAL_CAN_TxDataTypeDef 	queue[MAL_CAN_QUEUE_SIZE];
}MAL_CAN_TxQueueTypeDef;
#pragma pack()

//rx queue
#pragma pack(1)
typedef struct __MAL_CAN_RxDataTypeDef
{
	CAN_RxHeaderTypeDef header;
	uint8_t data[8];
}MAL_CAN_RxDataTypeDef;
#pragma pack()
#pragma pack(1)
typedef struct __MAL_CAN_RxQueueTypeDef
{
	uint32_t 	front;
	uint32_t	rear;
	MAL_CAN_RxDataTypeDef 	queue[MAL_CAN_QUEUE_SIZE];
}MAL_CAN_RxQueueTypeDef;
#pragma pack()


#pragma pack(1)
typedef struct __MAL_CAN_LedInstanceTypeDef
{
	MAL_CAN_LEDControlTypeDef flag;
	GPIO_PinState	onStatus;
	GPIO_TypeDef* 	GPIO_Port;
	uint16_t 		Pin;
}MAL_CAN_LedInstanceTypeDef;
#pragma pack()


#pragma pack(1)
typedef struct __MAL_CAN_HandleTypeDef
{
	CAN_HandleTypeDef *hcan;				/*hal can handle*/

	MAL_CAN_TxQueueTypeDef txQueue;
	MAL_CAN_RxQueueTypeDef rxQueue;

	MAL_CAN_LedInstanceTypeDef txLed;
	MAL_CAN_LedInstanceTypeDef rxLed;

	uint32_t txMailbox;
}MAL_CAN_HandleTypeDef;
#pragma pack()


/* CAN manager*/
#pragma pack(1)
typedef struct __MAL_CAN_RegistrationListTypeDef
{
	CAN_TypeDef *Instance;
	MAL_CAN_HandleTypeDef *pmcan;
}MAL_CAN_RegistrationListTypeDef;
#pragma pack()

#pragma pack(1)
typedef struct __MAL_CAN_AddressRegistTypeDef
{
	MAL_CAN_RegistrationListTypeDef list[CAN_ADDR_REGIST_SIZE];
	uint8_t registCnt;
}MAL_CAN_AddressRegistTypeDef;
#pragma pack()

#pragma pack(1)
typedef struct __MAL_CAN_ManagerHandleTypeDef
{
	MAL_CAN_AddressRegistTypeDef addrRegist;
}MAL_CAN_ManagerHandleTypeDef;
#pragma pack()
/* CAN manager*/


extern void MAL_CAN1_Init(void);
extern void MAL_CAN_LED_Off(MAL_CAN_LedInstanceTypeDef *mcanLed);
extern void MAL_CAN_LED_RX_On(MAL_CAN_HandleTypeDef *mcan);
extern void MAL_CAN_LEDInit(MAL_CAN_LedInstanceTypeDef *mcanLed, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState onStatus);
extern void MAL_CAN_FilterConfig(CAN_HandleTypeDef *hcan);
extern void MAL_CAN_HandleMatching(MAL_CAN_HandleTypeDef *mcan,CAN_HandleTypeDef *hcan);
extern void MAL_CAN_Process(void);
extern void MAL_CAN_SendAddQueue_ExtData(MAL_CAN_HandleTypeDef *mcan,uint32_t id, uint8_t *pdata, uint8_t size);
extern MAL_CAN_QueueStatus MAL_CAN_GetQueuePacket(MAL_CAN_HandleTypeDef *mcan,CAN_RxHeaderTypeDef *header,uint8_t *pdata);


#endif /* CAN_COM_INC_CAN_COM_H_ */
