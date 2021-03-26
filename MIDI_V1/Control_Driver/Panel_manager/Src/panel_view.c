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

extern PanelManager_TypeDef panel;

//=======================================================================================
//=======================================================================================

//=======================================================================================
//=======================================================================================
void View_Changer(PanelViewName_TypeDef changeView )
{

	if (changeView < VIEW_LAST_NUM) {
		if (panel.view.nowView != changeView) {
			panel.view.f_ViewChange = 1;
			panel.view.changeView = changeView;
			MAL_LCD_Set_Clear();
		}
	}
}
void View_Undo(void)
{
	View_Changer(panel.view.lastView);
}

void View_Selector(void)
{
	if(panel.view.f_ViewChange == 1)
	{
		panel.view.f_ViewChange = 0;
		if (panel.view.changeView < VIEW_LAST_NUM) {
			panel.view.lastView = panel.view.nowView;
			panel.view.nowView = panel.view.changeView;
			switch(panel.view.nowView)
			{
			case VIEW_0_MAIN:
				panel.view.viewFnc = View_0_Main;
				break;
			case VIEW_1_SETTING_PREVIEW:
				panel.view.viewFnc = View_1_SettingPreview;
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

void View_Manager(void)
{
	View_Selector();
	panel.view.viewFnc(); //선택된 뷰
}