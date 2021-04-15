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
		uint16_t *RawData;
		float SmoothData;
		uint16_t filterData;
		float LPF_Beta; // 0<ß<1
}filter_TypeDef;
#endif

void filter_manager(void);
void filter_init(void);

#endif /* FILTER_MANAGER_INC_FILTER_MANAGER_H_ */
