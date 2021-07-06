/*
 * filter_manager.h
 *
 *  Created on: 2021. 4. 15.
 *      Author: shin
 */

#ifndef FILTER_MANAGER_INC_FILTER_MANAGER_H_
#define FILTER_MANAGER_INC_FILTER_MANAGER_H_


//#define FIXED_POINT
#define FLOATING_POINT

#ifdef FLOATING_POINT
typedef struct{
		uint32_t *RawData;
		uint32_t SmoothData;
		uint32_t filterData;
		float LPF_Beta; // 0<ß<1
}filter_TypeDef;
#endif

void filter_manager(void);
void filter_init(void);
int64_t map(int64_t x, int64_t in_min, int64_t in_max, int64_t out_min, int64_t out_max);

#endif /* FILTER_MANAGER_INC_FILTER_MANAGER_H_ */
