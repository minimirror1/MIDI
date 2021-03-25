/*
 * long_key.c
 *
 *  Created on: 2021. 3. 23.
 *      Author: shin
 */

#include "main.h"
#include "HC165_MIDI_wheel.h"
#include "non_stop_delay_main.h"


#include "key_manager.h"
#include "long_key.h"



extern HC165_wheel_TypeDef wheel[8];

LongKey_TypeDef LongKeyWheel[8] = {0,};


void LongKey_Init(void)
{
//key mapping
	for(int i = 0; i < 8; i++)
	{
		LongKeyWheel[i].pBtnSt = &wheel[i].status.btn;
	}

}

void LongKey_Detect(LongKey_TypeDef *longKey)
{
	if (longKey->fPress == 0) {
		if (*longKey->pBtnSt == 1) {
			longKey->fPress = 1;
			longKey->tLong = MAL_SysTimer_GetTickCount();
		}
	} else if (longKey->fPress == 1) {
		//눌림 유지시간은 fPress 에따라
		longKey->PressTime = MAL_SysTimer_Elapsed(longKey->tLong); //눌림 유지 시간

		if (longKey->PressTime >= KEY_LONG_TIME) {
			longKey->fLongKey = SET;
		}

		if (*longKey->pBtnSt == 0) {
			longKey->PressTime = 0;
			longKey->fPress = 0;
			longKey->fLongKey = RESET;
		}
	} else {
		longKey->fPress = 0;
	}
}

//wheel
void LongKey_Wheel(void)
{
	for(int i = 0; i < 8; i++)
	{
		LongKey_Detect(&LongKeyWheel[i]);
	}
}



void LongKey(void)
{
	LongKey_Wheel();
}
