/*
 * view_0_main.c
 *
 *  Created on: 2021. 3. 25.
 *      Author: shin
 */

#include "main.h"

#include "HC595_MIDI.h"
#include "HC595_MIDI_Control.h"

#include "HC165_MIDI.h"
#include "HC165_MIDI_wheel.h"
#include "HC165_MIDI_btn.h"

#include "X_Touch_Extender_ADC.h"
#include "X_Touch_Extender_MotorAdc_packet.h"
#include "LCD_MIDI.h"
#include "LCD_MIDI_Control.h"
#include "non_stop_delay_main.h"

#include "panel_manager.h"
#include "panel_view.h"
#include "panel_control.h"
#include "panel_page.h"
#include "panel_slide.h"

#include "long_key.h"

#include "communication_info.h"


extern PanelManager_TypeDef panel;

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;

extern Comm_Page_TypeDef com_page;
extern Comm_Axle_TypeDef com_axle;


uint8_t f_v0_first = 1;
void View_0_Main(void)//일반 조종화면
{
	static uint32_t t_adc;

	if(f_v0_first == 1)
	{
		f_v0_first = 0;
		LCD_SetText_ADC_DEC(0, extenderPacket.adc[0]);
		LCD_SetText_ADC_DEC(1, extenderPacket.adc[1]);
		LCD_SetText_ADC_DEC(2, extenderPacket.adc[2]);
		LCD_SetText_ADC_DEC(3, extenderPacket.adc[3]);
		LCD_SetText_ADC_DEC(4, extenderPacket.adc[4]);
		LCD_SetText_ADC_DEC(5, extenderPacket.adc[5]);
		LCD_SetText_ADC_DEC(6, extenderPacket.adc[6]);
		LCD_SetText_ADC_DEC(7, extenderPacket.adc[7]);
	}


/*
	if (MAL_NonStopDelay(&t_adc, 50) == 1)
	{
		LCD_SetText_ADC_DEC(0, extenderPacket.adc[0]);
		LCD_SetText_ADC_DEC(1, extenderPacket.adc[1]);
		LCD_SetText_ADC_DEC(2, extenderPacket.adc[2]);
		LCD_SetText_ADC_DEC(3, extenderPacket.adc[3]);
		LCD_SetText_ADC_DEC(4, extenderPacket.adc[4]);
		LCD_SetText_ADC_DEC(5, extenderPacket.adc[5]);
		LCD_SetText_ADC_DEC(6, extenderPacket.adc[6]);
		LCD_SetText_ADC_DEC(7, extenderPacket.adc[7]);
	}*/
	slide_tx_manager();



	panel_longKey();
	Page_Display();

}















