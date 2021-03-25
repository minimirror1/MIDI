/*
 * HC165_MIDI_btn.h
 *
 *  Created on: 2021. 3. 5.
 *      Author: shin
 */

#ifndef HC165_MIDI_DRIVER_INC_HC165_MIDI_BTN_H_
#define HC165_MIDI_DRIVER_INC_HC165_MIDI_BTN_H_




typedef struct{
	uint8_t *btn;

}HC165_btn_Mapping_TypeDef;

typedef struct{
	uint8_t btn_old;

	uint8_t btn_toggle;
}HC165_btn_trigger_TypeDef;

typedef struct{
	uint8_t btn;
}HC165_btn_status_TypeDef;

typedef struct{
	HC165_btn_Mapping_TypeDef map[4];

	HC165_btn_trigger_TypeDef trigger[4];

	HC165_btn_status_TypeDef status[4];

}HC165_btn_TypeDef;


void HC165_MIDI_btn_Mapping(void);

#endif /* HC165_MIDI_DRIVER_INC_HC165_MIDI_BTN_H_ */
