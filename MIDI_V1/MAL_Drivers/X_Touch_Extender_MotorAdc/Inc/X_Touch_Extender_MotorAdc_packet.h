/*
 * X_Touch_Extender_MotorAdc_packet.h
 *
 *  Created on: Feb 3, 2021
 *      Author: shin
 */

#ifndef X_TOUCH_EXTENDER_MOTORADC_INC_X_TOUCH_EXTENDER_MOTORADC_PACKET_H_
#define X_TOUCH_EXTENDER_MOTORADC_INC_X_TOUCH_EXTENDER_MOTORADC_PACKET_H_

#include "uart.h"


typedef struct{

	uint8_t seqNum;
	uint8_t rxLen;
	uint8_t rxbuff[30];
	uint8_t checkSum;

}X_Touch_Extender_RxData_TypeDef;

typedef struct{
	MAL_UART_HandleTypeDef *muart;


	X_Touch_Extender_RxData_TypeDef rxHandle;

	uint32_t adc[8];
	uint16_t touch[8];

}X_Touch_Extender_Packet_HandleTypeDef;


void MAL_X_touch_test(void);
void MAL_X_TouchExtender_Packet_Init(void);

void Slide_control(uint8_t SlideNo, uint16_t vel);

#endif /* X_TOUCH_EXTENDER_MOTORADC_INC_X_TOUCH_EXTENDER_MOTORADC_PACKET_H_ */
