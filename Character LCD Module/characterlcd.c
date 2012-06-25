#include "characterlcd.h"

u8 _line1[16];
u8 _line2[16];

u8 _line1Update = 0;
u8 _line2Update = 0;

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

void CharacterLCD_SetLine(u8* destination, u8* data, u8 start, u8 length)
{
  for (u8 i = 0; (start + i) < (start + length); i++)
    destination[i] = data[start + i];
}

void CharacterLCD_SetLine1(u8* data, u8 start, u8 length)
{
  CharacterLCD_SetLine(_line1, data, start, length);
  _line1Update = 1;
}

void CharacterLCD_SetLine2(u8* data, u8 start, u8 length)
{
  CharacterLCD_SetLine(_line2, data, start, length);
  _line2Update = 1;
}

void CharacterLCD_ProcessLoop()
{
  if (_line1Update)
  {
    _line1Update = 0;
    CharacterLCD_SendCommand(LCD_CURSOR_ROW1);
    for (int i = 0; i < 16; i++)
      CharacterLCD_SendData(_line1[i]);
  }
  if (_line2Update)
  {
    _line2Update = 0;
    CharacterLCD_SendCommand(LCD_CURSOR_ROW2);
    for (int i = 0; i < 16; i++)
      CharacterLCD_SendData(_line2[i]);
  }
}
