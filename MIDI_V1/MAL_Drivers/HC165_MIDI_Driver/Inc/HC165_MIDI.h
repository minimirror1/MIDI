/*
 * HC165_MIDI.h
 *
 *  Created on: Feb 2, 2021
 *      Author: shin
 */

#ifndef HC165_MIDI_DRIVER_INC_HC165_MIDI_H_
#define HC165_MIDI_DRIVER_INC_HC165_MIDI_H_


#define HC165_WHEEL_IOCOUNT		24
#define HC165_BUTTON_IOCOUNT	32

typedef enum{
	HC165_MIDI_STOP = 0,
	HC165_MIDI_RUN
}HC165_MIDI_StatusTypeDef;

/*

typedef struct{
	TIM_HandleTypeDef *htim;

	HC165_MIDI_StatusTypeDef read_status;

	uint32_t initIo_count;			//hc165 io 개수

	uint32_t io_count;			//송신 카운트

	uint8_t send_seq;

	uint8_t clk_toggle;

	//output
	GPIO_TypeDef *PL_GPIO;
	uint16_t PL_GPIO_Pin;
	//output
	GPIO_TypeDef *CLK_GPIO;
	uint16_t CLK_GPIO_Pin;
	//input
	GPIO_TypeDef *DATA_GPIO;
	uint16_t DATA_GPIO_Pin;

	uint8_t *ioData;

	//uint8_t ioData[HC165_WHEEL_IOCOUNT];
}HC165_WHEEL_ConfigTypeDef;

typedef struct{
	TIM_HandleTypeDef *htim;

	HC165_MIDI_StatusTypeDef read_status;

	uint32_t initIo_count;			//hc165 io 개수

	uint32_t io_count;			//송신 카운트

	uint8_t send_seq;

	uint8_t clk_toggle;

	//output
	GPIO_TypeDef *PL_GPIO;
	uint16_t PL_GPIO_Pin;
	//output
	GPIO_TypeDef *CLK_GPIO;
	uint16_t CLK_GPIO_Pin;
	//input
	GPIO_TypeDef *DATA_GPIO;
	uint16_t DATA_GPIO_Pin;

	uint8_t *ioData;
	//uint8_t ioData[HC165_BUTTON_IOCOUNT];
}HC165_BUTTON_ConfigTypeDef;
*/


typedef struct{
	TIM_HandleTypeDef *htim;

	HC165_MIDI_StatusTypeDef read_status;

	uint32_t initIo_count;			//hc165 io 개수

	uint32_t io_count;			//송신 카운트

	uint8_t send_seq;

	uint8_t clk_toggle;

	//output
	GPIO_TypeDef *PL_GPIO;
	uint16_t PL_GPIO_Pin;
	//output
	GPIO_TypeDef *CLK_GPIO;
	uint16_t CLK_GPIO_Pin;
	//input
	GPIO_TypeDef *DATA_GPIO;
	uint16_t DATA_GPIO_Pin;

	uint8_t *ioData;
}HC165_ConfigTypeDef;

void MAL_HC165_MIDI_ReadTrigger(void);
void MAL_HC165_MIDI_Init(void);
void MAL_HC165_MIDI_TIM_Manager(void);

#endif /* HC165_MIDI_DRIVER_INC_HC165_MIDI_H_ */
