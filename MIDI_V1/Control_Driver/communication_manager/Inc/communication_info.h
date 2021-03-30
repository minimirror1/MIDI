/*
 * communication_info.h
 *
 *  Created on: 2021. 3. 29.
 *      Author: shin
 */

#ifndef COMMUNICATION_MANAGER_INC_COMMUNICATION_INFO_H_
#define COMMUNICATION_MANAGER_INC_COMMUNICATION_INFO_H_

#define AXLE_SET_PAGE 			4
#define AXLE_NICK_NAME_LEN	 	10

#define MAX_AXLE_INFO	256
#define MAX_PAGE_INFO	256
#define MAX_SLOT_NUM	8


typedef struct{
	uint32_t flag[8];

}Comm_SetFlag_TypeDef;


typedef struct{
	uint8_t set_page_num;
	uint16_t max;
	uint16_t min;
}Comm_AxleInfo_SetPage_TypeDef;

typedef struct{
	uint8_t axle_num;
	char nick_name[AXLE_NICK_NAME_LEN];
	Comm_AxleInfo_SetPage_TypeDef setPage[AXLE_SET_PAGE];
	uint8_t listNum;
}Comm_AxleInfo_TypeDef;



typedef struct{
	uint8_t cnt;
	Comm_AxleInfo_TypeDef *pAxleInfo[MAX_PAGE_INFO];
}Comm_AxleList_TypeDef;


typedef struct{
	Comm_SetFlag_TypeDef setFlag;
	Comm_AxleInfo_TypeDef axleInfo[MAX_AXLE_INFO];

	Comm_AxleList_TypeDef list;
}Comm_Axle_TypeDef;


//================================================

typedef struct{
	uint8_t axleNum;
	uint8_t setPageNum;

}Comm_Slot_TypeDef;


typedef struct{
	uint8_t pageNum;
	Comm_Slot_TypeDef slot_axle[MAX_SLOT_NUM];
	uint8_t listNum;
}Comm_PageInfo_TypeDef;

typedef struct{
	uint8_t cnt;
	Comm_PageInfo_TypeDef *pPageInfo[MAX_PAGE_INFO];
}Comm_PageList_TypeDef;

typedef struct{
	Comm_SetFlag_TypeDef setFlag;
	Comm_PageInfo_TypeDef pageInfo[MAX_PAGE_INFO];

	Comm_PageList_TypeDef	list;
}Comm_Page_TypeDef;


#endif /* COMMUNICATION_MANAGER_INC_COMMUNICATION_INFO_H_ */
