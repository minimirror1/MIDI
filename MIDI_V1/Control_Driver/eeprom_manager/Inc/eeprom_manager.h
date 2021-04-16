/*
 * eeprom_manager.h
 *
 *  Created on: 2021. 4. 16.
 *      Author: shin
 */

#ifndef EEPROM_MANAGER_INC_EEPROM_MANAGER_H_
#define EEPROM_MANAGER_INC_EEPROM_MANAGER_H_


#define FACTORY_VAL		0xAAAA

typedef enum{
	FACTORY_SETTING_FLAG = 0,
	SETTING_CAN_ID = 1,
}eeprom_address_TypeDef;


void eeprom_init(void);
#endif /* EEPROM_MANAGER_INC_EEPROM_MANAGER_H_ */
