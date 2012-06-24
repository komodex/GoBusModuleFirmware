#include "characterlcd.h"

void Delay(u16 delay)
{
  while (delay--);
}

void CharacterLCD_Init()
{
  // LCD pins
  CLCD_LCDRS_DDR = 1;
  CLCD_LCDE_DDR = 1;
  // Shift register pins
  CLCD_SD_DDR = 1;
  CLCD_SD_CR1 = 1;
  CLCD_STCP_DDR = 1;
  CLCD_STCP_CR1 = 1;
  CLCD_SHCP_DDR = 1;
  CLCD_SHCP_CR1 = 1;

  // Delay 50ms at the start
  Delay(20000); // 10ms
  Delay(20000); // 10ms
  Delay(20000); // 10ms
  Delay(20000); // 10ms
  Delay(20000); // 10ms

  // Function set
  CharacterLCD_SendCommand(LCD_FUNCTION_8BIT_2LINES);
  Delay(10000); // 5ms
  CharacterLCD_SendCommand(LCD_FUNCTION_8BIT_2LINES);
  Delay(10000); // 5ms
  CharacterLCD_SendCommand(LCD_FUNCTION_8BIT_2LINES);
  // Display off
  CharacterLCD_SendCommand(LCD_DISP_OFF);
  // Clear
  CharacterLCD_SendCommand(LCD_CLR);
  // Entry mode
  CharacterLCD_SendCommand(LCD_ENTRY_INC);
  // Display on
  CharacterLCD_SendCommand(LCD_DISP_ON);
}

void CharacterLCD_Send(u8 data)
{
  for (u8 i = 8; i > 0; i--)
  {
    if ((data & 0x80) == 0x80)
      CLCD_SD_ODR = 1;
    else
      CLCD_SD_ODR = 0;

    // Latch the data
    CLCD_SHCP_ODR = 1;
    CLCD_SHCP_ODR = 0;

    data = (data << 1);
  }

  // Latch the output
  CLCD_STCP_ODR = 1;
  CLCD_STCP_ODR = 0;

  CharacterLCD_Enable();
}

void CharacterLCD_SendCommand(u8 data)
{
  CLCD_LCDRS_ODR = 0;
  CharacterLCD_Send(data);
}

void CharacterLCD_SendData(u8 data)
{
  CLCD_LCDRS_ODR = 1;
  CharacterLCD_Send(data);
}

void CharacterLCD_Enable()
{
  CLCD_LCDE_ODR = 1;
  Delay(1000);
  CLCD_LCDE_ODR = 0;
  Delay(1000);
}
