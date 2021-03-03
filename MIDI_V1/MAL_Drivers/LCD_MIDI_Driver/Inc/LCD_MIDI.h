/*
 * LCD_MIDI.h
 *
 *  Created on: Feb 5, 2021
 *      Author: shin
 */

#ifndef LCD_MIDI_DRIVER_INC_LCD_MIDI_H_
#define LCD_MIDI_DRIVER_INC_LCD_MIDI_H_


#include "MIDI_LCD_textData2.h"


#define LCD_BUFF_SIZE	128
#define LCD_PAGE_SIZE	8

#define LCD_CMD_SIZE	15

#define LCD_IO_CMD			1
#define LCD_IO_DATA		0


//lcd commnad==========================================
#define LCD_CMD_RESET				0xE2
#define LCD_CMD_POWER_CTR			0x2F	//VB,VR,VF ON
#define LCD_CMD_REGULATION_RATIO	0x24	//4.0
#define LCD_CMD_BIAS_SEL			0xA2	//1/9
#define LCD_CMD_X					0xFA
#define LCD_CMD_SET_PAGE_ADDR		0xB0	//PAGE 0
#define LCD_CMD_SEG_DIR				0xA0	//Normal direction
#define LCD_CMD_ALL_PIXEL_ON		0xA4	//Normal display
#define LCD_CMD_INV_DISPLAY			0xA6	//Normal display
#define LCD_CMD_COM_DIR				0xC8	//reverse direction
#define LCD_CMD_SET_START_LINE		0x40	//strat line 0
#define LCD_CMD_DISPLAY_ON			0xAF	//display ON

#define LCD_CMD_DISPLAY_OFF			0xAE	//display OFF

#define LCD_CMD_SET_EV				0x81	//SET EV
#define LCD_CMD_SET_EV_VAL_MASK		0x3F	//SET EV VAL MASK   0~63

#define LCD_CMD_NOP					0xE3	//NOP

#define LCD_CMD_SET_PAGE_ADDR		0xB0	//PAGE ADDR
#define LCD_CMD_SET_PAGE_ADDR_MASK	0x0F	//PAGE ADDR MASK 0~8

#define LCD_CMD_SET_COL_0_LSB		0x00	//SET Column 0
#define LCD_CMD_SET_COL_0_MSB		0x10	//SET Column 0


//======================================================

typedef enum{
	LCD_MIDI_STOP = 0,
	LCD_MIDI_RUN
}LCD_TIM_StatusTypeDef;



typedef struct{
	GPIO_TypeDef 	*GPIO;
	uint16_t		Pin;
}LCD_Port_TypeDef;

typedef struct{
	GPIO_TypeDef 	*GPIO;
	uint16_t		mask; 	//Data = 0x00FF;  Sel = 0x0007;
	uint8_t			shift;
}LCD_Parallel_TypeDef;

typedef struct{
	LCD_Parallel_TypeDef ParaData; 	//D0 ~ D7 병렬 데이터
	LCD_Port_TypeDef	LCD_SEL_EN;
	LCD_Port_TypeDef	LCD_CMD;
	LCD_Port_TypeDef	LCD_CLK;
	LCD_Parallel_TypeDef ParaSel;	//A0 ~ A2 병렬 데이터
}LCD_GPIO_TypeDef;

typedef struct{

	uint8_t ev_level;

	uint8_t cmd_en;
	uint8_t send_size;	//보낼 데이터 길이
	uint8_t send_cnt;	//전송완료된 데이터 길이

	uint8_t cmd_data[LCD_CMD_SIZE];

	uint8_t send_page;
	uint8_t send_page_num;
	uint8_t frame[LCD_PAGE_SIZE][LCD_BUFF_SIZE];

}LCD_Num_TypeDef;

typedef struct{
	LCD_TIM_StatusTypeDef status;
	uint32_t seq_num;
}LCD_Control_TypeDef;



typedef struct{
	TIM_HandleTypeDef 	*htim;

	uint8_t f_init;
	uint8_t initLcdNum;

	uint8_t LcdScanNum;

	LCD_GPIO_TypeDef	pinout;
	LCD_Num_TypeDef 	lcd[8];

	LCD_Control_TypeDef ctr;

}LCD_Handle_TypeDef;


void LCD_control2(uint8_t selNum, LCDtextData_typedef *LCDtext);

void MAL_LCD_Init(void);
void MAL_LCD_MIDI_TIM_Manager(void);

void MAL_LCD_MIDI_SendTrigger(void);
uint8_t MAL_LCD_MIDI_AddQueue(uint8_t selNum, uint8_t cmd_en, uint8_t *data, uint8_t size);

void MAL_LCD_DATA_TEST(uint8_t value);
void MAL_LCD_SEL_TEST(uint8_t value);

uint8_t MAL_LCD_SendDataSequnce(uint8_t data);



#endif /* LCD_MIDI_DRIVER_INC_LCD_MIDI_H_ */
