/*
 * key_manager.c
 *
 *  Created on: 2021. 3. 23.
 *      Author: shin
 */


#include "main.h"
#include "key_manager.h"
#include "long_key.h"





void Key_Init(void)
{
	LongKey_Init();
}

void Key_Manager(void)
{
	LongKey();
}
