
#include "sevensegment.h"

static void WriteData(u16 data);
static void SetDigit(u8 digit);
static void UnsetDigit(u8 digit);
static void Latch();

u8 _digit1;
u8 _digit2;
u8 _digit3;
u8 _digit4;
u8 _colon;
u8 _apostrophe;

u8 _currentDigit = 1;

void SevenSegment_Init()
{
  // Initialize port pins
  // SDO
  SSEG_SDO_DDR = 1;
  SSEG_SDO_CR1 = 1;
  // CLK
  SSEG_CLK_DDR = 1;
  SSEG_CLK_CR1 = 1;
  // Latch
  SSEG_LATCH_DDR = 1;
  SSEG_LATCH_CR1 = 1;

  // Digit 1
  SSEG_D1_DDR = 1;
  SSEG_D1_CR1 = 1;
  // Digit 2
  SSEG_D2_DDR = 1;
  SSEG_D2_CR1 = 1;
  // Digit 3
  SSEG_D3_DDR = 1;
  SSEG_D3_CR1 = 1;
  // Digit 4
  SSEG_D4_DDR = 1;
  SSEG_D4_CR1 = 1;

  // Make sure all digits are turned off
  UnsetDigit(1);
  UnsetDigit(2);
  UnsetDigit(3);
  UnsetDigit(4);

  // Clear the LED driver
  WriteData(0x0000);
  Latch();

  // Set up Timer 4
  // Prescaler
  TIM4_PSCR_PSC = 0x07;
  // Auto-reload register
  TIM4_ARR = 0x70;
  // Set priority to level 2 (to not interfere with SPI interrupts)
  ITC_SPR6_VECT23SPR = 0x00;
  // Enable
  TIM4_CR1_CEN = 1;
  // Update interrupt enable
  TIM4_IER_UIE = 1;

  // Set up Timer 2 for PWM
  // Prescaler
//  PD_DDR_DDR4 = 1;
  TIM2_PSCR_PSC = 0x00;
  // Auto-reload register
  TIM2_ARRH = 0x03;
  TIM2_ARRL = 0xFE; // TODO: FE and not FF?
  // Set default brightness
  SevenSegment_SetBrightness(0x03, 0xFF);
  // Output compare mode
  TIM2_CCMR2_OC2M = 7;
  // Output enable
  TIM2_CCER1_CC2E = 1;
  // Enable
  TIM2_CR1_CEN = 1;


  //SevenSegment_SetDisplayValues(0xff,0xFF,0xff,0xff);

  //SetDigit(2);
  //PD_DDR_DDR4 = 1;
  //PD_CR1_C14 = 1;
}

// Display values
void SevenSegment_SetDisplayValues(u8 d1, u8 d2, u8 d3, u8 d4)
{
  _digit1 = d1;
  _digit2 = d2;
  _digit3 = d3;
  _digit4 = d4;
}

void SevenSegment_GetDisplayValues(u8 result[], u8 offset)
{
  result[offset + 0] = _digit1;
  result[offset + 1] = _digit2;
  result[offset + 2] = _digit3;
  result[offset + 3] = _digit4;
}

// Brightness
void SevenSegment_SetBrightness(u8 valueh, u8 valuel)
{
  TIM2_CCR2H = valueh;
  TIM2_CCR2L = valuel;
}
void SevenSegment_GetBrightness(u8 result[], u8 offset)
{
  result[offset + 0] = TIM2_CCR2H;
  result[offset + 1] = TIM2_CCR2L;
}

// Colon
void SevenSegment_SetColon(u8 value)
{
  if (value)
    _colon = (1<<0);
  else
    _colon = 0;
}

u8 SevenSegment_GetColon()
{
  if (_colon)
    return 1;
  return 0;
}

// Apostrophe
void SevenSegment_SetApostrophe(u8 value)
{
  if (value)
    _apostrophe = (1<<1);
  else
    _apostrophe = 0;
}

u8 SevenSegment_GetApostrophe()
{
  if (_apostrophe)
    return 1;
  return 0;
}

// ---------------

static void WriteData(u16 data)
{
  for (u8 i = 16; i > 0; i--)
  {
    if ((data & 0x8000) == 0x8000)
      SSEG_SDO_ODR = 1;
    else
      SSEG_SDO_ODR = 0;

    SSEG_CLK_ODR = 1;
    SSEG_CLK_ODR = 0;

    data = (data << 1);
  }
}

static void SetDigit(u8 digit)
{
  switch (digit)
  {
    case 1:

      SSEG_D1_ODR = 1;
      break;
    case 2:
      SSEG_D2_ODR = 1;
      break;
    case 3:
      SSEG_D3_ODR = 1;
      break;
    case 4:
      SSEG_D4_ODR = 1;
      break;
  }
}

static void UnsetDigit(u8 digit)
{
  switch (digit)
  {
    case 1:
      SSEG_D1_ODR = 0;
      break;
    case 2:
      SSEG_D2_ODR = 0;
      break;
    case 3:
      SSEG_D3_ODR = 0;
      break;
    case 4:
      SSEG_D4_ODR = 0;
      break;
  }
}

static void Latch()
{
  SSEG_LATCH_ODR = 1;
  SSEG_LATCH_ODR = 0;
}


// -----------

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQ)
{
  PB_ODR_ODR4 = 1;
  // Clear flag
  TIM4_SR_UIF = 0;

  switch (_currentDigit)
  {
    case 1:
      UnsetDigit(4);
      Latch();
      SetDigit(1);
      WriteData((_apostrophe << 8) | _digit2);
      break;

    case 2:
      UnsetDigit(1);
      Latch();
      SetDigit(2);
      WriteData((_colon << 8) | _digit3);
      break;

    case 3:
      UnsetDigit(2);
      Latch();
      SetDigit(3);
      WriteData(_digit4);
      break;

    case 4:
      UnsetDigit(3);
      Latch();
      SetDigit(4);
      WriteData((_colon << 8) | _digit1);
      break;
  }

  _currentDigit++;
  if (_currentDigit > 4)
    _currentDigit = 1;
  PB_ODR_ODR4 = 0;
}