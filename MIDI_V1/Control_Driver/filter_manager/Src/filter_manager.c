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


void filter_calc(float *SmoothData, uint16_t *filterData, uint16_t RawData, float LPF_Beta)
{

	*SmoothData = *SmoothData - (LPF_Beta * (*SmoothData - RawData));
	*filterData = round(*SmoothData);
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
	       // Don't do the following shift if you want to do further
	       // calculations in fixed-point using SmoothData
	       SmoothDataINT = SmoothDataFP>> FP_Shift;
	    }
	}
}
#endif

void filter_manager(void)
{
	static uint32_t t_filter = 0;
	static int k = 0;

/*	if (MAL_NonStopDelay(&t_filter, 5) == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			filter_calc(&filter[i].SmoothData, &filter[i].filterData, *filter[i].RawData, filter[i].LPF_Beta);
		}
	}*/

	filter_calc(&filter[k].SmoothData, &filter[k].filterData, *filter[k].RawData, filter[k].LPF_Beta);
	k++;
	if(k > 8)
		k = 0;

}
