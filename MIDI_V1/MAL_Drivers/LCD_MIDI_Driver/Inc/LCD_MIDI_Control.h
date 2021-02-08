/*
 * LCD_MIDI_Control.h
 *
 *  Created on: Feb 5, 2021
 *      Author: shin
 */

#ifndef LCD_MIDI_DRIVER_INC_LCD_MIDI_CONTROL_H_
#define LCD_MIDI_DRIVER_INC_LCD_MIDI_CONTROL_H_


#define CMD0_1       ((uint8_t) 0xE2 )
#define CMD0_2       ((uint8_t) 0x2F )
#define CMD0_3       ((uint8_t) 0x24 )
#define CMD0_4       ((uint8_t) 0xA2 )
#define CMD0_5       ((uint8_t) 0xFA )
#define CMD0_6       ((uint8_t) 0xB0 )
#define CMD0_7       ((uint8_t) 0xA0 )
#define CMD0_8       ((uint8_t) 0xA4 )
#define CMD0_9       ((uint8_t) 0xA6 )
#define CMD0_10      ((uint8_t) 0xC8 )
#define CMD0_11      ((uint8_t) 0x40 )
#define CMD0_12      ((uint8_t) 0xAF )

#define CMD1_1       ((uint8_t) 0x81 )
#define CMD1_a       ((uint8_t) 0x18 )
#define CMD1_b       ((uint8_t) 0x25 )
#define CMD1_3       ((uint8_t) 0xA6 )
#define CMD1_4       ((uint8_t) 0xE3 )

#define LCDcontrolStart0 ((uint8_t) 0x00 )
#define LCDcontrolStart1 ((uint8_t) 0x10 )

#define LCDcontrol0  ((uint8_t) 0xB0 )
#define LCDcontrol1  ((uint8_t) 0xB1 )
#define LCDcontrol2  ((uint8_t) 0xB2 )
#define LCDcontrol3  ((uint8_t) 0xB3 )
#define LCDcontrol4  ((uint8_t) 0xB4 )
#define LCDcontrol5  ((uint8_t) 0xB5 )
#define LCDcontrol6  ((uint8_t) 0xB6 )
#define LCDcontrol7  ((uint8_t) 0xB7 )



void MAL_LCD_Control_test(void);

#endif /* LCD_MIDI_DRIVER_INC_LCD_MIDI_CONTROL_H_ */
