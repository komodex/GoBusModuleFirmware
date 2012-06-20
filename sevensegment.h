
#ifndef _SEVENSEGMENT_H_
#define _SEVENSEGMENT_H_

#include "config.h"
//#include "iostm8s003f3.h"


// SDO
#define SSEG_SDO_ODR PA_ODR_ODR2
#define SSEG_SDO_DDR PA_DDR_DDR2
#define SSEG_SDO_CR1 PA_CR1_C12
// CLK
#define SSEG_CLK_ODR PC_ODR_ODR4
#define SSEG_CLK_DDR PC_DDR_DDR4
#define SSEG_CLK_CR1 PC_CR1_C14
// Latch
#define SSEG_LATCH_ODR PC_ODR_ODR3
#define SSEG_LATCH_DDR PC_DDR_DDR3
#define SSEG_LATCH_CR1 PC_CR1_C13

// Digit 1
#define SSEG_D1_ODR PD_ODR_ODR4
#define SSEG_D1_DDR PD_DDR_DDR4
#define SSEG_D1_CR1 PD_CR1_C14
// Digit 2
#define SSEG_D2_ODR PD_ODR_ODR5
#define SSEG_D2_DDR PD_DDR_DDR5
#define SSEG_D2_CR1 PD_CR1_C15
// Digit 3
#define SSEG_D3_ODR PD_ODR_ODR6
#define SSEG_D3_DDR PD_DDR_DDR6
#define SSEG_D3_CR1 PD_CR1_C16
// Digit 4
#define SSEG_D4_ODR PA_ODR_ODR1
#define SSEG_D4_DDR PA_DDR_DDR1
#define SSEG_D4_CR1 PA_CR1_C11



void SevenSegment_Init();

// Display values
void SevenSegment_SetDisplayValues(u8 d1, u8 d2, u8 d3, u8 d4);
void SevenSegment_GetDisplayValues(u8 result[], u8 offset);

// Brightness
void SevenSegment_SetBrightness(u8 valueh, u8 valuel);
void SevenSegment_GetBrightness(u8 result[], u8 offset);

// Colon
void SevenSegment_SetColon(u8 value);
u8   SevenSegment_GetColon();

// Apostrophe
void SevenSegment_SetApostrophe(u8 value);
u8   SevenSegment_GetApostrophe();

#endif
