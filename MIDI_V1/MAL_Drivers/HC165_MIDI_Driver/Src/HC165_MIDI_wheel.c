/*
 * HC165_MIDI_wheel.c
 *
 *  Created on: 2021. 3. 5.
 *      Author: shin
 */

#include "main.h"
#include "HC165_MIDI.h"
#include "HC165_MIDI_wheel.h"

#include "HC595_MIDI_Control.h"

extern uint8_t wheelIoData[HC165_WHEEL_IOCOUNT+1];
HC165_wheel_TypeDef wheel[8] = {0,};

//0			1			2			3			4			5			6			7
//cw :17 	cw :19		cw :21		cw :23		cw :9		cw :11		cw :13		cw :15
//ccw:16	ccw:18		ccw:20 		ccw:22		ccw:8		ccw:10		ccw:12		ccw:14
//btn:7		btn:6		btn:5 		btn:4		btn:3		btn:2		btn:1		btn:0



void HC165_MIDI_wheel_memSet(HC165_wheel_TypeDef *wheel, uint8_t *cw, uint8_t *ccw, uint8_t *btn)
{
	wheel->map.cw = cw;
	wheel->map.ccw = ccw;
	wheel->map.btn = btn;
}
void HC165_MIDI_wheel_Mapping(void)
{
	HC165_MIDI_wheel_memSet(&wheel[0],
				&wheelIoData[17],
				&wheelIoData[16],
				&wheelIoData[7]);

	HC165_MIDI_wheel_memSet(&wheel[1],
				&wheelIoData[19],
				&wheelIoData[18],
				&wheelIoData[6]);

	HC165_MIDI_wheel_memSet(&wheel[2],
				&wheelIoData[21],
				&wheelIoData[20],
				&wheelIoData[5]);

	HC165_MIDI_wheel_memSet(&wheel[3],
				&wheelIoData[23],
				&wheelIoData[22],
				&wheelIoData[4]);

	HC165_MIDI_wheel_memSet(&wheel[4],
				&wheelIoData[9],
				&wheelIoData[8],
				&wheelIoData[3]);

	HC165_MIDI_wheel_memSet(&wheel[5],
				&wheelIoData[11],
				&wheelIoData[10],
				&wheelIoData[2]);

	HC165_MIDI_wheel_memSet(&wheel[6],
				&wheelIoData[13],
				&wheelIoData[12],
				&wheelIoData[1]);

	HC165_MIDI_wheel_memSet(&wheel[7],
				&wheelIoData[15],
				&wheelIoData[14],
				&wheelIoData[0]);
}


void HC165_MIDI_wheel_Event_Btn(uint8_t selNum)
{
	if(*wheel[selNum].map.btn != wheel[selNum].trigger.btn_old)
	{
		wheel[selNum].trigger.btn_old = *wheel[selNum].map.btn;
		if(*wheel[selNum].map.btn == HC165_PUSH_ST)
		{
			wheel[selNum].status.btn = 1;
		}
		else
		{
			wheel[selNum].status.btn = 0;
		}
	}
}
void HC165_MIDI_wheel_Event_Wheel(uint8_t selNum)
{
	if(*wheel[selNum].map.cw != wheel[selNum].trigger.cw_old)
	{
		wheel[selNum].trigger.cw_old = *wheel[selNum].map.cw;
		if(*wheel[selNum].map.cw == HC165_PUSH_ST)
		{
			wheel[selNum].status.cw = 1;
		}
		else
		{
			wheel[selNum].status.cw = 0;
		}
	}

	if(*wheel[selNum].map.ccw != wheel[selNum].trigger.ccw_old)
	{
		wheel[selNum].trigger.ccw_old = *wheel[selNum].map.ccw;
		if(*wheel[selNum].map.ccw == HC165_PUSH_ST)
		{
			wheel[selNum].status.ccw = 1;
		}
		else
		{
			wheel[selNum].status.ccw = 0;
		}
	}

	wheel[selNum].status.ccw = *wheel[selNum].map.ccw;

	wheel[selNum].status.cw = *wheel[selNum].map.cw;

	if((wheel[selNum].status.cw == 0)&&(wheel[selNum].status.ccw == 0))
	{
		return;
	}

	if((wheel[selNum].status.cw == 1)&&(wheel[selNum].status.ccw == 1))
	{
		wheel[selNum].trigger.wheel_toggle = 1;
	}

	if(wheel[selNum].trigger.wheel_toggle == 1)
	{
		if(wheel[selNum].status.cw == 0)
		{
			if(wheel[selNum].status.ccw == 1)
			{
				wheel[selNum].status.wheelCnt++;
				if(wheel[selNum].status.wheelCnt >= 13)
				{
					wheel[selNum].status.wheelCnt = 13;
				}
				wheel[selNum].trigger.wheel_toggle = 0;
				MAL_LED_Wheel_Control(selNum, wheel[selNum].status.wheelCnt);
			}
		}
		else if(wheel[selNum].status.ccw == 0)
		{
			if(wheel[selNum].status.cw == 1)
			{

				wheel[selNum].status.wheelCnt--;
				if (wheel[selNum].status.wheelCnt <= 0) {
					wheel[selNum].status.wheelCnt = 0;
				}
				wheel[selNum].trigger.wheel_toggle = 0;
				MAL_LED_Wheel_Control(selNum, wheel[selNum].status.wheelCnt);
			}
		}
	}
}

void HC165_MIDI_wheel_EventProcses(void)
{
	for(int i=0; i < 8; i++)
	{
		HC165_MIDI_wheel_Event_Btn(i);
		HC165_MIDI_wheel_Event_Wheel(i);
	}
}
