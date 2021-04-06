/*
 * panel_slide.h
 *
 *  Created on: 2021. 4. 2.
 *      Author: shin
 */

#ifndef PANEL_MANAGER_INC_PANEL_SLIDE_H_
#define PANEL_MANAGER_INC_PANEL_SLIDE_H_



typedef struct{
		uint32_t t_motorPosi[8];
		uint8_t f_motorPosi[8];
		uint16_t motorPosi[8];

		uint16_t oldAdc[8];

		uint32_t t_txTime[8];
}Slide_TypeDef;

void slide_tx_manager(void);
uint8_t slide_id_check(uint8_t motor_id);

#endif /* PANEL_MANAGER_INC_PANEL_SLIDE_H_ */
