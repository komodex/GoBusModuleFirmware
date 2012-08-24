#include "characterlcd.h"

u8 _initialized = 0;

u8 _rawID = 0;
u8 _rawType = 0;
u8 _rawData = 0;

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

  _initialized = 1;

  // Set up Timer 2 for PWM
  // Prescaler
  TIM2_PSCR_PSC = 0x04;
  // Auto-reload register
  TIM2_ARRH = 0x00;
  TIM2_ARRL = 0xFE; // TODO: FE and not FF?
  // Set default brightness
  CharacterLCD_SetColor(0x00, 0x00, 0x00);
  // Output compare mode
  TIM2_CCMR1_OC1M = 7;
  TIM2_CCMR2_OC2M = 7;
  TIM2_CCMR3_OC3M = 7;
  // Output polarity
  TIM2_CCER1_CC1P = 1;
  TIM2_CCER1_CC2P = 1;
  TIM2_CCER2_CC3P = 1;
  // Output enable
  TIM2_CCER1_CC1E = 1;
  TIM2_CCER1_CC2E = 1;
  TIM2_CCER2_CC3E = 1;
  // Enable
  TIM2_CR1_CEN = 1;
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
  u16 delay = 50;
  if (!_initialized)
    delay = 1000;

  CLCD_LCDE_ODR = 1;
  Delay(delay);
  CLCD_LCDE_ODR = 0;
  Delay(delay);
}

void CharacterLCD_SendRaw(u8 id, u8 isData, u8 value)
{
  _rawID = id;
  _rawType = isData;
  _rawData = value;

  if (isData)
    CharacterLCD_SendData(value);
  else
    CharacterLCD_SendCommand(value);
}

void CharacterLCD_GetRaw(u8 result[], u8 offset)
{
  result[offset + 0] = _rawID;
  result[offset + 1] = _rawType;
  result[offset + 2] = _rawData;
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

void CharacterLCD_GetLine1(u8 result[], u8 offset)
{
  for (u8 i = 0; i < 16; i++)
    result[offset + i] = _line1[i];
}

void CharacterLCD_GetLine2(u8 result[], u8 offset)
{
  for (u8 i = 0; i < 16; i++)
    result[offset + i] = _line2[i];
}

void CharacterLCD_SetColor(u8 red, u8 green, u8 blue)
{
  TIM2_CCR1L = red;
  TIM2_CCR2L = green;
  TIM2_CCR3L = blue;
}

void CharacterLCD_GetColor(u8 result[], u8 offset)
{
  result[offset + 0] = TIM2_CCR1L;
  result[offset + 1] = TIM2_CCR2L;
  result[offset + 2] = TIM2_CCR3L;
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
