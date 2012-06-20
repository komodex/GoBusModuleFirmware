#include "config.h"

int main( void )
{
  // Set up the clock
  CLK_CKDIVR_CPUDIV = 0;
  CLK_CKDIVR_HSIDIV = 0;

  // Temp stuff
  PB_DDR_DDR5 = 1;
  PB_CR1_C15 = 1;
  PB_CR2_C25 = 1;
  PB_DDR_DDR4 = 1;
  PB_CR1_C14 = 1;
  PB_CR2_C24 = 1;
  // End temp stuff

  SPI_Init();
  SPI_Reset();

  __enable_interrupt();

  SevenSegment_Init();

  // TEMP TEMP TEMP
  // Setting up the uart
  /*
  UART1_CR2_TEN = 1;
  UART1_BRR2 = 0x01;
  UART1_BRR1 = 0x01;
*/
  // TEMP TEMP TEMP

  while(1)
  {
  }

}

void SendIRQ()
{
  IRQ_DDR = 1;
  __no_operation();
  IRQ_DDR = 0;
}

void HandleMessage(u8* rxBuffer, u8* txBuffer)
{
  switch (rxBuffer[1])
  {
    // Display value
    case CMD_DISPLAYVALUE | CMD_READ:
      txBuffer[1] = CMD_DISPLAYVALUE | CMD_READ;
      SevenSegment_GetDisplayValues(txBuffer, 2);
      SendIRQ();
      break;

    case CMD_DISPLAYVALUE | CMD_WRITE:
      SevenSegment_SetDisplayValues(rxBuffer[2], rxBuffer[3], rxBuffer[4], rxBuffer[5]);
      break;

    // Brightness
    case CMD_BRIGHTNESS | CMD_READ:
      txBuffer[1] = CMD_BRIGHTNESS | CMD_READ;
      SevenSegment_GetBrightness(txBuffer, 2);
      SendIRQ();
      break;

    case CMD_BRIGHTNESS | CMD_WRITE:
      SevenSegment_SetBrightness(rxBuffer[2], rxBuffer[3]);
      break;

    // Colon
    case CMD_COLON | CMD_READ:
      txBuffer[1] = CMD_COLON | CMD_READ;
      txBuffer[2] = SevenSegment_GetColon();
      SendIRQ();
      break;

    case CMD_COLON | CMD_WRITE:
      SevenSegment_SetColon(rxBuffer[2]);
      break;

    // Apostrophe
    case CMD_APOSTROPHE | CMD_READ:
      txBuffer[1] = CMD_APOSTROPHE | CMD_READ;
      txBuffer[2] = SevenSegment_GetApostrophe();
      SendIRQ();
      break;

    case CMD_APOSTROPHE | CMD_WRITE:
      SevenSegment_SetApostrophe(rxBuffer[2]);
      break;
  }
}
