/*
 * X_Touch_Extender_MotorAdc_packet.c
 *
 *  Created on: Feb 3, 2021
 *      Author: shin
 */


#include "main.h"
#include "uart.h"
#include "X_Touch_Extender_MotorAdc_packet.h"

extern MAL_UART_HandleTypeDef muart1;

X_Touch_Extender_Packet_HandleTypeDef extenderPacket = {0,};


void MAL_X_TouchExtender_Packet_Init(void)
{
	extenderPacket.muart = &muart1;

}

// CMD
const uint8_t MCU_END           = 0xFE;
const uint8_t CHECK_SUM_LEF     = 0x80;
// LEN
const uint8_t LEN_MOTOR_CONTROL = 0x04;
const uint8_t LEN_ADC           = 0x03;
const uint8_t LEN_TOUCH         = 0x03;

#define   MCU_CMD_READY  0x00
#define MCU_CMD_INIT   0x42
#define MCU_CMD_ADC    0x66
#define MCU_CMD_TOUCH  0x62
#define MCU_CMD_MOTOR  0x45

void Slide_control(uint8_t SlideNo, uint16_t vel)
{
	uint8_t send_buff[10] = {0,};
	uint8_t send_cnt = 0;

	  vel = vel >> 4;

  uint16_t sum      = LEN_MOTOR_CONTROL + MCU_CMD_MOTOR + SlideNo + (vel & 0xFF) + ((vel >> 8) & 0xFF);
  uint8_t sumNo     = (uint8_t)(sum/CHECK_SUM_LEF) + 1;
  uint8_t check_sum = CHECK_SUM_LEF*sumNo - sum;

  if (check_sum >= 0x80)   check_sum = 0x00;



  send_buff[send_cnt++] = MCU_END;                  // cmd
  send_buff[send_cnt++] = CHECK_SUM_LEF;                  // cmd
  send_buff[send_cnt++] = MCU_CMD_MOTOR;                  // cmd
  send_buff[send_cnt++] = SlideNo;                        // slide No
  send_buff[send_cnt++] = vel & 0xFF;                     // data Low
  send_buff[send_cnt++] = (vel >> 8) & 0xFF;              // data High
  send_buff[send_cnt++] = MCU_END;                        // end : 0xFE
  send_buff[send_cnt++] = check_sum;                      // chek sum


  MAL_UART_SendDataStream(extenderPacket.muart, send_buff, 8);
}

uint16_t test_cnt(void)
{
	static uint16_t t_cnt = 0;
	static uint8_t toggle = 0;

	if(toggle == 0)
	{
		t_cnt +=10;
		if(t_cnt > 4000)
		{
			toggle = 1;
		}
	}
	else if(toggle == 1)
	{
		t_cnt -=10;
		if(t_cnt < 100)
		{
			toggle = 0;
		}
	}

	return t_cnt;

}

void MAL_X_touch_test(void)
{
	  uint8_t CMD1[6] = {0xFE, 0x80, 0x42, 0x01, 0xFE, 0x3B};
	  uint8_t CMD2[6] = {0xFE, 0x80, 0x42, 0x00, 0xFE, 0x3C};
	  uint8_t CMD3[6] = {0xFE, 0x80, 0x42, 0x02, 0xFE, 0x3A};

	  HAL_Delay(1500);
	  MAL_UART_SendDataStream(extenderPacket.muart, CMD1, 6);
	  HAL_Delay(10);
	  MAL_UART_SendDataStream(extenderPacket.muart, CMD1, 6);
	  HAL_Delay(10);
	  MAL_UART_SendDataStream(extenderPacket.muart, CMD2, 6);
	  HAL_Delay(160);
	  MAL_UART_SendDataStream(extenderPacket.muart, CMD3, 6);
	  MAL_UART_SendDataStream(extenderPacket.muart, CMD3, 6);
	  HAL_Delay(240);

	  Slide_control(0,0);
	  Slide_control(1,0);
	  Slide_control(2,0);
	  Slide_control(3,0);
	  Slide_control(4,0);
	  Slide_control(5,0);
	  Slide_control(6,0);
	  Slide_control(7,0);


/*
	  while(1)
	  {
		  Slide_control(0,test_cnt());
		  Slide_control(1,test_cnt());
		  Slide_control(2,test_cnt());
		  Slide_control(3,test_cnt());
		  Slide_control(4,test_cnt());
		  Slide_control(5,test_cnt());
		  Slide_control(6,test_cnt());
		  Slide_control(7,test_cnt());

		  HAL_Delay(30);
	  }*/

}
