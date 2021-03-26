/*
 * panel_manager.h
 *
 *  Created on: 2021. 3. 23.
 *      Author: shin
 */

#ifndef PANEL_MANAGER_INC_PANEL_MANAGER_H_
#define PANEL_MANAGER_INC_PANEL_MANAGER_H_




typedef enum{

	VIEW_0_MAIN = 0,
	VIEW_1_SETTING_PREVIEW,
	VIEW_LAST_NUM
}PanelViewName_TypeDef;

typedef struct{
	uint8_t f_ViewChange;
	PanelViewName_TypeDef nowView;	//현재 보여지는 뷰 번호
	PanelViewName_TypeDef lastView;	//이전에 보여졌던 뷰 번호
	PanelViewName_TypeDef changeView;	//이전에 보여졌던 뷰 번호

	void (*viewFnc)();
}PanelView_TypeDef;

typedef struct{
	uint8_t *btn[4];
	uint8_t *wheelBtn;
	uint8_t *wheelRot;
	uint16_t *slideTouch;
	uint16_t *slideAdc;
}Panel_In_TypeDef;

typedef struct{
	uint8_t *btn[4];
	uint8_t *wheelGauge;
	uint8_t *barGauge;
}Panel_Out_TypeDef;

typedef struct{
	Panel_In_TypeDef in;	//btn wheel slide
	Panel_Out_TypeDef out;	//LED
}Panel_Interface;

typedef struct{

	PanelView_TypeDef view;
	Panel_Interface	interface[8];

}PanelManager_TypeDef;

void Panel_Manager(void);

#endif /* PANEL_MANAGER_INC_PANEL_MANAGER_H_ */
