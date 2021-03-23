/*
 * long_key.h
 *
 *  Created on: 2021. 3. 23.
 *      Author: shin
 */

#ifndef KEY_MANAGER_INC_LONG_KEY_H_
#define KEY_MANAGER_INC_LONG_KEY_H_



#define KEY_LONG_TIME	500

typedef struct{

	uint8_t *pBtnSt;	//눌림상태



	uint32_t tLong;		//눌림시간 타이머
	uint8_t fPress; 	//눌림 플레그
	uint8_t fLongKey;	//길게 누름 활성
	//=============
	uint32_t PressTime;	//눌림 유지 시간

}LongKey_typeDef;

void LongKey(void);

#endif /* KEY_MANAGER_INC_LONG_KEY_H_ */
