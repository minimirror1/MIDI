/*
 * LCD_MIDI_Control.h
 *
 *  Created on: Feb 5, 2021
 *      Author: shin
 */

#ifndef LCD_MIDI_DRIVER_INC_LCD_MIDI_CONTROL_H_
#define LCD_MIDI_DRIVER_INC_LCD_MIDI_CONTROL_H_



void LCD_Pixel_wirte_newLogo(uint8_t lcdNum);
void LCD_Pixel_wirte_logo(uint8_t lcdNum, char logo);

void LCD_pixel_write_sizeA_p(uint8_t lcdNum, char ascii, uint8_t No);
void LCD_Write_String(uint8_t lcdNum,uint8_t line, char *str, uint8_t len);
void LCD_CenterLine(uint8_t lcdNum);

void LCD_SetText_AXLENUM_DEC(uint8_t lcdNum, uint8_t group_num,uint8_t motor_num);
void LCD_SetText_ADC_DEC(uint8_t lcdNum, uint32_t value);
void MAL_LCD_Set_EvLevel(uint8_t val);
void MAL_LCD_Set_AllOn(void);
void MAL_LCD_Set_Clear(void);

#endif /* LCD_MIDI_DRIVER_INC_LCD_MIDI_CONTROL_H_ */
