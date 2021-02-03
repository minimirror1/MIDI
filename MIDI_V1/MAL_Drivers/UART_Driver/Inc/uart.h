/*
 * uart.h
 *
 *  Created on: Feb 3, 2021
 *      Author: shin
 */

#ifndef UART_DRIVER_INC_UART_H_
#define UART_DRIVER_INC_UART_H_


//-----SETTING-------------------------------------------------------



//DATA BUFF SIZE
#define MAL_UART_QUEUE_SIZE	1024

#define UART_ADDR_REGIST_SIZE  10
//-------------------------------------------------------------------

//=============================================================================

typedef enum __MAL_UART_QueueStatus
{
	MAL_UART_EMPTY = 0,
	MAL_UART_CONTAIN
}MAL_UART_QueueStatus;

typedef enum __MAL_UART_485ControlTypeDef
{
	MAL_UART_485DISABLE = 0,
	MAL_UART_485ENABLE
}MAL_UART_485ControlTypeDef;

typedef enum __MAL_UART_LEDControlTypeDef
{
	MAL_UART_LED_DISABLE = 0,
	MAL_UART_LED_ENABLE
}MAL_UART_LEDControlTypeDef;


#pragma pack(1)
typedef struct __MAL_UART_QueueTypeDef
{
	uint32_t 	front;
	uint32_t	rear;
	uint8_t 	queue[MAL_UART_QUEUE_SIZE];
}MAL_UART_QueueTypeDef;
#pragma pack()

#pragma pack(1)
typedef struct __MAL_UART_485InstanceTypeDef
{
	MAL_UART_485ControlTypeDef flag;
	GPIO_TypeDef* 	EN_GPIO_Port;
	uint16_t 		EN_Pin;
}MAL_UART_485InstanceTypeDef;
#pragma pack()

#pragma pack(1)
typedef struct __MAL_UART_LedInstanceTypeDef
{
	MAL_UART_LEDControlTypeDef flag;
	GPIO_PinState	onStatus;
	GPIO_TypeDef* 	GPIO_Port;
	uint16_t 		Pin;
}MAL_UART_LedInstanceTypeDef;
#pragma pack()

/*
#pragma pack(1)
typedef struct __MAL_UART_CommStatusTypeDef
{
	uint8_t		Mode;
	uint16_t 	Len;
	uint8_t 	PollMode;
	uint8_t 	TimoutMode;
	uint32_t 	TxTime;
	uint32_t 	RxTime;
}MAL_UART_CommStatusTypeDef;
#pragma pack()
*/


#pragma pack(1)
typedef struct __MAL_UART_HandleTypeDef
{
	UART_HandleTypeDef *huart;				/*hal uart handle*/

	//MAL_UART_CommStatusTypeDef commStatus;	/**/

	MAL_UART_QueueTypeDef txQueue;
	MAL_UART_QueueTypeDef rxQueue;

	uint8_t rxBuf;

	MAL_UART_485InstanceTypeDef rs485;

	MAL_UART_LedInstanceTypeDef txLed;
	MAL_UART_LedInstanceTypeDef rxLed;

}MAL_UART_HandleTypeDef;
#pragma pack()


/* uart manager*/
#pragma pack(1)
typedef struct __MAL_UART_RegistrationListTypeDef
{
	USART_TypeDef *Instance;
	MAL_UART_HandleTypeDef *pMuart;
}MAL_UART_RegistrationListTypeDef;
#pragma pack()

#pragma pack(1)
typedef struct __MAL_UART_AddressRegistTypeDef
{
	MAL_UART_RegistrationListTypeDef list[UART_ADDR_REGIST_SIZE];
	uint8_t registCnt;
}MAL_UART_AddressRegistTypeDef;
#pragma pack()

#pragma pack(1)
typedef struct __MAL_UART_ManagerHandleTypeDef
{
	MAL_UART_AddressRegistTypeDef addrRegist;
}MAL_UART_ManagerHandleTypeDef;
#pragma pack()
/* uart manager*/


void MAL_UART_Init(void);
void MAL_UART_HandleMatching(MAL_UART_HandleTypeDef *muart,UART_HandleTypeDef *huart);
void MAL_UART_RxAppointment(MAL_UART_HandleTypeDef *muart);
void MAL_UART_RS485Init(MAL_UART_HandleTypeDef *muart, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void MAL_UART_LEDInit(MAL_UART_LedInstanceTypeDef *muartLed, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState onStatus);
void MAL_UART_Process(void);
void MAL_UART_SendByte(MAL_UART_HandleTypeDef *muart, uint8_t data);
void MAL_UART_SendString(MAL_UART_HandleTypeDef *muart, char *str);
void MAL_UART_SendDataStream(MAL_UART_HandleTypeDef *muart, uint8_t *dataStream, uint32_t len);
void MAL_UART_SendASCII(MAL_UART_HandleTypeDef *muart, uint32_t value);
void MAL_UART_SendHex(MAL_UART_HandleTypeDef *muart, uint32_t value, uint8_t nbsize);
MAL_UART_QueueStatus MAL_UART_GetQueueData_Byte(MAL_UART_HandleTypeDef *muart, uint8_t *pdata);



#endif /* UART_DRIVER_INC_UART_H_ */
