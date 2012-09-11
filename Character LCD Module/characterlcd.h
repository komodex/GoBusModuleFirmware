#ifndef _CHARACTERLCD_H_
#define _CHARACTERLCD_H_

#include "config.h"

// Pin definitions
// LCD RS
#define CLCD_LCDRS_DDR PB_DDR_DDR4
#define CLCD_LCDRS_CR1 PB_CR1_C14
#define CLCD_LCDRS_ODR PB_ODR_ODR4
// LCD E
#define CLCD_LCDE_DDR PB_DDR_DDR5
#define CLCD_LCDE_CR1 PB_CR1_C15
#define CLCD_LCDE_ODR PB_ODR_ODR5

// Serial data
#define CLCD_SD_DDR PA_DDR_DDR2
#define CLCD_SD_CR1 PA_CR1_C12
#define CLCD_SD_ODR PA_ODR_ODR2
// SHCP - Shift register clock
#define CLCD_SHCP_DDR PA_DDR_DDR1
#define CLCD_SHCP_CR1 PA_CR1_C11
#define CLCD_SHCP_ODR PA_ODR_ODR1

///////

void CharacterLCD_Init();
void CharacterLCD_SendCommand(u8 data);
void CharacterLCD_SendData(u8 data);
void CharacterLCD_Enable();

void CharacterLCD_SendRaw(u8 id, u8 isData, u8 value);
void CharacterLCD_GetRaw(u8 result[], u8 offset);

void CharacterLCD_SetLine(u8 line, u8* data, u8 start, u8 length);
void CharacterLCD_GetLine(u8 line, u8 result[], u8 offset);

void CharacterLCD_SetCustomChar(u8 index, u8* data, u8 start);
void CharacterLCD_GetCustomChar(u8 index, u8 result[], u8 offset);

void CharacterLCD_SetColor(u8 red, u8 green, u8 blue);
void CharacterLCD_GetColor(u8 result[], u8 offset);

void CharacterLCD_ProcessLoop();

//////
// Commands

// LCD function
#define LCD_FUNCTION_8BIT_2LINES 0x38

// LCD Display
#define LCD_DISP_OFF 0x08
#define LCD_DISP_ON 0x0C

// LCD Instructions
#define LCD_CLR 0x01

// LCD Entry Mode
#define LCD_ENTRY_INC 0x06

// Move cursor commands
#define LCD_CURSOR_ROW1 0x80
#define LCD_CURSOR_ROW2 0xC0
#define LCD_CURSOR_ROW3 0x94
#define LCD_CURSOR_ROW4 0xD4

// Custom character addresses
#define LCD_CUSTOM_CHAR 0x40

#endif
