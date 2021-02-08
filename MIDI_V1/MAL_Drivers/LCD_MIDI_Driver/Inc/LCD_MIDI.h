/*
 * LCD_MIDI.h
 *
 *  Created on: Feb 5, 2021
 *      Author: shin
 */

#ifndef LCD_MIDI_DRIVER_INC_LCD_MIDI_H_
#define LCD_MIDI_DRIVER_INC_LCD_MIDI_H_



#define LCD_BUFF_SIZE	150


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
	uint8_t send_size;	//보낼 데이터 길이
	uint8_t send_cnt;	//전송완료된 데이터 길이

	uint8_t selNum;
	uint8_t cmd_en;

	uint8_t data[LCD_BUFF_SIZE];

/*	union{
		struct{
			uint8_t selNum : 3;
			uint8_t sel_en : 1;
			uint8_t cmd : 1;
			uint8_t res : 3;
		};
		uint8_t ctr;
	};*/


}LCD_Buff_TypeDef;

typedef struct{
	LCD_TIM_StatusTypeDef status;
	uint8_t seq_num;
}LCD_Control_TypeDef;



typedef struct{
	TIM_HandleTypeDef 	*htim;
	LCD_GPIO_TypeDef	pinout;
	LCD_Buff_TypeDef 	buff;

	LCD_Control_TypeDef ctr;

}LCD_Handle_TypeDef;



void MAL_LCD_Init(void);
void MAL_LCD_MIDI_TIM_Manager(void);

void MAL_LCD_MIDI_SendTrigger(void);
uint8_t MAL_LCD_MIDI_AddQueue(uint8_t selNum, uint8_t cmd_en, uint8_t *data, uint8_t size);

void MAL_LCD_DATA_TEST(uint8_t value);
void MAL_LCD_SEL_TEST(uint8_t value);

uint8_t MAL_LCD_SendDataSequnce(uint8_t data);



#endif /* LCD_MIDI_DRIVER_INC_LCD_MIDI_H_ */
