/*
 * uart.c
 *
 *  Created on: Feb 3, 2021
 *      Author: shin
 */


/*
 * uart.c
 *
 *  Created on: 2021. 1. 27.
 *      Author: shin
 */



#include "main.h"

#include "uart.h"

extern UART_HandleTypeDef huart1;
MAL_UART_HandleTypeDef muart1;

MAL_UART_ManagerHandleTypeDef muartManager = {0,};

void MAL_UART_AddrRegist(MAL_UART_HandleTypeDef *muart, USART_TypeDef *instance);
void MAL_UART_HandleMatching(MAL_UART_HandleTypeDef *muart,UART_HandleTypeDef *huart);
void MAL_UART_RxAppointment(MAL_UART_HandleTypeDef *muart);
void MAL_UART_RS485Init(MAL_UART_HandleTypeDef *muart, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

static inline void MAL_UART_RS485TxEnable(MAL_UART_HandleTypeDef *muart);
static inline void MAL_UART_RS485TxDisable(MAL_UART_HandleTypeDef *muart);
static inline void MAL_UART_LED_On(MAL_UART_LedInstanceTypeDef *muartLed);
static inline void MAL_UART_LED_Off(MAL_UART_LedInstanceTypeDef *muartLed);

void MAL_UART_Process(void);
static void MAL_UART_TxQueueTransmit(MAL_UART_HandleTypeDef *muart);
void MAL_UART_SendByte(MAL_UART_HandleTypeDef *muart, uint8_t data);
void MAL_UART_SendString(MAL_UART_HandleTypeDef *muart, char *str);
void MAL_UART_SendDataStream(MAL_UART_HandleTypeDef *muart, uint8_t *dataStream, uint32_t len);
void MAL_UART_SendASCII(MAL_UART_HandleTypeDef *muart, uint32_t value);
void MAL_UART_SendHex(MAL_UART_HandleTypeDef *muart, uint32_t value, uint8_t nbsize);

/*===================================================================
 * 초기화 함수
===================================================================*/

#if 0  //init.c 양식
void MAL_UART_Init(void)
{

	//dbg uart
	MAL_UART_HandleMatching(&muart3,&huart3);
	MAL_UART_RxAppointment(&muart3);

	//md driver m1
	MAL_UART_HandleMatching(&muart4,&huart4);
	MAL_UART_RxAppointment(&muart4);
	MAL_UART_RS485Init(&muart4,M1_485EN_GPIO_Port,M1_485EN_Pin);

	//md driver m2
	MAL_UART_HandleMatching(&muart2,&huart2);
	MAL_UART_RxAppointment(&muart2);
	MAL_UART_RS485Init(&muart2,M2_485EN_GPIO_Port,M2_485EN_Pin);

}
#endif


void MAL_UART_Init(void)
{

	//dbg uart
	MAL_UART_HandleMatching(&muart1,&huart1);
	MAL_UART_RxAppointment(&muart1);

}

void MAL_UART_AddrRegist(MAL_UART_HandleTypeDef *muart, USART_TypeDef *instance)
{
	muartManager.addrRegist.list[muartManager.addrRegist.registCnt].Instance = instance;
	muartManager.addrRegist.list[muartManager.addrRegist.registCnt].pMuart = muart;

	muartManager.addrRegist.registCnt++;
	if(muartManager.addrRegist.registCnt >=UART_ADDR_REGIST_SIZE)
	{
		Error_Handler();
	}

}

/**
  * @간략      muart 헨들에 hal uart 헨들 등록
  * @매개변수 *muart 헨들
  * @매개변수 *huart 헨들
  * @반환      없음
  */
void MAL_UART_HandleMatching(MAL_UART_HandleTypeDef *muart,UART_HandleTypeDef *huart)
{
	muart->huart = huart;

	MAL_UART_AddrRegist(muart,huart->Instance);
}
/**
  * @간략      uart rx 버퍼 등록
  * @매개변수 *muart 헨들
  * @반환      없음
  */
void MAL_UART_RxAppointment(MAL_UART_HandleTypeDef *muart)
{
	while (HAL_UART_Receive_IT(muart->huart, &muart->rxBuf, 1)!= HAL_OK);
}

void MAL_UART_RS485Init(MAL_UART_HandleTypeDef *muart, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	muart->rs485.flag = MAL_UART_485ENABLE;
	muart->rs485.EN_GPIO_Port = GPIOx;
	muart->rs485.EN_Pin = GPIO_Pin;

	MAL_UART_RS485TxDisable(muart);
}

void MAL_UART_LEDInit(MAL_UART_LedInstanceTypeDef *muartLed, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState onStatus)
{
	muartLed->flag = MAL_UART_LED_ENABLE;
	muartLed->GPIO_Port = GPIOx;
	muartLed->Pin = GPIO_Pin;
	muartLed->onStatus = GPIO_PIN_RESET;

	MAL_UART_LED_Off(muartLed);
}

/*===================================================================
 * rs485함수
===================================================================*/
static inline void MAL_UART_RS485TxEnable(MAL_UART_HandleTypeDef *muart)
{
	if(muart->rs485.flag == MAL_UART_485ENABLE)
	{
		muart->rs485.EN_GPIO_Port->ODR |= muart->rs485.EN_Pin;
	}
}
static inline void MAL_UART_RS485TxDisable(MAL_UART_HandleTypeDef *muart)
{
	if(muart->rs485.flag == MAL_UART_485ENABLE)
	{
		muart->rs485.EN_GPIO_Port->ODR &= ~muart->rs485.EN_Pin;
	}
}

/*===================================================================
 * LED 함수
===================================================================*/
static inline void MAL_UART_LED_On(MAL_UART_LedInstanceTypeDef *muartLed)
{
	if(muartLed->flag == MAL_UART_LED_ENABLE)
	{
		if(muartLed->onStatus == GPIO_PIN_RESET)
			muartLed->GPIO_Port->ODR &= ~muartLed->Pin;
		else
			muartLed->GPIO_Port->ODR |= muartLed->Pin;

	}
}

static inline void MAL_UART_LED_Off(MAL_UART_LedInstanceTypeDef *muartLed)
{
	if (muartLed->flag == MAL_UART_LED_ENABLE)
	{
		if(muartLed->onStatus == GPIO_PIN_RESET)
		{
			if(muartLed->onStatus == GPIO_PIN_RESET)
				muartLed->GPIO_Port->ODR |= muartLed->Pin;
			else
				muartLed->GPIO_Port->ODR &= ~muartLed->Pin;
		}
	}
}

/*===================================================================
 * 프로세스 함수
===================================================================*/
void MAL_UART_Process(void)
{
	//MAL_UART_TxQueueTransmit(&muart3);
}

/*===================================================================
 * 송신 큐 함수
===================================================================*/
/**
  * @간략      Queue를 체크하여 송신한다
  * @매개변수 *muart
  * @반환      없음
  */
static void MAL_UART_TxQueueTransmit(MAL_UART_HandleTypeDef *muart)
{
	uint32_t size = 0;

	if(muart->txQueue.front == muart->txQueue.rear)
	{
		MAL_UART_RS485TxDisable(muart);
		MAL_UART_LED_Off(&muart->txLed);
		return;
	}


/*	if(HAL_UART_GetState(muart->huart) != HAL_UART_STATE_READY)
		return;*/

	if (muart->txQueue.front > muart->txQueue.rear)
	{
		size = muart->txQueue.front - muart->txQueue.rear;
	}
	else if (muart->txQueue.front < muart->txQueue.rear)
	{
		size = MAL_UART_QUEUE_SIZE - muart->txQueue.rear;
	}

	MAL_UART_RS485TxEnable(muart);
	MAL_UART_LED_On(&muart->txLed);
	HAL_UART_Transmit_IT(muart->huart,&muart->txQueue.queue[muart->txQueue.rear], size);
}


// xxx test 코드
/**
  * @간략      사용중인 큐 길이를 계산한다
  * @매개변수 *muart 송신 헨들
  * @반환      남은 큐 개수
  */
uint32_t MAL_UART_QueueCalc(MAL_UART_HandleTypeDef *muart)
{
	uint32_t ret = 0;

	if(muart->txQueue.front >= muart->txQueue.rear)
	{
		ret = muart->txQueue.front - muart->txQueue.rear;
	}
	else
	{
		ret = MAL_UART_QUEUE_SIZE - muart->txQueue.rear;
		ret += muart->txQueue.front;
	}
	return ret;
}


/**
  * @간략      Queue에 데이터를 추가한다
  * @매개변수 *muart 송신 헨들
  * @매개변수 data 송신 byte
  * @반환      없음
  */
void MAL_UART_SendAddQueue(MAL_UART_HandleTypeDef *muart, uint8_t data) {

/*	if(MAL_UART_QueueCalc(muart) > (MAX_UART_QUEUE_SZ-100))
		return;*/

	muart->txQueue.queue[muart->txQueue.front] = data;

	muart->txQueue.front++;
	if(muart->txQueue.front >=MAL_UART_QUEUE_SIZE)
		muart->txQueue.front = 0;
}
/**
  * @간략      바이트 송신
  * @매개변수 *muart 송신 헨들
  * @매개변수 data 송신 byte
  * @반환      없음
  */
void MAL_UART_SendByte(MAL_UART_HandleTypeDef *muart, uint8_t data) {
	MAL_UART_SendAddQueue(muart, data);
	MAL_UART_TxQueueTransmit(muart);
}
/**
  * @간략      문자열 송신
  * @매개변수 *muart 송신 헨들
  * @매개변수 *str 문자열 송신 주소 (문자열 마지막은 null 이어야함)
  * @반환      없음
  */
void MAL_UART_SendString(MAL_UART_HandleTypeDef *muart, char *str) {
	int ptr = 0;
	while (str[ptr] != 0)
		MAL_UART_SendAddQueue(muart, str[ptr++]);

	MAL_UART_TxQueueTransmit(muart);
}

/**
  * @간략      데이터열 송신
  * @매개변수 *muart 송신 헨들
  * @매개변수 *dataStream 데이터 열 버퍼 주소
  * @매개변수 len 데이터 열 길이
  * @반환      없음
  */
void MAL_UART_SendDataStream(MAL_UART_HandleTypeDef *muart, uint8_t *dataStream, uint32_t len) {
	int ptr = 0;
	while (len--)
		MAL_UART_SendAddQueue(muart, dataStream[ptr++]);

	MAL_UART_TxQueueTransmit(muart);
}
/**
  * @간략      숫자를 ASCII 코드로 변환하여 송신
  * @매개변수 *muart 송신 헨들
  * @매개변수 value (u32)숫자
  * @반환      없음
  */
void MAL_UART_SendASCII(MAL_UART_HandleTypeDef *muart, uint32_t value) {
	uint8_t buff[10] = {0,};
	uint32_t i = 9;

	if (value != 0) {

		while (value) {
			buff[i--] = (value % 10) + 0x30;
			value /= 10;
		}

		for (i = 0; i < 10; i++)
			if (buff[i])
				MAL_UART_SendAddQueue(muart, buff[i]);
	} else
		MAL_UART_SendAddQueue(muart, '0');

	MAL_UART_TxQueueTransmit(muart);
}
/**
  * @간략      숫자를 HEX ASCII 코드로 변환하여 송신
  * @매개변수 *muart 송신 헨들
  * @매개변수 value (u32)숫자
  * @매개변수 nbsize hex 자리수
  * @반환      없음
  */
void MAL_UART_SendHex(MAL_UART_HandleTypeDef *muart, uint32_t value, uint8_t nbsize) {
	uint8_t i = nbsize;
	uint8_t data;

	while (i--) {
		data = (value >> (i * 4)) & 0xF;

		if (data > 9)
			MAL_UART_SendAddQueue(muart, data - 0xA + 'A');
		else
			MAL_UART_SendAddQueue(muart, data + '0');
	}
	MAL_UART_TxQueueTransmit(muart);
}


/*===================================================================
 * 송수신함수
===================================================================*/
/**
  * @간략      uart 레지스터 번호를 입력받아 mal handle 를 리턴
  * @매개변수 uartNum 송신 헨들
  * @반환      malhandle
  */
MAL_UART_HandleTypeDef* MAL_UART_RegToMhandle(uint32_t uartNum) {

	MAL_UART_HandleTypeDef *ret = 0;

	uint8_t cntTemp = muartManager.addrRegist.registCnt;
	volatile uint8_t i = 0;
	for(i = 0; i < cntTemp; i++)
	{
		if((uint32_t)muartManager.addrRegist.list[i].Instance == uartNum)
		{
			ret = muartManager.addrRegist.list[i].pMuart;
			return ret;
		}
	}

	return ret;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	MAL_UART_HandleTypeDef *muart = MAL_UART_RegToMhandle((uint32_t)huart->Instance);
	uint32_t size = 0;

	if(muart == 0) return;

	muart->txQueue.rear += muart->huart->TxXferSize;

	if(muart->txQueue.rear >= MAL_UART_QUEUE_SIZE)
	{
		muart->txQueue.rear -= MAL_UART_QUEUE_SIZE;
	}

	if(muart->txQueue.front != muart->txQueue.rear)
	{
		if(muart->txQueue.front > muart->txQueue.rear)
		{
			size = muart->txQueue.front - muart->txQueue.rear;
		}
		else
		{
			size = MAL_UART_QUEUE_SIZE - muart->txQueue.rear;
		}
		HAL_UART_Transmit_IT(muart->huart,&muart->txQueue.queue[muart->txQueue.rear], size);
	}
	else
	{
		MAL_UART_RS485TxDisable(muart);
		MAL_UART_LED_Off(&muart->txLed);
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	MAL_UART_HandleTypeDef *muart = MAL_UART_RegToMhandle((uint32_t)huart->Instance);

	if(muart == 0) return;


	muart->rxQueue.queue[muart->rxQueue.front] = muart->rxBuf;

	muart->rxQueue.front++;
	if(muart->rxQueue.front >= MAL_UART_QUEUE_SIZE)
		muart->rxQueue.front = 0;

	while (HAL_UART_Receive_IT(huart, &muart->rxBuf, 1)!= HAL_OK)
		;

}

/*===================================================================
 * 수신큐 데이터 반환 함수
===================================================================*/
MAL_UART_QueueStatus MAL_UART_GetQueueData_Byte(MAL_UART_HandleTypeDef *muart, uint8_t *pdata)
{
	if(muart->rxQueue.front != muart->rxQueue.rear)
	{
		*pdata = muart->rxQueue.queue[muart->rxQueue.rear];

		muart->rxQueue.rear++;
		if(muart->rxQueue.rear>=MAL_UART_QUEUE_SIZE)
			muart->rxQueue.rear = 0;

		MAL_UART_LED_On(&muart->rxLed);
		return MAL_UART_CONTAIN;
	}
	MAL_UART_LED_Off(&muart->rxLed);
	return MAL_UART_EMPTY;
}






