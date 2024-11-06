/*
 * can_com.c
 *
 *  Created on: 2021. 10. 27.
 *      Author: shin
 */
#include "main.h"
#ifdef PROTOCOL_DEF
#include "can_com.h"
#include <string.h>

MAL_CAN_ManagerHandleTypeDef mcanManager = {0,};


void MAL_CAN_AddrRegist(MAL_CAN_HandleTypeDef *mcan, CAN_TypeDef *instance);
void MAL_CAN_FilterConfig(CAN_HandleTypeDef *hcan);
void MAL_CAN_HandleMatching(MAL_CAN_HandleTypeDef *mcan,CAN_HandleTypeDef *hcan);
void MAL_CAN_Process(void);
void MAL_CAN_TxQueueTransmit(MAL_CAN_HandleTypeDef *mcan);
void MAL_CAN_SendAddQueue_ExtData(MAL_CAN_HandleTypeDef *mcan,uint32_t extId, uint8_t *pdata, uint8_t size);
MAL_CAN_QueueStatus MAL_CAN_GetQueuePacket(MAL_CAN_HandleTypeDef *mcan,CAN_RxHeaderTypeDef *header,uint8_t *pdata);
static MAL_CAN_HandleTypeDef* MAL_CAN_RegToMhandle(uint32_t canNum);




__weak void CAN_COM_Parsing(uint8_t canCh,CAN_RxHeaderTypeDef *header,uint8_t *pdata)
{

}



/*===================================================================
 * 초기화 함수
===================================================================*/
#if 0  //init.c 양식
/**
  * @간략      mal드라이버 초기화
  * @반환      없음
  */
void MAL_CAN1_Init(void)
{
	MAL_CAN_FilterConfig(&hcan1);
	MAL_CAN_HandleMatching(&mcan1,&hcan1);
}
#endif

void MAL_CAN_AddrRegist(MAL_CAN_HandleTypeDef *mcan, CAN_TypeDef *instance)
{
	mcanManager.addrRegist.list[mcanManager.addrRegist.registCnt].Instance = instance;
	mcanManager.addrRegist.list[mcanManager.addrRegist.registCnt].pmcan = mcan;

	mcanManager.addrRegist.registCnt++;
	if(mcanManager.addrRegist.registCnt >CAN_ADDR_REGIST_SIZE)
	{
		Error_Handler();
	}

}
/**
  * @간략      filter config
  * @매개변수 *hcan
  * @반환      없음
  */
void MAL_CAN_FilterConfig(CAN_HandleTypeDef *hcan)
{
	CAN_FilterTypeDef  sFilterConfig;

	/*##-2- Configure the CAN Filter ###########################################*/
#ifdef CAN1
	if(hcan->Instance == CAN1)
#else
	if(hcan->Instance == CAN)
#endif
	{
		sFilterConfig.FilterBank = 0;
		sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
		sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
		sFilterConfig.FilterIdHigh = 0x0000;
		sFilterConfig.FilterIdLow = 0x0000;
		sFilterConfig.FilterMaskIdHigh = 0x0000;
		sFilterConfig.FilterMaskIdLow = 0x0000;
		sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
		sFilterConfig.FilterActivation = ENABLE;
		sFilterConfig.SlaveStartFilterBank = 14;
	}
	else
	{
		sFilterConfig.FilterBank = 14;
		sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
		sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
		sFilterConfig.FilterIdHigh = 0x0000;
		sFilterConfig.FilterIdLow = 0x0000;
		sFilterConfig.FilterMaskIdHigh = 0x0000;
		sFilterConfig.FilterMaskIdLow = 0x0000;
		sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
		sFilterConfig.FilterActivation = ENABLE;
		sFilterConfig.SlaveStartFilterBank = 14;
	}

	if (HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
	{
		/* Filter configuration Error */
		Error_Handler();
	}

	/*##-3- Start the CAN peripheral ###########################################*/
	if (HAL_CAN_Start(hcan) != HAL_OK)
	{
		/* Start Error */
		Error_Handler();
	}

	/*##-4- Activate CAN RX notification #######################################*/
	if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		/* Notification Error */
		Error_Handler();
	}
}

/**
  * @간략      mal handle 등록
  * @매개변수 *mcan
  * @매개변수 *hcan
  * @반환      없음
  */
void MAL_CAN_HandleMatching(MAL_CAN_HandleTypeDef *mcan,CAN_HandleTypeDef *hcan)
{
	mcan->hcan = hcan;

	MAL_CAN_AddrRegist(mcan, hcan->Instance);
}

/*===================================================================
 * LED 함수
===================================================================*/
void MAL_CAN_LED_On(MAL_CAN_LedInstanceTypeDef *mcanLed)
{
	if(mcanLed->flag == MAL_CAN_LED_ENABLE)
	{
		if(mcanLed->onStatus == GPIO_PIN_RESET)
			mcanLed->GPIO_Port->ODR &= ~mcanLed->Pin;
		else
			mcanLed->GPIO_Port->ODR |= mcanLed->Pin;

	}
}

void MAL_CAN_LED_RX_On(MAL_CAN_HandleTypeDef *mcan)
{
	MAL_CAN_LED_On(&mcan->rxLed);
}

void MAL_CAN_LED_Off(MAL_CAN_LedInstanceTypeDef *mcanLed)
{
	if (mcanLed->flag == MAL_CAN_LED_ENABLE)
	{
		if(mcanLed->onStatus == GPIO_PIN_RESET)
		{
			if(mcanLed->onStatus == GPIO_PIN_RESET)
				mcanLed->GPIO_Port->ODR |= mcanLed->Pin;
			else
				mcanLed->GPIO_Port->ODR &= ~mcanLed->Pin;
		}
	}
}

void MAL_CAN_LEDInit(MAL_CAN_LedInstanceTypeDef *mcanLed, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState onStatus)
{
	mcanLed->flag = MAL_CAN_LED_ENABLE;
	mcanLed->GPIO_Port = GPIOx;
	mcanLed->Pin = GPIO_Pin;
	mcanLed->onStatus = onStatus;

	MAL_CAN_LED_Off(mcanLed);
}

//============================================

/*===================================================================
 * 프로세스 함수
===================================================================*/
void MAL_CAN_Process(void)
{
	uint8_t i = 0;
	CAN_RxHeaderTypeDef header;
	uint8_t data[8] = {0,};

	for(i = 0; i<mcanManager.addrRegist.registCnt; i++)
	{
		//MAL_CAN_TxQueueTransmit(mcanManager.addrRegist.list[i].pmcan);
		if(MAL_CAN_GetQueuePacket(mcanManager.addrRegist.list[i].pmcan,&header,data) == MAL_CONTAIN)
		{
			CAN_COM_Parsing(i,&header,data);//0=can1
		}
	}
}

/*===================================================================
 * 송신함수
===================================================================*/


/**
  * @간략      Queue를 체크하여 송신한다
  * @매개변수 *mcan
  * @반환      없음
  */
void MAL_CAN_TxQueueTransmit(MAL_CAN_HandleTypeDef *mcan)
{
	if(mcan->txQueue.front == mcan->txQueue.rear)
		return;

	//비어있는 mailBox가 없으면 리턴한다.
	if(HAL_CAN_GetTxMailboxesFreeLevel(mcan->hcan) == 0)
		return;

	if(HAL_CAN_AddTxMessage(mcan->hcan,&mcan->txQueue.queue[mcan->txQueue.rear].header,(uint8_t *) &mcan->txQueue.queue[mcan->txQueue.rear].data[0],
			&mcan->txMailbox) == HAL_OK)
	{
		MAL_CAN_LED_On(&mcan->txLed);
		mcan->txQueue.rear++;
		if(mcan->txQueue.rear >=MAL_CAN_QUEUE_SIZE)
			mcan->txQueue.rear = 0;
	}
	MAL_CAN_LED_Off(&mcan->txLed);
	//HAL_OK 가 아닐경우 버퍼위치를 이동시키지 않는다. 다음에 재전송

}

/**
  * @간략      Queue에 데이터를 추가한다
  * @매개변수 *mcan 송신 헨들
  * @매개변수 id can id 필드 데이터
  * @매개변수 *pdata 전송될 데이터
  * @매개변수 size pdata 길이
  * @반환      없음
  */
void MAL_CAN_SendAddQueue_ExtData(MAL_CAN_HandleTypeDef *mcan,uint32_t extId, uint8_t *pdata, uint8_t size) {

	if(size > 8)
		return;

	MAL_CAN_TxDataTypeDef *pQueue;
	pQueue = (MAL_CAN_TxDataTypeDef *)&mcan->txQueue.queue[mcan->txQueue.front].header;

	pQueue->header.ExtId = extId;
	pQueue->header.IDE = CAN_ID_EXT;
	pQueue->header.RTR = CAN_RTR_DATA;
	pQueue->header.DLC = size;
	pQueue->header.StdId = 0;

	memset(pQueue->data,0x00,8);
	memcpy(pQueue->data,pdata,size);

	mcan->txQueue.front++;
	if(mcan->txQueue.front >=MAL_CAN_QUEUE_SIZE)
		mcan->txQueue.front = 0;

	MAL_CAN_TxQueueTransmit(mcan);
}


/*===================================================================
 * 데이터 반환 함수
===================================================================*/
MAL_CAN_QueueStatus MAL_CAN_GetQueuePacket(MAL_CAN_HandleTypeDef *mcan,CAN_RxHeaderTypeDef *header,uint8_t *pdata)
{
	if(mcan->rxQueue.front != mcan->rxQueue.rear)
	{
		*header = mcan->rxQueue.queue[mcan->rxQueue.rear].header;
		memcpy(header,&mcan->rxQueue.queue[mcan->rxQueue.rear].header,sizeof(CAN_RxHeaderTypeDef));
		memcpy(pdata,&mcan->rxQueue.queue[mcan->rxQueue.rear].data[0],header->DLC);

		mcan->rxQueue.rear++;
		if(mcan->rxQueue.rear >=MAL_CAN_QUEUE_SIZE)
			mcan->rxQueue.rear = 0;
		MAL_CAN_LED_Off(&mcan->rxLed);
		return MAL_CONTAIN;
	}
	return MAL_EMPTY;
}



/*===================================================================
 * 송수신함수
===================================================================*/
/**
  * @간략      can 레지스터 주소를 입력받아 mal handle 를 리턴
  * @매개변수 canNum 송신 헨들
  * @반환      malhandle
  */
static MAL_CAN_HandleTypeDef* MAL_CAN_RegToMhandle(uint32_t canNum)
{
	MAL_CAN_HandleTypeDef *ret = 0;

	uint8_t cntTemp = mcanManager.addrRegist.registCnt;
	volatile uint8_t i = 0;
	for(i = 0; i < cntTemp; i++)
	{
		if((uint32_t)mcanManager.addrRegist.list[i].Instance == canNum)
		{
			ret = mcanManager.addrRegist.list[i].pmcan;
			return ret;
		}
	}

	return ret;
}

#ifdef PROTOCOL_DEF1
void HAL_CAN_RxFifo0MsgPendingCallback1(CAN_HandleTypeDef *hcan)
{
	MAL_CAN_HandleTypeDef *mcan = MAL_CAN_RegToMhandle((uint32_t)hcan->Instance);

	if(mcan == 0) return;

	if(HAL_CAN_GetRxMessage(mcan->hcan, CAN_RX_FIFO0, &mcan->rxQueue.queue[mcan->rxQueue.front].header,
			&mcan->rxQueue.queue[mcan->rxQueue.front].data[0]) == HAL_OK)
	{
		mcan->rxQueue.front++;
		if(mcan->rxQueue.front >= MAL_CAN_QUEUE_SIZE)
			mcan->rxQueue.front = 0;
	}
	MAL_CAN_LED_On(&mcan->rxLed);
}
#else
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	MAL_CAN_HandleTypeDef *mcan = MAL_CAN_RegToMhandle((uint32_t)hcan->Instance);

	if(mcan == 0) return;

	if(HAL_CAN_GetRxMessage(mcan->hcan, CAN_RX_FIFO0, &mcan->rxQueue.queue[mcan->rxQueue.front].header,
			&mcan->rxQueue.queue[mcan->rxQueue.front].data[0]) == HAL_OK)
	{
		mcan->rxQueue.front++;
		if(mcan->rxQueue.front >= MAL_CAN_QUEUE_SIZE)
			mcan->rxQueue.front = 0;
	}
	MAL_CAN_LED_On(&mcan->rxLed);
}
#endif

static inline void MAL_CAN_TX_Queue(CAN_HandleTypeDef *hcan)
{
#ifdef CAN1
	if(hcan->Instance == CAN1)
#else
		if(hcan->Instance == CAN)
#endif
		{
			MAL_CAN_TxQueueTransmit(mcanManager.addrRegist.list[0].pmcan);
		}
		else{
			MAL_CAN_TxQueueTransmit(mcanManager.addrRegist.list[1].pmcan);
		}

}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{
	MAL_CAN_TX_Queue(hcan);
}
void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan)
{
	MAL_CAN_TX_Queue(hcan);
}
void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan)
{
	MAL_CAN_TX_Queue(hcan);
}

#endif
