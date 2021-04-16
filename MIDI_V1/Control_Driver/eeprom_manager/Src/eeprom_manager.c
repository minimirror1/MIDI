/*
 * eeprom_manager.c
 *
 *  Created on: 2021. 4. 16.
 *      Author: shin
 */


#include "main.h"
#include "eeprom.h"
#include "eeprom_manager.h"

uint16_t VirtAddVarTab[NB_OF_VAR] ={0,};

extern uint8_t my_can_id;

void eeprom_write_16(eeprom_address_TypeDef virtAddr, uint16_t value)
{
	EE_WriteVariable(virtAddr, value);
}

void eeprom_read_16(eeprom_address_TypeDef virtAddr, uint16_t *value)
{
	EE_ReadVariable(virtAddr, value);
}

void eeprom_write_8(eeprom_address_TypeDef virtAddr, uint8_t value)
{
	uint16_t temp = value;
	EE_WriteVariable(virtAddr, temp);
}

void eeprom_read_8(eeprom_address_TypeDef virtAddr, uint8_t *value)
{
	uint16_t temp = 0;
	EE_ReadVariable(virtAddr, &temp);
	*value = temp;
}

void factory_setting(void)
{
	uint16_t f_factory = 0;

	eeprom_read_16(FACTORY_SETTING_FLAG, &f_factory);

	if(f_factory != FACTORY_VAL)
	{
		eeprom_write_16(FACTORY_SETTING_FLAG, FACTORY_VAL);

		my_can_id = 1;
		eeprom_write_8(SETTING_CAN_ID, my_can_id);


	}
}


void eeprom_init(void)
{
	HAL_FLASH_Unlock();

	if (EE_Init() != EE_OK)
	{
		Error_Handler();
	}

	for(int i = 0; i < NB_OF_VAR; i++)
	{
		VirtAddVarTab[i] = i;
	}


	factory_setting();

	eeprom_read_8(SETTING_CAN_ID, &my_can_id);



}
