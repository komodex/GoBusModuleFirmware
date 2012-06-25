#ifndef _CHARACTERLCD_H_
#define _CHARACTERLCD_H_

#include "config.h"

// Pin definitions
// LCD RS
#define CLCD_LCDRS_DDR PB_DDR_DDR5
#define CLCD_LCDRS_CR1 PB_CR1_C15
#define CLCD_LCDRS_ODR PB_ODR_ODR5
// LCD E
#define CLCD_LCDE_DDR PB_DDR_DDR4
#define CLCD_LCDE_CR1 PB_CR1_C14
#define CLCD_LCDE_ODR PB_ODR_ODR4

// Serial data
#define CLCD_SD_DDR PA_DDR_DDR1
#define CLCD_SD_CR1 PA_CR1_C11
#define CLCD_SD_ODR PA_ODR_ODR1
// STCP - Storage register clock
#define CLCD_STCP_DDR PC_DDR_DDR3
#define CLCD_STCP_CR1 PC_CR1_C13
#define CLCD_STCP_ODR PC_ODR_ODR3
// SHCP - Shift register clock
#define CLCD_SHCP_DDR PC_DDR_DDR4
#define CLCD_SHCP_CR1 PC_CR1_C14
#define CLCD_SHCP_ODR PC_ODR_ODR4

///////

void CharacterLCD_Init();
void CharacterLCD_SendCommand(u8 data);
void CharacterLCD_SendData(u8 data);
void CharacterLCD_Enable();

void CharacterLCD_SetLine1(u8* data, u8 start, u8 length);
void CharacterLCD_SetLine2(u8* data, u8 start, u8 length);

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

#endif
