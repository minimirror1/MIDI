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

extern X_Touch_Extender_Packet_HandleTypeDef extenderPacket;
filter_TypeDef filter[8] = {0,};

void filter_init(void)
{
	for(int i = 0; i < 8; i++)
	{
		filter[i].LPF_Beta = 1;
		filter[i].SmoothData = 0;
		filter[i].RawData = &extenderPacket.adc[i];
	}
}


int64_t map(int64_t x, int64_t in_min, int64_t in_max, int64_t out_min, int64_t out_max)
{
	 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void filter_calc(uint32_t *SmoothData, uint32_t *filterData, uint32_t RawData, float LPF_Beta)
{
	int32_t errorVal = *SmoothData - RawData;

	int32_t reflection = errorVal * LPF_Beta;

	*SmoothData = *SmoothData - reflection;

	//*filterData = *SmoothData;

	//*filterData = map(*SmoothData, 0, 0x7FFFFFFF, TEST_OUT_MIN, TEST_OUT_MAX);
	if(*SmoothData >= 0x3FFFFFFF)
		*SmoothData = 0x3FFFFFFF;

	*filterData = map(*SmoothData, 0, 0x3FFFFFFF, TEST_OUT_MIN, TEST_OUT_MAX);


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
			filter_calc(&filter[i].SmoothData, &filter[i].filterData, *filter[i].RawData, filter[i].LPF_Beta);
		}
	}

}
