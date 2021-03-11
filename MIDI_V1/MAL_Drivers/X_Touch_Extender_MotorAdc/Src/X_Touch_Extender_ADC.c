/*
 * X_Touch_Extender_ADC.c
 *
 *  Created on: 2021. 3. 4.
 *      Author: shin
 */




#include "main.h"
#include "uart.h"
#include "X_Touch_Extender_ADC.h"
#include "X_Touch_Extender_MotorAdc_packet.h"

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;



void cmd_check(uint8_t data)
{
	if((data == SLIDER_CMD_ADC)||(data == SLIDER_CMD_TOUCH))
	{
		extenderPacket.rxHandle.seqNum = 1;

		extenderPacket.rxHandle.rxbuff[extenderPacket.rxHandle.rxLen] = data;
		extenderPacket.rxHandle.rxLen++;
		return;
	}

	extenderPacket.rxHandle.seqNum = 0;
	extenderPacket.rxHandle.rxLen = 0;
}

void rx_body(uint8_t data)
{
	extenderPacket.rxHandle.rxbuff[extenderPacket.rxHandle.rxLen] = data;
	extenderPacket.rxHandle.rxLen++;

	if (extenderPacket.rxHandle.rxbuff[0] == SLIDER_CMD_ADC) {
		if (extenderPacket.rxHandle.rxLen > 3) {
			extenderPacket.rxHandle.seqNum = 2;
		}
	} else if (extenderPacket.rxHandle.rxbuff[0] == SLIDER_CMD_TOUCH) {
		if (extenderPacket.rxHandle.rxLen > 2) {
			extenderPacket.rxHandle.seqNum = 2;
		}
	}
}

void end_check(uint8_t data)
{
	if(data == 0xFE)
	{
		extenderPacket.rxHandle.rxbuff[extenderPacket.rxHandle.rxLen] = data;
		extenderPacket.rxHandle.rxLen++;
		extenderPacket.rxHandle.seqNum = 3;
	}
	else
	{
		extenderPacket.rxHandle.seqNum = 0;
		extenderPacket.rxHandle.rxLen = 0;
	}
}


void packet_Parser_ADC(uint8_t *data)
{
	X_Touch_Rx_ADC_PacketTypedef *packet = (X_Touch_Rx_ADC_PacketTypedef *)data;

	uint16_t crcTemp = 0;


	crcTemp = data[0]+data[1]+data[2]+data[3]+data[5]+4;

	if((crcTemp % 0x80) == 0)
	{
		if(packet->slideNo < 8)
		{
			extenderPacket.adc[packet->slideNo] = packet->data;
		}
	}
}

void packet_Parser_TOUCH(uint8_t *data)
{
	X_Touch_Rx_Touch_PacketTypedef *packet = (X_Touch_Rx_Touch_PacketTypedef *)data;

	uint16_t crcTemp = 0;


	crcTemp = data[0]+data[1]+data[2]+data[4]+3;


	if((crcTemp % 0x80) == 0)
	{
		if(packet->slideNo < 8)
		{
			extenderPacket.touch[packet->slideNo] = packet->data;
		}
	}
}
void crc_check(uint8_t data)
{
	extenderPacket.rxHandle.rxbuff[extenderPacket.rxHandle.rxLen] = data;

	switch(extenderPacket.rxHandle.rxbuff[0])
	{
	case SLIDER_CMD_ADC :
		packet_Parser_ADC(&extenderPacket.rxHandle.rxbuff[0]);
		break;
	case SLIDER_CMD_TOUCH :
		packet_Parser_TOUCH(&extenderPacket.rxHandle.rxbuff[0]);
		break;
	}


}


void MAL_X_TouchExtender_ADC_Parser(void)
{
	uint8_t data = 0;
	while(MAL_UART_GetQueueData_Byte(extenderPacket.muart, &data) == MAL_UART_CONTAIN)
	{
		switch(extenderPacket.rxHandle.seqNum)
		{
		case 0:
			cmd_check(data);
			break;
		case 1:
			rx_body(data);
			break;
		case 2:
			end_check(data);
			break;
		case 3:
			crc_check(data);

			extenderPacket.rxHandle.seqNum = 0;
			extenderPacket.rxHandle.rxLen = 0;
			break;


		}
	}
}



void MAL_X_TouchExtender_ADC_Process()
{
	MAL_X_TouchExtender_ADC_Parser();
}
