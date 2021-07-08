/*
 * panel_view.h
 *
 *  Created on: 2021. 3. 25.
 *      Author: shin
 */

#ifndef PANEL_MANAGER_INC_PANEL_VIEW_H_
#define PANEL_MANAGER_INC_PANEL_VIEW_H_

void View_Undo(void);
void View_Changer(PanelViewName_TypeDef changeView );
void View_Manager(void);


void View_0_Main(void);
void View_1_SettingPreview(void);
void View_2_SettingMenu(void);
void View_3_AxleChange(void);
void View_4_PageChange(void);
void View_5_DeviceSetting(void);
void View_6_SlideSetting(void);
#endif /* PANEL_MANAGER_INC_PANEL_VIEW_H_ */
