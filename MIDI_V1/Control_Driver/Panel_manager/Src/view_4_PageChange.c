/*
 * view_4_PageChange.c
 *
 *  Created on: 2021. 3. 29.
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

extern Panel_Page_TypeDef page;

extern Comm_Page_TypeDef com_page;
extern Comm_Axle_TypeDef com_axle;

extern HC165_wheel_TypeDef wheel[8];
extern HC165_btn_TypeDef btn[8];

uint8_t tempPageNum;

uint8_t f_pageChange = SET;
uint8_t changePageCnt = 0;

uint8_t f_v4_first = 1;

void ChangePage_Display(void)
{
	if (f_pageChange == SET)
	{
		f_pageChange = RESET;
		for (int i = 0; i < 8; i++)
		{
			if (com_axle.axleInfo[com_page.pageInfo[tempPageNum].slot_axle[i].axleNum].nick_name != 0)
				LCD_Write_String(i, 1, com_axle.axleInfo[com_page.pageInfo[tempPageNum].slot_axle[i].axleNum].nick_name, 10);

			if (com_axle.axleInfo[com_page.pageInfo[tempPageNum].slot_axle[i].axleNum].axle_num != 0)
			{
				LCD_SetText_AXLENUM_DEC(i, com_axle.axleInfo[com_page.pageInfo[tempPageNum].slot_axle[i].axleNum].axle_num);
				LCD_pixel_write_sizeA_p(i, '|', 14);

				LCD_SetText_ADC_DEC(i, tempPageNum);
				LCD_pixel_write_sizeA_p(i, 'P', 16);

				LCD_CenterLine(i);
			}
			else
			{
				LCD_Pixel_wirte_logo(i, ' ');
			}


		}
	}
}


void Change_Page(void)
{
	int i = 7;
	if (wheel[i].status.f_rot != ROT_CLEAR)
	{
		if (wheel[i].status.f_rot == ROT_CW)
		{
			changePageCnt++;
			if (changePageCnt > com_page.list.cnt)
				changePageCnt = 1;

		}
		else if (wheel[i].status.f_rot == ROT_CCW)
		{
			changePageCnt--;
			if (changePageCnt == 0)
				changePageCnt = com_page.list.cnt;
		}
		tempPageNum = changePageCnt;
		wheel[i].status.f_rot = ROT_CLEAR;
		f_pageChange = SET;
	}

}

void PageApplyManager(void)
{
	if(btn[7].status[2].btn == 1)//취소
	{
		View_Changer(VIEW_0_MAIN);
		f_v4_first = 1;

	}
	else if(btn[7].status[3].btn == 1)//적용
	{
		f_v4_first = 1;

		page.changeNum = tempPageNum;
		View_Changer(VIEW_0_MAIN);

	}
}

void View_4_PageChange(void)
{
	static uint8_t toggleLed = 0;
	static uint32_t t_SetLed;

	if(f_v4_first == 1)
	{
		f_v4_first = 0;
		f_pageChange = SET;
		tempPageNum = page.changeNum;
		changePageCnt = tempPageNum;

		panel_wheel_Led_rot(7,1);
	}
	Change_Page();
	ChangePage_Display();
	PageApplyManager();


	if(MAL_NonStopDelay(&t_SetLed, 500) == 1)
	{
		MAL_LED_Button_Control(7, LED_SELECT, toggleLed);
		MAL_LED_Button_Control(7, LED_MUTE, toggleLed);
		toggleLed ^= 1;

/*		if(toggleLed == 1)
		{
			MAL_LED_Wheel_Control(7, 13);
		}
		else
		{
			MAL_LED_Wheel_Control(7, 0);
		}*/
	}
	panel_wheel_Led_rot(7,0);
}














