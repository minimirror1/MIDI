/*
 * panel_page.h
 *
 *  Created on: 2021. 3. 30.
 *      Author: shin
 */

#ifndef PANEL_MANAGER_INC_PANEL_PAGE_H_
#define PANEL_MANAGER_INC_PANEL_PAGE_H_




typedef struct{
		uint8_t f_change;
		uint8_t changeNum;

}Panel_Page_TypeDef;

void Set_Page(uint8_t pageNum);
void Page_Display(void);


#endif /* PANEL_MANAGER_INC_PANEL_PAGE_H_ */
