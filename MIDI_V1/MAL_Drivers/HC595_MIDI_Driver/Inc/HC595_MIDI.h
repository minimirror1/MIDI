/*
 * HC595_MIDI.h
 *
 *  Created on: Feb 2, 2021
 *      Author: shin
 */

#ifndef HC595_MIDI_DRIVER_INC_HC595_MIDI_H_
#define HC595_MIDI_DRIVER_INC_HC595_MIDI_H_



#define HC595_WHEEL_IO_COUNT 	104
#define HC595_BAR_IO_COUNT 		64
#define HC595_LCD_BTN_IO_COUNT 	56


typedef enum{
	HC595_MIDI_STOP = 0,
	HC595_MIDI_RUN
}HC595_MIDI_StatusTypeDef;

typedef struct{
	TIM_HandleTypeDef *htim;

	HC595_MIDI_StatusTypeDef send_status;

	uint32_t initIo_count;			//hc595 io 개수

	uint32_t io_count;			//송신 카운트

	uint8_t send_seq;

	uint8_t clk_toggle;

	GPIO_TypeDef *LATCH_GPIO;
	uint16_t LATCH_GPIO_Pin;

	GPIO_TypeDef *CLK_GPIO;
	uint16_t CLK_GPIO_Pin;

	GPIO_TypeDef *DATA_GPIO;
	uint16_t DATA_GPIO_Pin;

	uint8_t ioData[HC595_WHEEL_IO_COUNT];


}HC595_Wheel_ConfigTypeDef;

typedef struct{
	TIM_HandleTypeDef *htim;

	HC595_MIDI_StatusTypeDef send_status;

	uint32_t bar_initIo_count;			//hc595 io 개수
	uint32_t lcdbtn_initIo_count;			//hc595 io 개수

	uint32_t io_count;			//송신 카운트


	uint8_t send_seq;

	uint8_t clk_toggle;

	GPIO_TypeDef *LATCH_GPIO;
	uint16_t LATCH_GPIO_Pin;

	GPIO_TypeDef *CLK_GPIO;
	uint16_t CLK_GPIO_Pin;

	GPIO_TypeDef *BAR_DATA_GPIO;
	uint16_t BAR_DATA_GPIO_Pin;

	GPIO_TypeDef *LCD_BTN_DATA_GPIO;
	uint16_t LCD_BTN_DATA_GPIO_Pin;


	uint8_t ioData_bar[HC595_BAR_IO_COUNT];

	uint8_t ioData_lcdBtn[HC595_BAR_IO_COUNT];//CLK LATCH 를 공통사용하기 때문에 버퍼크기를 같게

}HC595_BAR_LCD_BTN_ConfigTypeDef;


void MAL_HC595_MIDI_SendTrigger(void);
void MAL_HC595_MIDI_Wheel_WritePin(uint32_t pinNum, GPIO_PinState PinStatus);
void MAL_HC595_MIDI_Bar_WritePin(uint32_t pinNum, GPIO_PinState PinStatus);
void MAL_HC595_MIDI_LCD_BTN_WritePin(uint32_t pinNum, GPIO_PinState PinStatus);
void MAL_HC595_MIDI_All_Off(void);


//=====드라이버 함수.
void MAL_HC595_MIDI_Init(void);
void MAL_HC595_MIDI_TIM_Manager(void);



#endif /* HC595_MIDI_DRIVER_INC_HC595_MIDI_H_ */
