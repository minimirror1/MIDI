/*
 * board_info.h
 *
 *  Created on: 2021. 3. 11.
 *      Author: shin
 */

#ifndef INC_BOARD_INFO_H_
#define INC_BOARD_INFO_H_





typedef struct{
	uint8_t my_can_id;

}Communication_Info_TypeDef;


typedef struct{
	Communication_Info_TypeDef comm;

}Board_Info_TypeDef;


#endif /* INC_BOARD_INFO_H_ */
