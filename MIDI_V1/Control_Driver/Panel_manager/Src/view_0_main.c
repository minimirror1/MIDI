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

#include "app_pid_init_cmd.h"
#include "app_pid_midi_cmd.h"
#include "prtc_data_pid_midi.h"


extern PanelManager_TypeDef panel;

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;

extern Comm_Page_TypeDef com_page;
extern Comm_Axle_TypeDef com_axle;

extern Panel_Page_TypeDef page;

extern HC165_btn_TypeDef btn[8];

extern uint8_t my_can_id;


uint8_t f_v0_first = 1;

uint8_t f_enableToggle[8] = {0,};

void View_0_enable(void)
{
	for(int i = 0; i < 8; i++)
	{
		if (com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].axle_num != 0)
		{
			if (btn[i].status[3].btn == 1)
			{
				if (f_enableToggle[i] == 0)
				{
					f_enableToggle[i] = 1;

					if (get_slide_slot_flag(i) == 1)
					{
						set_slide_slot_flag(i, 0);
						MAL_LED_Button_Control(i, 3, LED_OFF);
						Slide_control(i, 0);
						LCD_pixel_write_sizeA_p(i, ' ', 16);
						LCD_pixel_write_sizeA_p(i, 'O', 17);
						LCD_pixel_write_sizeA_p(i, 'F', 18);
						LCD_pixel_write_sizeA_p(i, 'F', 19);

					}
					else if (get_slide_slot_flag(i) == 0)
					{
/*						set_slide_slot_flag(i, 1);
						MAL_LED_Button_Control(i, 3, LED_ON);*/
						//상위에 모터위치를 요청하고  응답받으면 활성화 한다.
						app_tx_midi_sub_pid_adc_rqt(
								0,
								1,
								my_can_id,
								0,
								31,
								com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].axleNum].axle_num);
					}
				}
			}
			else
			{
				if (f_enableToggle[i] == 1)
				{
					f_enableToggle[i] = 0;
				}
			}
		}
	}
}
void View_0_enableRsp(uint8_t slot_id, uint16_t set_posi)
{
	if(slot_id > 8)
		return;

	set_slide_slot_flag(slot_id, 1);
	MAL_LED_Button_Control(slot_id, 3, LED_ON);

	extenderPacket.adc[slot_id] = set_posi;

	Slide_control(slot_id, set_posi);
	LCD_SetText_ADC_DEC(slot_id, set_posi);

}



void View_0_Main(void)//일반 조종화면
{

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

		slide_slot_clear();


	}

	View_0_enable();


	slide_tx_manager();



	panel_longKey();
	Page_Display();

}















