/*
 * filter_manager.c
 *
 *  Created on: 2021. 4. 15.
 *      Author: shin
 */


#include "main.h"
#include "math.h"
#include "non_stop_delay_main.h"
#include "filter_manager.h"

#include "X_Touch_Extender_MotorAdc_packet.h"

#include "communication_info.h"
#include "panel_page.h"

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;
extern Comm_Axle_TypeDef com_axle;
extern Comm_Page_TypeDef com_page;
extern Panel_Page_TypeDef page;
filter_TypeDef filter[8] = {0,};

void filter_init(void)
{
	for(int i = 0; i < 8; i++)
	{
		filter[i].LPF_Beta = 1;
		filter[i].SmoothData = 0;
		filter[i].RawData = &extenderPacket.adc[i];
	}

	for(int i = 0; i < MAX_AXLE_INFO;i++)
	{
		com_axle.axleInfo[i].setPage.max = 4095;
		com_axle.axleInfo[i].setPage.min = 0;
		com_axle.axleInfo[i].setPage.range = 4095;
	}
}


int64_t map(int64_t x, int64_t in_min, int64_t in_max, int64_t out_min, int64_t out_max)
{
//	if(in_min <= in_max)
//	{
//		if((x < in_min)||( in_max < x))
//		{
//			x = (in_min+in_max) /2;
//		}
//	}
//	else
//	{
//		if((x < in_max)||( in_min < x))
//		{
//			x = (in_min+in_max) /2;
//		}
//	}
	int64_t temp = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//	if(temp > 0)
//		temp--;
	 return temp;
}


void filter_calc(int i, uint32_t *SmoothData, uint32_t *filterData, uint32_t RawData, float LPF_Beta)
{
/*	int32_t errorVal = *SmoothData - RawData;

	int32_t reflection = errorVal * LPF_Beta;

	*SmoothData = *SmoothData - reflection;*/

	//*filterData = *SmoothData;

	//*filterData = map(*SmoothData, 0, 0x7FFFFFFF, TEST_OUT_MIN, TEST_OUT_MAX);


/*	if(*SmoothData >= 0x3FFFFFFF)
		*SmoothData = 0x3FFFFFFF;

	 *filterData = map(*SmoothData, 0, 0x3FFFFFFF, TEST_OUT_MIN, TEST_OUT_MAX);*/

	if (RawData >= com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].setPage.range << ADC_SHIFT)
		RawData = com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].setPage.range << ADC_SHIFT;


	int32_t errorVal = *SmoothData - RawData;

	int32_t reflection = errorVal * LPF_Beta;

	*SmoothData = *SmoothData - reflection;

	if (*SmoothData >= com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].setPage.range << ADC_SHIFT)
		*SmoothData = com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].setPage.range << ADC_SHIFT;



	*filterData = map(
			*SmoothData,
			0,
			com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].setPage.range << ADC_SHIFT,
			com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].setPage.min,
			com_axle.axleInfo[com_page.pageInfo[page.changeNum].slot_axle[i].listNum].setPage.max);


/*	*SmoothData = *SmoothData - (LPF_Beta * (*SmoothData - RawData));
	*filterData = round(*SmoothData);*/
}

#ifdef FIXED_POINT
void filter_calc_p()
{
	int RawData;
	signed long SmoothDataINT;
	signed long SmoothDataFP;
	int Beta = 4; // Length of the filter < 16

	void main (void){
	    while(1){
	       // Function that brings Fresh Data into RawData
	       RawData = GetRawData();
	       RawData <<= FP_Shift; // Shift to fixed point
	       SmoothDataFP = (SmoothDataFP<< Beta)-SmoothDataFP;
	       SmoothDataFP += RawData;
	       SmoothDataFP >>= Beta;
	       // Don't do the fllowing shift if you want to do further
	       // calculations in fixed-point using SmoothData
	       SmoothDataINT = SmoothDataFP>> FP_Shift;
	    }
	}
}
#endif

void filter_manager(void)
{
	static uint32_t t_filter = 0;

	if (MAL_NonStopDelay(&t_filter, 20) == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			filter_calc(i,&filter[i].SmoothData, &filter[i].filterData, *filter[i].RawData, filter[i].LPF_Beta);
		}
	}

}
