/*
MIDI LCD text  data

midi lcd 텍스트 픽셀 데이터

*/

#include "main.h"
#include "MIDI_LCD_textData2.h"
#include <string.h>

LCDtextData_typedef  LCDtext; 

const uint8_t ASCII_24[128][36] = {    // 4608bytes   가로 : 12, 세로 : 24(8*3)
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 0x00
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0xC0,0x20,0x20,0x10,0x10,0x10,0x20,0x20,0xC0,0x00, // 0x01
   0x00,0xFF,0x00,0x00,0x46,0x86,0x80,0x86,0x46,0x00,0x00,0xFF,
   0x00,0x00,0x03,0x04,0x04,0x08,0x08,0x08,0x04,0x04,0x03,0x00},
  {0x00,0x00,0xC0,0xE0,0xE0,0xF0,0xF0,0xF0,0xE0,0xE0,0xC0,0x00, // 0x02
   0x00,0xFF,0xFF,0xFF,0xB9,0x79,0x7F,0x79,0xB9,0xFF,0xFF,0xFF,
   0x00,0x00,0x03,0x07,0x07,0x0F,0x0F,0x0F,0x07,0x07,0x03,0x00},
  {0x00,0x00,0x80,0xC0,0xC0,0x80,0x00,0x80,0xC0,0xC0,0x80,0x00, // 0x03
   0x00,0x1E,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x1E,
   0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x07,0x03,0x01,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0x80,0x00,0x00,0x00,0x00, // 0x04
   0x00,0x10,0x38,0x7C,0xFE,0xFF,0xFF,0xFF,0xFE,0x7C,0x38,0x10,
   0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x03,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0x80,0x00,0x00,0x00,0x00, // 0x05
   0x00,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xF0,
   0x00,0x00,0x01,0x01,0x09,0x0C,0x0F,0x0C,0x09,0x01,0x01,0x00},
  {0x00,0x00,0x00,0x00,0xC0,0xE0,0xE0,0xE0,0xC0,0x00,0x00,0x00, // 0x06
   0x00,0xF8,0xFC,0xFC,0xFB,0xFF,0xFF,0xFF,0xFB,0xFC,0xFC,0xF8,
   0x00,0x00,0x01,0x01,0x09,0x0C,0x0F,0x0C,0x09,0x01,0x01,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 0x07
   0x00,0x00,0x00,0x1C,0x3E,0x7F,0x7F,0x7F,0x3E,0x1C,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // 0x08
   0x00,0xFF,0xFF,0xE3,0xC1,0x80,0x80,0x80,0xC1,0xE3,0xFF,0xFF,
   0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 0x09
   0x00,0x00,0x00,0x3C,0x42,0x81,0x81,0x81,0x42,0x3C,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // 0x0A
   0x00,0xFF,0xFF,0x81,0x3C,0x7E,0x7E,0x7E,0x3C,0x81,0xFF,0xFF,
   0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x60,0xE0,0xE0,0xE0,0x00, // 0x0B
   0x00,0xC0,0xE0,0x30,0x18,0x1C,0x36,0xE3,0xC1,0x01,0x03,0x00,
   0x00,0x03,0x07,0x0C,0x08,0x08,0x0C,0x07,0x03,0x00,0x00,0x00},
  {0x00,0x80,0xC0,0x40,0x60,0x20,0x20,0x60,0x40,0xC0,0x80,0x00, // 0x0C
   0x00,0x07,0x8F,0x88,0x98,0xF0,0xF0,0x98,0x88,0x8F,0x07,0x00,
   0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x30,0x60,0xC0,0x80,0x00, // 0x0D
   0x00,0x00,0x00,0x00,0x80,0x80,0xFF,0x00,0x20,0x18,0x0F,0x00,
   0x00,0x00,0x06,0x0F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0xF8,0x98,0x30,0x60,0xC0,0x00,0x00, // 0x0E
   0x00,0x80,0xC0,0xE0,0xE0,0xFF,0x01,0x03,0x06,0xFF,0x00,0x00,
   0x00,0x01,0x03,0x03,0x01,0x0C,0x1E,0x1F,0x0F,0x07,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00, // 0x0F
   0x00,0x10,0x11,0xBA,0x44,0x82,0x83,0x82,0x44,0xBA,0x11,0x10,
   0x00,0x00,0x01,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x01,0x00},
  {0x00,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 0x10
   0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x7E,0x7E,0x3C,0x3C,0x18,0x18,
   0x00,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0, // 0x11
   0x00,0x18,0x18,0x3C,0x3C,0x7E,0x7E,0xFF,0xFF,0xFF,0xFF,0xFF,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07},
  {0x00,0x00,0x40,0x60,0x30,0xF8,0xF8,0x30,0x60,0x40,0x00,0x00, // 0x12
   0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x01,0x03,0x06,0x0F,0x0F,0x06,0x03,0x01,0x00,0x00},
  {0x00,0x00,0xF0,0xF8,0xF0,0x00,0x00,0xF0,0xF8,0xF0,0x00,0x00, // 0x13
   0x00,0x00,0x07,0x3F,0x07,0x00,0x00,0x07,0x3F,0x07,0x00,0x00,
   0x00,0x00,0x06,0x0F,0x06,0x00,0x00,0x06,0x0F,0x06,0x00,0x00},
  {0x00,0xE0,0xF0,0x30,0x10,0x10,0xF0,0xF0,0x10,0xF0,0xF0,0x10, // 0x14
   0x00,0x03,0x07,0x06,0x04,0x04,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
   0x00,0x00,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x0F,0x0F,0x08},
  {0x00,0x00,0xC0,0xE0,0x30,0x10,0x10,0x10,0x30,0x60,0xC0,0x00, // 0x15
   0x00,0x00,0x18,0x3D,0x67,0x42,0x42,0x42,0xE6,0xBC,0x18,0x00,
   0x00,0x00,0x03,0x06,0x0C,0x08,0x08,0x08,0x0C,0x07,0x03,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 0x16
   0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
   0x00,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x00},
  {0x00,0x00,0x80,0xC0,0x60,0xF0,0xF0,0x60,0xC0,0x80,0x00,0x00, // 0x17
   0x00,0x00,0x80,0x80,0x00,0xFF,0xFF,0x00,0x80,0x80,0x00,0x00,
   0x00,0x00,0x18,0x19,0x1B,0x1F,0x1F,0x1B,0x19,0x18,0x00,0x00},
  {0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xF0,0xE0,0xC0,0x80,0x00, // 0x18
   0x00,0x01,0x01,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x01,0x01,
   0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0xF8,0xF8,0xF8,0xF8,0xF8,0x00,0x00,0x00, // 0x19
   0x00,0x40,0xC0,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0xC0,0x40,
   0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x07,0x03,0x01,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x80,0xC0,0x00,0x00,0x00,0x00,0x00,0x00, // 0x1A
   0x08,0x1C,0x3E,0x7F,0xFF,0xFF,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,
   0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x80,0x00,0x00,0x00,0x00, // 0x1B
   0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0xFF,0xFF,0x7F,0x3E,0x1C,0x08,
   0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 0x1C
   0x00,0x00,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 0x1D
   0x00,0x18,0x3C,0x7E,0xDB,0x18,0x18,0x18,0xDB,0x7E,0x3C,0x18,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00, // 0x1E
   0x00,0x80,0xE0,0xF8,0xFE,0xFF,0xFF,0xFE,0xF8,0xE0,0x80,0x00,
   0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00},
  {0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00, // 0x1F
   0x00,0x01,0x07,0x1F,0x7F,0xFF,0xFF,0x7F,0x1F,0x07,0x01,0x00,
   0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // space
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0xFE,0x00,0x00,0x00,0x00, // !
   0x00,0x00,0x00,0x00,0x00,0x01,0x3F,0x01,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x06,0x0F,0x06,0x00,0x00,0x00,0x00},
  {0x00,0x46,0x6F,0x3F,0x1E,0x00,0x46,0x6F,0x3F,0x1E,0x00,0x00, // "
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0xF0,0xF0,0x80,0x80,0x80,0xF8,0xF8,0xC0,0xC0,0x00, // #
   0xC3,0xC3,0xFF,0xFF,0x61,0x61,0x61,0xFF,0xFF,0x30,0x30,0x00,
   0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x07,0x07,0x00,0x00,0x00},
  {0xE0,0xF0,0x38,0x18,0x08,0xFE,0xFE,0x08,0x18,0x30,0x78,0x78, // $
   0x01,0x03,0x07,0x06,0x06,0xFF,0xFF,0x0C,0x0C,0x1C,0xF8,0xF0,
   0x0F,0x0F,0x06,0x0C,0x0C,0x3F,0x3F,0x0C,0x0C,0x0E,0x07,0x03},
  {0xF8,0xFC,0x06,0x06,0xFC,0xF8,0x00,0x80,0xE0,0x38,0x0C,0x00, // %
   0x00,0x01,0x83,0xC3,0x71,0x9C,0xC7,0x61,0x60,0xC0,0x80,0x00,
   0x18,0x0E,0x03,0x00,0x00,0x0F,0x1F,0x30,0x30,0x1F,0x0F,0x00},
  {0x00,0x3C,0xEE,0x86,0xC6,0x6E,0x3C,0x00,0x00,0x00,0x00,0x00, // &
   0xF0,0xFC,0x0E,0x03,0x07,0x1C,0xF0,0xC0,0x00,0x90,0xF0,0x30,
   0x07,0x0F,0x1C,0x18,0x18,0x18,0x0C,0x0F,0x07,0x0F,0x18,0x18},
  {0x00,0x00,0x00,0x00,0x00,0x46,0x6F,0x3F,0x1E,0x00,0x00,0x00, // '
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0x3C,0x06,0x01,0x00,0x00, // (
   0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x18,0x20,0x00,0x00},
  {0x00,0x00,0x01,0x06,0x3C,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00, // )
   0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x20,0x18,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,0x00},
  {0xC0,0xC0,0x80,0x00,0x70,0xF8,0x70,0x00,0x80,0xC0,0xC0,0x00, // *
   0xC0,0xE1,0x61,0x12,0x8C,0xF3,0x8C,0x12,0x61,0xE1,0xC0,0x00,
   0x00,0x00,0x00,0x00,0x03,0x07,0x03,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00, // +
   0x00,0x0C,0x0C,0x0C,0x0C,0xFF,0xFF,0x0C,0x0C,0x0C,0x0C,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ,
   0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x23,0x37,0x1F,0x0F,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // -
   0x00,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x06,0x0F,0x0F,0x06,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0x3C,0x0F,0x03,0x00, // /
   0x00,0x00,0xC0,0xF0,0x3C,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,
   0x0C,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0xF8,0xFC,0x0E,0x06,0x03,0x03,0x03,0x06,0x0E,0xFC,0xF0,0x00, // 0
   0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
   0x01,0x03,0x07,0x06,0x0C,0x0C,0x0C,0x06,0x07,0x03,0x01,0x00},
  {0x00,0x00,0x18,0x1C,0x0E,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00, // 1
   0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x0C,0x0C,0x0F,0x0F,0x0C,0x0C,0x00,0x00,0x00},
  {0x18,0x3C,0x3E,0x06,0x03,0x03,0x03,0x07,0x0E,0xFC,0xF8,0x00, // 2
   0x00,0x00,0x00,0x80,0xC0,0x60,0x38,0x1C,0x07,0x03,0x00,0x00,
   0x0C,0x0E,0x0F,0x0D,0x0C,0x0C,0x0C,0x0C,0x0C,0x0F,0x0F,0x00},
  {0x00,0x1C,0x1E,0x06,0x03,0x03,0x03,0x03,0x86,0xFE,0x78,0x00, // 3
   0x80,0xC0,0xC0,0x00,0x03,0x03,0x03,0x07,0x0D,0xF8,0xF0,0x00,
   0x01,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0E,0x07,0x07,0x01,0x00},
  {0x00,0x00,0x00,0x80,0xE0,0x38,0x0E,0xFF,0xFF,0x00,0x00,0x00, // 4
   0x60,0x78,0x6E,0x63,0x60,0x60,0x60,0xFF,0xFF,0x60,0x60,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0F,0x0F,0x0C,0x00,0x00},
  {0x00,0xFF,0xFF,0x03,0x83,0x83,0x83,0x83,0x03,0x03,0x00,0x00, // 5
   0x00,0x83,0x83,0x03,0x01,0x01,0x01,0x03,0x87,0xFE,0xF8,0x00,
   0x03,0x07,0x07,0x0E,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00,0x00},
  {0xC0,0xF0,0x38,0x1C,0x8E,0x86,0x87,0x83,0x03,0x03,0x00,0x00, // 6
   0xFF,0xFF,0x06,0x03,0x01,0x01,0x01,0x03,0x07,0xFE,0xF8,0x00,
   0x00,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00,0x00},
  {0x0F,0x0F,0x03,0x03,0x03,0x03,0x03,0x03,0xE3,0xFF,0x1F,0x00, // 7
   0x00,0x00,0x00,0x00,0x00,0xC0,0xF8,0x3F,0x07,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x0E,0x0F,0x01,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x7C,0xFE,0x87,0x03,0x03,0x03,0x87,0xFE,0x7C,0x00,0x00, // 8
   0xF8,0xFC,0x0E,0x07,0x03,0x03,0x03,0x07,0x0E,0xFC,0xF8,0x00,
   0x01,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x01,0x00},
  {0xF0,0xFC,0x0E,0x07,0x03,0x03,0x03,0x07,0x0E,0xFC,0xF0,0x00, // 9
   0x01,0x07,0x0E,0x1C,0x18,0x18,0x18,0x8C,0xE6,0x7F,0x1F,0x00,
   0x00,0x0C,0x0C,0x0C,0x06,0x06,0x03,0x01,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0xC0,0xE0,0xE0,0xC0,0x00,0x00,0x00,0x00, // :
   0x00,0x00,0x00,0x00,0xC0,0xE1,0xE1,0xC0,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0xC0,0xE0,0xE0,0xC0,0x00,0x00,0x00,0x00, // ;
   0x00,0x00,0x00,0x00,0xC0,0xE1,0xE1,0xC0,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x08,0x0D,0x07,0x03,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00, // <
   0x04,0x0E,0x1B,0x31,0x60,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x06,0x0C,0x08,0x00},
  {0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00, // =
   0x00,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x02,0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00,0x00,0x00,0x00, // >
   0x00,0x00,0x00,0x00,0x80,0xC0,0x60,0x31,0x1B,0x0E,0x04,0x00,
   0x08,0x0C,0x06,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x18,0x3C,0x1E,0x07,0x03,0x03,0x03,0x83,0xC7,0xFE,0x7C,0x00, // ?
   0x00,0x00,0x00,0x00,0x00,0x3C,0x3F,0x03,0x01,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x04,0x0E,0x0E,0x04,0x00,0x00,0x00,0x00},
  {0xF8,0x0C,0x86,0xC3,0x63,0x23,0x63,0xC3,0xE6,0x0C,0xF8,0x00, // @
   0xFF,0x00,0x1F,0x3F,0x70,0x60,0x20,0x3F,0x7F,0x60,0x3F,0x00,
   0x01,0x03,0x06,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x06,0x02,0x00},
  {0x00,0x00,0x00,0xE3,0xFB,0x1F,0x1F,0xF8,0xE0,0x00,0x00,0x00, // A
   0x00,0xC0,0xFE,0x3F,0x19,0x18,0x18,0x19,0x3F,0xFE,0xC0,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x00,0x0C,0x0F,0x0F,0x0C},
  {0x03,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x87,0xFE,0xFC,0x00, // B
   0x00,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x07,0xFD,0xF8,0x00,
   0x0C,0x0F,0x0F,0x0C,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00},
  {0xF0,0xFC,0x0E,0x07,0x03,0x03,0x03,0x03,0x06,0x0F,0x1F,0x00, // C
   0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,
   0x00,0x03,0x07,0x06,0x0C,0x0C,0x0C,0x0C,0x07,0x07,0x03,0x00},
  {0x03,0xFF,0xFF,0x03,0x03,0x03,0x03,0x07,0x0E,0xFC,0xF8,0x00, // D
   0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
   0x0C,0x0F,0x0F,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x01,0x00},
  {0x03,0xFF,0xFF,0x03,0x03,0x03,0x03,0x83,0x83,0x0F,0x0F,0x00, // E
   0x00,0xFF,0xFF,0x03,0x03,0x03,0x03,0x07,0x07,0x00,0x00,0x00,
   0x0C,0x0F,0x0F,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0F,0x0F,0x00},
  {0x03,0xFF,0xFF,0x03,0x03,0x03,0x03,0x83,0x83,0x0F,0x0F,0x00, // F
   0x00,0xFF,0xFF,0x03,0x03,0x03,0x03,0x07,0x07,0x00,0x00,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0xF0,0xFC,0x0E,0x07,0x03,0x03,0x03,0x03,0x06,0x1F,0x1F,0x00, // G
   0xFF,0xFF,0x00,0x00,0x00,0x00,0x30,0x30,0x30,0xF0,0xF0,0x30,
   0x00,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00},
  {0x03,0xFF,0xFF,0x03,0x00,0x00,0x00,0x03,0xFF,0xFF,0x03,0x00, // H
   0x00,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0xFF,0xFF,0x00,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x0C,0x0F,0x0F,0x0C,0x00},
  {0x00,0x00,0x00,0x03,0x03,0xFF,0xFF,0x03,0x03,0x00,0x00,0x00, // I
   0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x0C,0x0C,0x0F,0x0F,0x0C,0x0C,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0xFF,0xFF,0x03,0x00, // J
   0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,
   0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00,0x00},
  {0x03,0xFF,0xFF,0x83,0xE0,0xE0,0x38,0x3B,0x0F,0x0F,0x03,0x00, // K
   0x00,0xFF,0xFF,0x1F,0x79,0x70,0xC0,0xC0,0x00,0x00,0x00,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x01,0x0D,0x0F,0x0F,0x0C,0x00},
  {0x03,0xFF,0xFF,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // L
   0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x0C,0x0F,0x0F,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0F,0x0F,0x00},
  {0x03,0xFF,0xFF,0xF0,0x80,0x00,0x80,0xF0,0xFF,0xFF,0x03,0x00, // M
   0x00,0xFF,0xFF,0x01,0x0F,0x7C,0x0F,0x01,0xFF,0xFF,0x00,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x0C,0x0F,0x0F,0x0C,0x00},
  {0x03,0xFF,0xFF,0x3C,0xE0,0x00,0x00,0x03,0xFF,0xFF,0x03,0x00, // N
   0x00,0xFF,0xFF,0x00,0x01,0x0F,0x78,0xC0,0xFF,0xFF,0x00,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x03,0x0F,0x0F,0x00,0x00},
  {0xF0,0xFC,0x1E,0x07,0x03,0x03,0x03,0x07,0x1E,0xFC,0xF0,0x00, // O
   0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0x00,
   0x00,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00,0x00},
  {0x03,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x07,0xFE,0xFC,0x00, // P
   0x00,0xFF,0xFF,0x06,0x06,0x06,0x06,0x06,0x07,0x03,0x01,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0xF0,0xFC,0x1E,0x07,0x03,0x03,0x03,0x07,0x1E,0xFC,0xF0,0x00, // Q
   0xFF,0xFF,0x80,0xC0,0x40,0xC0,0xC0,0x80,0x00,0xFF,0xFF,0x00,
   0x00,0x03,0x07,0x0E,0x0C,0x0C,0x0D,0x0F,0x07,0x07,0x0C,0x08},
  {0x03,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x07,0xFE,0xF8,0x00, // R
   0x00,0xFF,0xFF,0x06,0x06,0x1E,0x7E,0xF6,0xC7,0x03,0x00,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x0D,0x0F,0x0F,0x0C,0x00},
  {0x7C,0xFE,0xC6,0x83,0x83,0x03,0x03,0x06,0x1F,0x1F,0x00,0x00, // S
   0xC0,0xC0,0x01,0x01,0x03,0x03,0x07,0x06,0x0E,0xFC,0xF8,0x00,
   0x0F,0x0F,0x03,0x06,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x01,0x00},
  {0x0F,0x0F,0x03,0x03,0x03,0xFF,0xFF,0x03,0x03,0x03,0x0F,0x0F, // T
   0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x00},
  {0x03,0xFF,0xFF,0x03,0x00,0x00,0x00,0x03,0xFF,0xFF,0x03,0x00, // U
   0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,
   0x00,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00,0x00},
  {0x03,0x3F,0xFF,0xC3,0x00,0x00,0x00,0x00,0xC3,0xFF,0x3F,0x03, // V
   0x00,0x00,0x03,0x3F,0xFC,0xC0,0xC0,0xFC,0x3F,0x03,0x00,0x00,
   0x00,0x00,0x00,0x00,0x01,0x0F,0x0F,0x01,0x00,0x00,0x00,0x00},
  {0x03,0xFF,0xFF,0x03,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0x03, // W
   0x00,0x01,0xFF,0xFE,0x80,0xFF,0xFF,0x80,0xFE,0xFF,0x01,0x00,
   0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00},
  {0x03,0x07,0x1F,0x79,0xE0,0x80,0x80,0xE0,0x79,0x1F,0x07,0x03, // X
   0x00,0x00,0x80,0xE0,0x79,0x1F,0x1F,0x79,0xE0,0x80,0x00,0x00,
   0x0C,0x0E,0x0F,0x0D,0x00,0x00,0x00,0x00,0x0D,0x0F,0x0E,0x0C},
  {0x03,0x07,0x3F,0xFB,0xC0,0x00,0x00,0xC0,0xFB,0x3F,0x07,0x03, // Y
   0x00,0x00,0x00,0x01,0x07,0xFE,0xFE,0x07,0x01,0x00,0x00,0x00,
   0x00,0x00,0x00,0x0C,0x0C,0x0F,0x0F,0x0C,0x0C,0x00,0x00,0x00},
  {0x0F,0x0F,0x03,0x03,0x03,0x03,0xC3,0xF3,0x3F,0x0F,0x03,0x00, // Z
   0x00,0x00,0xC0,0xF0,0x3C,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,
   0x0C,0x0F,0x0F,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0F,0x0F,0x00},
  {0x00,0x00,0x00,0x00,0xFF,0xFF,0x03,0x03,0x03,0x03,0x00,0x00, // [
   0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x1F,0x1F,0x18,0x18,0x18,0x18,0x00,0x00},
  {0x83,0xFF,0xFF,0x83,0x80,0x80,0x80,0x80,0x83,0xFF,0xFF,0x83, /* \ */
   0x08,0x09,0xFF,0xFE,0x88,0xFF,0xFF,0x88,0xFE,0xFF,0x09,0x08,
   0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00},
  {0x00,0x00,0x03,0x03,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,0x00, // ]
   0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,
   0x00,0x00,0x18,0x18,0x18,0x18,0x1F,0x1F,0x00,0x00,0x00,0x00},
  {0x00,0x30,0x18,0x0C,0x06,0x03,0x03,0x06,0x0C,0x18,0x30,0x00, // ^
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // _
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C},
  {0x00,0x00,0x02,0x07,0x0E,0x18,0x30,0x00,0x00,0x00,0x00,0x00, // `
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00, // a
   0x82,0xC3,0x61,0x21,0x31,0x31,0x31,0x33,0xFF,0xFE,0x00,0x00,
   0x07,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x06,0x07,0x0F,0x0C,0x00},
  {0x03,0xFF,0xFF,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00, // b
   0x00,0xFF,0xFF,0x03,0x01,0x01,0x01,0x03,0x07,0xFE,0xF8,0x00,
   0x0C,0x0F,0x07,0x06,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00,0x00},
  {0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x80,0x80,0x00, // c
   0xF8,0xFE,0x07,0x03,0x01,0x01,0x01,0x01,0x03,0x0F,0x0F,0x00,
   0x01,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00},
  {0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x83,0x03,0xFF,0xFF,0x00, // d
   0xF8,0xFE,0x07,0x03,0x01,0x01,0x01,0x01,0x03,0xFF,0xFF,0x00,
   0x00,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x06,0x0F,0x0F,0x00},
  {0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00, // e
   0xFC,0xFE,0x37,0x33,0x31,0x31,0x31,0x33,0x37,0x3E,0x3C,0x00,
   0x00,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00},
  {0x80,0x80,0x80,0xFC,0xFE,0x87,0x83,0x83,0x83,0x07,0x06,0x00, // f
   0x01,0x01,0x01,0xFF,0xFF,0x01,0x01,0x01,0x01,0x00,0x00,0x00,
   0x00,0x0C,0x0C,0x0F,0x0F,0x0C,0x0C,0x0C,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x80, // g
   0xFE,0xFF,0x03,0x01,0x01,0x01,0x01,0x01,0x03,0xFF,0xFF,0x01,
   0x21,0x63,0xE7,0xC6,0xC6,0xC6,0xC6,0xC6,0xE3,0x7F,0x3F,0x00},
  {0x03,0xFF,0xFF,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00, // h
   0x00,0xFF,0xFF,0x06,0x03,0x01,0x01,0x01,0x03,0xFF,0xFE,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x00,0x0C,0x0F,0x0F,0x0C},
  {0x00,0x00,0x00,0x80,0x8C,0x9E,0x9E,0x0C,0x00,0x00,0x00,0x00, // i
   0x00,0x00,0x00,0x01,0x01,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x0C,0x0C,0x0F,0x0F,0x0C,0x0C,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x80,0x80,0x8C,0x9E,0x9E,0x0C,0x00,0x00, // j
   0x00,0x00,0x00,0x00,0x01,0x01,0x01,0xFF,0xFF,0x00,0x00,0x00,
   0x30,0x70,0xE0,0xC0,0xC0,0xC0,0xE0,0x7F,0x3F,0x00,0x00,0x00},
  {0x01,0xFF,0xFF,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00, // k
   0x00,0xFF,0xFF,0x20,0x30,0x78,0xCD,0x87,0x03,0x01,0x01,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x0D,0x0F,0x0E,0x0C,0x00},
  {0x00,0x00,0x00,0x03,0x03,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00, // l
   0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x0C,0x0C,0x0F,0x0F,0x0C,0x0C,0x00,0x00,0x00},
  {0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00, // m
   0x01,0xFF,0xFF,0x03,0x01,0xFF,0xFF,0x03,0x01,0xFF,0xFF,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x0F,0x0F,0x0C,0x00,0x0F,0x0F,0x0C},
  {0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00, // n
   0x01,0xFF,0xFF,0x06,0x03,0x01,0x01,0x03,0xFF,0xFE,0x00,0x00,
   0x0C,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x0C,0x0F,0x0F,0x0C,0x00},
  {0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00, // o
   0xF8,0xFE,0x07,0x03,0x01,0x01,0x01,0x03,0x07,0xFE,0xF8,0x00,
   0x00,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00,0x00},
  {0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00, // p
   0x01,0xFF,0xFF,0x03,0x01,0x01,0x01,0x03,0x07,0xFE,0xF8,0x00,
   0xC0,0xFF,0xFF,0xC6,0xCC,0x0C,0x0C,0x0E,0x07,0x03,0x00,0x00},
  {0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00, // q
   0xF8,0xFE,0x07,0x03,0x01,0x01,0x01,0x03,0xFF,0xFF,0x01,0x00,
   0x00,0x03,0x07,0x0E,0x0C,0x0C,0xCC,0xC6,0xFF,0xFF,0xC0,0x00},
  {0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00, // r
   0x01,0xFF,0xFF,0x06,0x03,0x01,0x01,0x01,0x03,0x07,0x07,0x00,
   0x0C,0x0F,0x0F,0x0C,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x00, // s
   0x0E,0x1F,0x1B,0x31,0x31,0x31,0x61,0x63,0xE7,0xC7,0x80,0x00,
   0x0F,0x0F,0x06,0x0C,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00},
  {0x80,0x80,0x80,0xFE,0xFF,0x80,0x80,0x80,0x80,0x80,0x00,0x00, // t
   0x01,0x01,0x01,0xFF,0xFF,0x01,0x01,0x01,0x01,0x01,0x00,0x00,
   0x00,0x00,0x00,0x03,0x07,0x0E,0x0C,0x0C,0x0E,0x07,0x03,0x00},
  {0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00, // u
   0x01,0xFF,0xFF,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0x00,0x00,
   0x00,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x06,0x07,0x0F,0x0C,0x00},
  {0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80, // v
   0x01,0x03,0x1F,0xFD,0xE0,0x00,0x00,0xE0,0xFD,0x1F,0x03,0x01,
   0x00,0x00,0x00,0x00,0x03,0x0F,0x0F,0x03,0x00,0x00,0x00,0x00},
  {0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80, // w
   0x01,0x0F,0xFF,0xF1,0x80,0xF8,0xF8,0x80,0xF1,0xFF,0x0F,0x01,
   0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00},
  {0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00, // x
   0x01,0x03,0x07,0x8D,0xF8,0x70,0xF8,0x8D,0x07,0x03,0x01,0x00,
   0x0C,0x0E,0x0F,0x0D,0x00,0x00,0x00,0x0D,0x0F,0x0E,0x0C,0x00},
  {0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80, // y
   0x01,0x07,0x1F,0x79,0xE0,0x80,0x80,0xE0,0x79,0x1F,0x07,0x01,
   0x00,0xC0,0xC0,0xE0,0xF9,0xDF,0x07,0x01,0x00,0x00,0x00,0x00},
  {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00, // z
   0x03,0x03,0x81,0xC1,0x61,0x31,0x19,0x0D,0x07,0x03,0x01,0x00,
   0x0E,0x0F,0x0D,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0F,0x0F,0x00},
  {0x00,0x00,0x00,0x00,0x00,0xFC,0xFE,0x07,0x03,0x01,0x01,0x00, // {
   0x00,0x00,0x04,0x0E,0x1B,0xF1,0xE0,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,0x38,0x30,0x20,0x20,0x00},
  {0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00, // |
   0x00,0x00,0x00,0x00,0x00,0xE7,0xE7,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x01,0x01,0x03,0x07,0xFE,0xFC,0x00,0x00,0x00,0x00,0x00, // }
   0x00,0x00,0x00,0x00,0x00,0xE0,0xF1,0x1F,0x0E,0x04,0x00,0x00,
   0x00,0x20,0x20,0x30,0x38,0x1F,0x0F,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ~
   0x08,0x0C,0x06,0x06,0x06,0x0C,0x18,0x18,0x18,0x0C,0x04,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x3C,0x66,0x42,0x42,0x66,0x3C,0x00,0x00,0x00, // 0x7F
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};


const uint8_t Tsize[3][2] = {
  {12, 24},  // text A
  {24, 36},  // text B
  {36, 48},  // text C 
};

void LCD_pixel_init(LCDtextData_typedef *LCDtext)
{
  for (int i = 0; i<128;i++)
    memset(LCDtext->data[i],0x00,sizeof(uint8_t)*8);
}

//void LCD_pixel_write(LCDtextData_typedef *LCDtext, uint8_t text[], TEXT_SIZE_typedef size)
//{
//  LCDtext->size = size;
//  
// switch (size)
// {
// case TEXT_SIZE_A:
//   
//   break;
// case TEXT_SIZE_B:
//   
//   break;  
// case TEXT_SIZE_C:
//   
//   break;  
// }
//  
//}

void LCD_pixel_write_sizeA(LCDtextData_typedef *LCDtext, uint8_t ascii, uint8_t No)
{
  LCDtext->size = TEXT_SIZE_A;
  // 텍스트 픽셀값 얻기
  uint8_t text[36];
  for(int i=0;i<36;i++)
  {
    text[i] = ASCII_24[ascii][i];
 
  }
  
  // 텍스트 위치 선정
  uint8_t H = 1;
  uint8_t W = 0;
  if (No >= 10)  
  {
    H = 1+4;
    W = (No-10)*12;
  }
  else 
  {
    W = No*12;
  }
  
  //   변수에 데이터 저장
  for (int i=0; i<12; i++)
     LCDtext->data[i+W][H] = text[i];
  H++;
  for (int i=0; i<12; i++)
     LCDtext->data[i+W][H] = text[i+12];
  H++;
  for (int i=0; i<12; i++)
     LCDtext->data[i+W][H] = text[i+24];
  
}
                           