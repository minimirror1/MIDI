/*
 * HC165_MIDI_wheel.h
 *
 *  Created on: 2021. 3. 5.
 *      Author: shin
 */

#ifndef HC165_MIDI_DRIVER_INC_HC165_MIDI_WHEEL_H_
#define HC165_MIDI_DRIVER_INC_HC165_MIDI_WHEEL_H_

typedef enum{

	ROT_CLEAR = 0,
	ROT_CW = 1,
	ROT_CCW = 2

}wheel_rot_TypeDef;

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

	uint8_t f_rot; //0: clear, 1:cw, 2:ccw;
}HC165_wheel_status_TypeDef;

typedef struct{
	HC165_wheel_Mapping_TypeDef map;

	HC165_wheel_trigger_TypeDef trigger;

	HC165_wheel_status_TypeDef status;

}HC165_wheel_TypeDef;


void HC165_MIDI_wheel_Mapping(void);
void HC165_MIDI_wheel_EventProcses(void);

#endif /* HC165_MIDI_DRIVER_INC_HC165_MIDI_WHEEL_H_ */
