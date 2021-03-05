/*
 * non_stop_delay_main.c
 *
 *  Created on: 2021. 1. 27.
 *      Author: shin
 */



#include "main.h"


/**
  * @간략      매개변수 time과 systimer 차이 계산
  * @매개변수 time
  * @반환      tick차이
  */
uint32_t MAL_SysTimer_Elapsed ( uint32_t time )
{
    if (HAL_GetTick() >= time) return (HAL_GetTick() - time               );
    else                             return ((0xffffffff - time)+ HAL_GetTick()+1);
}

/**
  * @간략      매개변수 time1,2 의 차이 계산
  * @매개변수 time1
  * @매개변수 time2
  * @반환      time 차이
  */
uint32_t MAL_SysTimer_GetElapsed (uint32_t time1, uint32_t time2)
{
    if (time1 >= time2) return (time1 - time2);
    else                return ((0xffffffff-time2) + time1+1);
}

/**
  * @간략      현재 tick 반환
  * @반환      tick
  */
uint32_t MAL_SysTimer_GetTickCount(void)
{
    return HAL_GetTick();
}


/**
  * @간략      무한루프 루틴에서 코어가 대기하지않는 딜레이.
  * @매개변수 *saveMem	타임슬롯이 저장될 메모리 주소
  * @매개변수 Delay	딜레이 시간	. 단위 ms
  * @반환      0		Delay 시간이 지나기 전.
  * @반환      1		Delay 시간이 초과됨.
  * @e.g
  * 		uint32_t t_delay;//32bit 크기의 전역 또는 static
  *
  * 		if(MAL_NonStopDelay(&t_delay, 500)) //t_delay & 으로 주소값 전달.
  * 		{
  * 			//루틴
  * 		}
  */
uint8_t MAL_NonStopDelay(uint32_t *saveMem, uint32_t Delay)
{
	if(MAL_SysTimer_Elapsed(*saveMem) > Delay)
	{
		*saveMem = HAL_GetTick();
		return 1;
	}
	else
	{
		return 0;
	}
}



