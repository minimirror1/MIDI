/*
MIDI LCD text  data

midi lcd 텍스트 픽셀 데이터

@ LCD 
 픽셀 : 가로 128 , 세로 64
 출력 : ((세로 8줄 페러럴 데이터)*가로 128번)*8번 

*/
#ifndef MIDI_LCD_textData2_H_
#define MIDI_LCD_textData2_H_


typedef enum{
  LCD_TEXT_H0 = 0,
  LCD_TEXT_H1 ,
}LCDtext_H_No_typedef;

typedef enum{
  TEXT_SIZE_A = 0,
  TEXT_SIZE_B,
  TEXT_SIZE_C,
}TEXT_SIZE_typedef;

typedef struct 
{
  LCDtext_H_No_typedef  H;      // text 줄 위치
  TEXT_SIZE_typedef     size;   // text size 선택
//  uint8_t text[20];
//  uint8_t textA[10][2];         // text size - 가로 : 12,      세로 : 24(8*3)
//  uint8_t textB[5][2];          // text size - 가로 : 24(8*3), 세로 : 32(8*4)
  uint8_t textA[20];         // text size - 가로 : 12,      세로 : 24(8*3)
  uint8_t textB[10];          // text size - 가로 : 24(8*3), 세로 : 32(8*4)
  uint8_t textC[3];
  uint8_t data[128][8];         // LCD pixel data
  
  uint8_t  text_A[36];
  
}LCDtextData_typedef;


extern const uint8_t ASCII_24[128][36];
extern LCDtextData_typedef  LCDtext; 

void LCD_pixel_init(LCDtextData_typedef *LCDtext);
void LCD_pixel_write_sizeA(LCDtextData_typedef *LCDtext, uint8_t ascii, uint8_t No);

#endif  /* MIDI_LCD_textData2_H_ */
