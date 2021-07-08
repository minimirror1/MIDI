/*
 * view_5_deviceSetting.c
 *
 *  Created on: 2021. 4. 16.
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

#include "app_pid_midi_cmd.h"

#include "eeprom_manager.h"

extern Panel_Page_TypeDef page;

extern Comm_Page_TypeDef com_page;
extern Comm_Axle_TypeDef com_axle;

extern HC165_wheel_TypeDef wheel[8];
extern HC165_btn_TypeDef btn[8];

extern LongKey_TypeDef LongKeyWheel[8];

uint8_t f_v5_first = 1;

uint8_t tempCanid = 0;
extern uint8_t my_can_id;


#define CAN_ID_SLOT_NUM 7
void Change_canID(void) {

	int i = CAN_ID_SLOT_NUM;
	uint8_t f_new = 0;

	if (wheel[i].status.f_rot != ROT_CLEAR)
	{
		if (wheel[i].status.f_rot == ROT_CW)
		{
			tempCanid++;
			if(tempCanid == 0)
				tempCanid++;
		}
		else if (wheel[i].status.f_rot == ROT_CCW)
		{
			tempCanid--;
			if(tempCanid == 0)
				tempCanid--;
		}
		wheel[i].status.f_rot = ROT_CLEAR;
		f_new = 1;
	}

	if(f_new == 1)
	{
		f_new = 0;

		LCD_SetText_ADC_DEC(CAN_ID_SLOT_NUM, tempCanid);
	}

	panel_wheel_Led_rot(CAN_ID_SLOT_NUM, 0);
}

uint8_t f_v5_cancel = 0;
uint8_t f_v5_apply = 0;
void DeviceSettingApplyManager(void) {
	if (btn[7].status[2].btn == 1) //취소
	{
		if (f_v5_cancel == 0)
			f_v5_cancel = 1;
	}
	else
	{
		if (f_v5_cancel == 1)
			f_v5_cancel = 2;
	}

	if (btn[7].status[3].btn == 1) //적용
	{
		if (f_v5_apply == 0)
			f_v5_apply = 1;
	}
	else
	{
		if (f_v5_apply == 1)
			f_v5_apply = 2;
	}

	if (f_v5_apply == 2)
	{
		f_v5_apply = 0;
		f_v5_cancel = 0;

		f_v5_first = 1;

		if(my_can_id != tempCanid)
		{
			my_can_id = tempCanid;
			eeprom_write_8(VADDR_SETTING_CAN_ID, my_can_id);
		}




		View_Changer(VIEW_0_MAIN);

	}
	else if (f_v5_cancel == 2)
	{
		f_v5_apply = 0;
		f_v5_cancel = 0;

		View_Changer(VIEW_0_MAIN);
		f_v5_first = 1;

	}

}

void View_5_DeviceSetting(void) {

	static uint8_t toggleLed = 0;
	static uint32_t t_SetLed;

	if(f_v5_first == 1)
	{
		f_v5_first = 0;
		/*can id*/
		tempCanid = my_can_id;
		LCD_Write_String(CAN_ID_SLOT_NUM, 1, "MY ID", sizeof("MY ID"));
		LCD_SetText_ADC_DEC(CAN_ID_SLOT_NUM, tempCanid);

		LCD_Write_String(0, 1, "FW_VER", sizeof("FW_VER"));
		LCD_Write_String(0, 2, FW_VER_STR, sizeof(FW_VER_STR));

	}

	if (MAL_NonStopDelay(&t_SetLed, 500) == 1)
	{
		MAL_LED_Button_Control(7, LED_SELECT, toggleLed);
		MAL_LED_Button_Control(7, LED_MUTE, toggleLed);
		toggleLed ^= 1;
	}

	Change_canID();


	DeviceSettingApplyManager();


}

