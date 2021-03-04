/*
 * X_Touch_Extender_ADC.h
 *
 *  Created on: 2021. 3. 4.
 *      Author: shin
 */

#ifndef X_TOUCH_EXTENDER_MOTORADC_INC_X_TOUCH_EXTENDER_ADC_H_
#define X_TOUCH_EXTENDER_MOTORADC_INC_X_TOUCH_EXTENDER_ADC_H_


#pragma pack(1)
typedef struct{
	uint8_t cmd;
	uint8_t slideNo;
	uint16_t data;
	uint8_t end;
	uint8_t checkSum;

}X_Touch_Rx_ADC_PacketTypedef;

typedef struct{
	uint8_t cmd;
	uint8_t slideNo;
	uint8_t data;
	uint8_t end;
	uint8_t checkSum;

}X_Touch_Rx_Touch_PacketTypedef;

#pragma pack()


#define SLIDER_CMD_ADC		0x66
#define SLIDER_CMD_TOUCH	0x62


void MAL_X_TouchExtender_ADC_Process();

#endif /* X_TOUCH_EXTENDER_MOTORADC_INC_X_TOUCH_EXTENDER_ADC_H_ */
