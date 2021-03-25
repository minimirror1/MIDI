/*
 * HC165_MIDI_btn.c
 *
 *  Created on: 2021. 3. 5.
 *      Author: shin
 */

#include "main.h"
#include "HC165_MIDI.h"
#include "HC165_MIDI_btn.h"

extern uint8_t buttonIoData[HC165_BUTTON_IOCOUNT+1];
HC165_btn_TypeDef btn[8] = {0,};

//0			1		2		3		4		5		6		7
//re:31		27		23		19		15		11		7		3
//sl:30		26		22		18		14		10		6		2
//mu:29		25		21		17		13		9		5		1
//se:28		24		20		16		12		8		4		0

void HC165_MIDI_btn_memSet(HC165_btn_TypeDef *pBtn, uint8_t *re, uint8_t *sl, uint8_t *mu, uint8_t *se)
{
	pBtn->map[0].btn = re;
	pBtn->map[1].btn = sl;
	pBtn->map[2].btn = mu;
	pBtn->map[3].btn = se;
}
void HC165_MIDI_btn_Mapping(void)
{
	HC165_MIDI_btn_memSet(&btn[0],&buttonIoData[31],&buttonIoData[30],&buttonIoData[29],&buttonIoData[28]);
	HC165_MIDI_btn_memSet(&btn[1],&buttonIoData[27],&buttonIoData[26],&buttonIoData[25],&buttonIoData[24]);
	HC165_MIDI_btn_memSet(&btn[2],&buttonIoData[23],&buttonIoData[22],&buttonIoData[21],&buttonIoData[20]);
	HC165_MIDI_btn_memSet(&btn[3],&buttonIoData[19],&buttonIoData[18],&buttonIoData[17],&buttonIoData[16]);
	HC165_MIDI_btn_memSet(&btn[4],&buttonIoData[15],&buttonIoData[14],&buttonIoData[13],&buttonIoData[12]);
	HC165_MIDI_btn_memSet(&btn[5],&buttonIoData[11],&buttonIoData[10],&buttonIoData[9],&buttonIoData[8]);
	HC165_MIDI_btn_memSet(&btn[6],&buttonIoData[7],&buttonIoData[6],&buttonIoData[5],&buttonIoData[4]);
	HC165_MIDI_btn_memSet(&btn[7],&buttonIoData[3],&buttonIoData[2],&buttonIoData[1],&buttonIoData[0]);
}
void HC165_MIDI_btn_EventProcses()
{

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 4; j++){
			if (*btn[i].map[j].btn != btn[i].trigger[j].btn_old) {
				btn[i].trigger[j].btn_old = *btn[i].map[j].btn;
				if (*btn[i].map[j].btn == HC165_PUSH_ST) {
					btn[i].status[j].btn = 1;
				} else {
					btn[i].status[j].btn = 0;
				}
			}
		}
	}

}
