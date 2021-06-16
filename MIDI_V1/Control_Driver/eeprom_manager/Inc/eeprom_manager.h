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
	VADDR_FACTORY_SETTING_FLAG = 0,
	VADDR_SETTING_CAN_ID = 1,
}eeprom_address_TypeDef;


void eeprom_init(void);

void eeprom_write_16(eeprom_address_TypeDef virtAddr, uint16_t value);
void eeprom_read_16(eeprom_address_TypeDef virtAddr, uint16_t *value);
void eeprom_write_8(eeprom_address_TypeDef virtAddr, uint8_t value);
void eeprom_read_8(eeprom_address_TypeDef virtAddr, uint8_t *value);

#endif /* EEPROM_MANAGER_INC_EEPROM_MANAGER_H_ */
