/*
 * panel_view.c
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
#include "panel_page.h"

extern PanelManager_TypeDef panel;
extern Panel_Page_TypeDef page;
//=======================================================================================
//=======================================================================================

//=======================================================================================
//=======================================================================================
void View_Changer(PanelViewName_TypeDef changeView) {

	if (changeView < VIEW_LAST_NUM)
	{
		if (panel.view.nowView != changeView)
		{
			panel.view.f_ViewChange = 1;
			panel.view.changeView = changeView;

		}
	}
}
void View_Undo(void) {
	View_Changer(panel.view.lastView);
}

void View_Selector(void) {
	if (panel.view.f_ViewChange == 1)
	{
		panel.view.f_ViewChange = 0;
		if (panel.view.changeView < VIEW_LAST_NUM)
		{
			panel.view.lastView = panel.view.nowView;
			panel.view.nowView = panel.view.changeView;

			MAL_LCD_Set_Clear();
			for (int i = 0; i < 8; i++)
			{
				LCD_CenterLine(i);
				MAL_LED_BackLight_Control(i, LED_WHITE);
				MAL_LED_BarGauge_Control(i, 0);
				MAL_LED_Wheel_Control(i, 0);
				MAL_LED_Button_Control(i, 0, LED_OFF);
				MAL_LED_Button_Control(i, 1, LED_OFF);
				MAL_LED_Button_Control(i, 2, LED_OFF);
				MAL_LED_Button_Control(i, 3, LED_OFF);
			}

			switch (panel.view.nowView)
			{
				case VIEW_0_MAIN:
					panel.view.viewFnc = View_0_Main;
					page.f_change = 1; //페이지 불러오기
					break;
				case VIEW_1_SETTING_PREVIEW:
					panel.view.viewFnc = View_1_SettingPreview;
					break;
				case VIEW_2_SETTING_MENU:
					panel.view.viewFnc = View_2_SettingMenu;
					break;
				case VIEW_3_AXLE_CHANGE:
					panel.view.viewFnc = View_3_AxleChange;
					break;
				case VIEW_4_PAGE_CHANGE:
					panel.view.viewFnc = View_4_PageChange;
					break;
				case VIEW_5_DEVICE_SETTING:
					panel.view.viewFnc = View_5_DeviceSetting;
					break;
				case VIEW_LAST_NUM:
					panel.view.viewFnc = View_0_Main;
					break;
				default:
					panel.view.viewFnc = View_0_Main;
					break;
			}
		}
	}
}

void View_Manager(void) {

	panel.view.viewFnc(); //선택된 뷰
	View_Selector();
	static uint8_t f_first = 1;
	if (f_first)
	{
		f_first = 0;
		for (int i = 0; i < 8; i++)
			LCD_CenterLine(i);
	}

}
