/*
 * can_header.h
 *
 *  Created on: 2021. 10. 27.
 *      Author: shin
 */

#ifndef CAN_COM_INC_CAN_HEADER_H_
#define CAN_COM_INC_CAN_HEADER_H_



#pragma pack(1)
typedef struct{
    union {
        struct {
            uint32_t emc : 1;
            uint32_t srcId : 8;
            uint32_t tarId : 8;
            uint32_t cmdType : 1;
            uint32_t cmd : 10;
            uint32_t stream : 1;
            uint32_t res: 3;
        };
        uint32_t Header;
    };
    uint8_t payload[0];
}CAN_Header_TypeDef;




#pragma pack()

#endif /* CAN_COM_INC_CAN_HEADER_H_ */
