/*
 * HC595.h
 *
 *  Created on: Feb 1, 2021
 *      Author: shin
 */

#ifndef HC595_DRIVER_INC_HC595_H_
#define HC595_DRIVER_INC_HC595_H_



#define MAX_HC595_IO_CNT 	200
#define MAX_HANDLE_CNT 	3


typedef enum{
	HC595_STOP = 0,
	HC595_RUN
}HC595_StatusTypeDef;

typedef struct{
	TIM_HandleTypeDef *htim;	//10khz timer interrupt
	uint32_t io_count;			//hc595 io 개수

	GPIO_PinState gpio_default_out;	// high  low

	GPIO_TypeDef *LATCH_GPIO;
	uint16_t LATCH_GPIO_Pin;

	GPIO_TypeDef *CLK_GPIO;
	uint16_t CLK_GPIO_Pin;

	GPIO_TypeDef *DATA_GPIO;
	uint16_t DATA_GPIO_Pin;
}HC595_ConfigTypeDef;

typedef struct{
	HC595_StatusTypeDef send_status;
	uint32_t io_count;
	uint8_t send_seq;
	uint8_t clk_toggle;

	uint8_t io_data[MAX_HC595_IO_CNT];

}HC595_ControlTypeDef;
typedef struct{
	HC595_ConfigTypeDef config;
	HC595_ControlTypeDef control;
}HC595_HandleTypeDef;


typedef struct{
	HC595_HandleTypeDef *HC595[MAX_HANDLE_CNT];
	uint8_t handle_cnt;
}HC595_ManagerTypeDef;


void MAL_HC595_Init(HC595_HandleTypeDef *HC595,	HC595_ConfigTypeDef *sConfig);
void MAL_HC595_SendTrigger(HC595_HandleTypeDef *HC595);
void MAL_HC595_WritePin(HC595_HandleTypeDef *HC595, uint32_t pinNum, GPIO_PinState PinStatus);


#endif /* HC595_DRIVER_INC_HC595_H_ */
