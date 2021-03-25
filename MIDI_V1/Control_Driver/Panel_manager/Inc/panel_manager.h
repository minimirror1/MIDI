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
	VIEW_1_LONGKEY
}PanelViewName_TypeDef;

typedef struct{
	PanelViewName_TypeDef nowView;	//현재 보여지는 뷰 번호
	PanelViewName_TypeDef lastView;	//이전에 보여졌던 뷰 번호

	void (*viewFnc)();
}PanelView_TypeDef;

typedef struct{
	uint8_t *btn[4];
	uint8_t *wheelBtn;
	uint8_t *wheelRot;
	uint8_t *slideTouch;
	uint16_t *slideAdc;
}Panel_In_TypeDef;

typedef struct{
	uint8_t *btn[4];
	uint8_t *wheel[13];
	uint8_t *bar[8];
}Panel_Out_TypeDef;

typedef struct{
	Panel_In_TypeDef in;
	Panel_Out_TypeDef out;
}Panel_Interface;

typedef struct{

	PanelView_TypeDef view;
	Panel_Interface	interface;

}PanelManager_TypeDef;

#endif /* PANEL_MANAGER_INC_PANEL_MANAGER_H_ */
