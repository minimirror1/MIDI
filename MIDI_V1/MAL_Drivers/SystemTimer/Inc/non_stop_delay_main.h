/*
 * non_stop_delay_main.h
 *
 *  Created on: 2021. 1. 27.
 *      Author: shin
 */

#ifndef TICK_NON_STOP_DELAY_INC_NON_STOP_DELAY_MAIN_H_
#define TICK_NON_STOP_DELAY_INC_NON_STOP_DELAY_MAIN_H_



uint32_t MAL_SysTimer_Elapsed ( uint32_t time );
uint32_t MAL_SysTimer_GetElapsed (uint32_t time1, uint32_t time2);
uint32_t MAL_SysTimer_GetTickCount(void);
uint8_t MAL_NonStopDelay(uint32_t *saveMem, uint32_t Delay);

#endif /* TICK_NON_STOP_DELAY_INC_NON_STOP_DELAY_MAIN_H_ */
