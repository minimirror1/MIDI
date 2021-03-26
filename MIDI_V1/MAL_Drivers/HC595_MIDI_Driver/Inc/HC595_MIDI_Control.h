/*
 * HC595_MIDI_Control.h
 *
 *  Created on: Feb 2, 2021
 *      Author: shin
 */

#ifndef HC595_MIDI_DRIVER_INC_HC595_MIDI_CONTROL_H_
#define HC595_MIDI_DRIVER_INC_HC595_MIDI_CONTROL_H_


#define	MIDI_LED_GROUP_COUNT 	8


typedef enum{
	LED_BLACK = 0,	//R:X,G:X,B:X
	LED_RED,		//R:O,G:X,B:X
	LED_GREEN,		//R:X,G:O,B:X
	LED_BLUE,		//R:X,G:X,B:O
	LED_MAGENTA,	//R:O,G:X,B:O
	LED_YELLOW,		//R:O,G:O,B:X
	LED_CYAN,		//R:X,G:O,B:O
	LED_WHITE		//R:O,G:O,B:O
}HC595_LED_BacklightTypeDef;

typedef enum{
	LED_REC = 0,
	LED_SOLO,
	LED_MUTE,
	LED_SELECT

}HC595_LED_ButtonTypeDef;

typedef enum{
	LED_ON = 0,
	LED_OFF
}HC595_LED_StatusTypeDef;

typedef struct{
	uint8_t value;	//0~13
}HC595_LED_WheelGauge_TypeDef;

typedef struct{
	HC595_LED_BacklightTypeDef color;
	HC595_LED_StatusTypeDef r;
	HC595_LED_StatusTypeDef g;
	HC595_LED_StatusTypeDef b;
}HC595_LED_Backlight_TypeDef;

typedef struct{
	uint8_t value; 	//0~8
}HC595_LED_BarGauge_TypeDef;

typedef struct{
	HC595_LED_StatusTypeDef rec;
	HC595_LED_StatusTypeDef solo;
	HC595_LED_StatusTypeDef mute;
	HC595_LED_StatusTypeDef select;
}HC595_LED_Button_TypeDef;



typedef struct{
	HC595_LED_WheelGauge_TypeDef 	wheelGauge;
	HC595_LED_Backlight_TypeDef		backLight;
	HC595_LED_BarGauge_TypeDef		barGauge;
	HC595_LED_Button_TypeDef		button;
}HC595_LED_GroupTypeDef;

void MAL_LED_Refresh(void);
void MAL_LED_Control_Init(void);

void MAL_LED_Wheel_Control(uint8_t ch, uint8_t value);
void MAL_LED_BackLight_Control(uint8_t ch, HC595_LED_BacklightTypeDef color );
void MAL_LED_BarGauge_Control(uint8_t ch, uint8_t value);
void MAL_LED_Button_Control(uint8_t ch, HC595_LED_ButtonTypeDef btn, HC595_LED_StatusTypeDef status);


#endif /* HC595_MIDI_DRIVER_INC_HC595_MIDI_CONTROL_H_ */
