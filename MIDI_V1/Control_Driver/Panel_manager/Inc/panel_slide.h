/*
 * panel_slide.h
 *
 *  Created on: 2021. 4. 2.
 *      Author: shin
 */

#ifndef PANEL_MANAGER_INC_PANEL_SLIDE_H_
#define PANEL_MANAGER_INC_PANEL_SLIDE_H_



typedef struct{
		uint8_t f_slotEnable[8];

		uint32_t t_motorPosi[8];
		uint8_t f_motorPosi[8];
		uint16_t motorPosi[8];

		uint32_t oldAdc[8];

		uint32_t oldAdc_v6[8];

		//0.0.6v 활성 후 최초값이 모터위치 범위 내에 있을때 활성됨.
		uint8_t f_enablePosi[8];
		int32_t enablePosi[8];

		uint32_t t_txTime[8];
}Slide_TypeDef;

void slide_tx_manager(void);
uint8_t slide_id_check(uint8_t motor_id);

void slide_slot_clear(void);
void set_slide_slot_flag(uint8_t slotNum, uint8_t status);
uint8_t get_slide_slot_flag(uint8_t slotNum);

#endif /* PANEL_MANAGER_INC_PANEL_SLIDE_H_ */
