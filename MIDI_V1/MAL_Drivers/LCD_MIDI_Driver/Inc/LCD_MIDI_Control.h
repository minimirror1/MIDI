/*
 * LCD_MIDI_Control.h
 *
 *  Created on: Feb 5, 2021
 *      Author: shin
 */

#ifndef LCD_MIDI_DRIVER_INC_LCD_MIDI_CONTROL_H_
#define LCD_MIDI_DRIVER_INC_LCD_MIDI_CONTROL_H_


void LCD_Pixel_wirte_logo(uint8_t lcdNum);
void LCD_pixel_write_sizeA_p(uint8_t lcdNum, char ascii, uint8_t No);

void LCD_SetText_DEC(uint8_t lcdNum, uint32_t value);

#endif /* LCD_MIDI_DRIVER_INC_LCD_MIDI_CONTROL_H_ */
