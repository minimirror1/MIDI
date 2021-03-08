/*
 * HC165_MIDI_wheel.h
 *
 *  Created on: 2021. 3. 5.
 *      Author: shin
 */

#ifndef HC165_MIDI_DRIVER_INC_HC165_MIDI_WHEEL_H_
#define HC165_MIDI_DRIVER_INC_HC165_MIDI_WHEEL_H_



typedef struct{
	uint8_t *cw;
	uint8_t *ccw;
	uint8_t *btn;

}HC165_wheel_Mapping_TypeDef;

typedef struct{
	uint8_t cw_old;
	uint8_t ccw_old;
	uint8_t btn_old;

	uint8_t wheel_toggle;
}HC165_wheel_trigger_TypeDef;

typedef struct{
	uint8_t cw;
	uint8_t ccw;
	uint8_t btn;

	int8_t wheelCnt;
}HC165_wheel_status_TypeDef;

typedef struct{
	HC165_wheel_Mapping_TypeDef map;

	HC165_wheel_trigger_TypeDef trigger;

	HC165_wheel_status_TypeDef status;

}HC165_wheel_TypeDef;


void HC165_MIDI_wheel_Mapping(void);
void HC165_MIDI_wheel_EventProcses(void);

#endif /* HC165_MIDI_DRIVER_INC_HC165_MIDI_WHEEL_H_ */
