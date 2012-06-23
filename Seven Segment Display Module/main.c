#include "config.h"

int main( void )
{
  // Set up the clock
  CLK_CKDIVR_CPUDIV = 0;
  CLK_CKDIVR_HSIDIV = 0;

  SPI_Init();
  SPI_Reset();

  __enable_interrupt();

  SevenSegment_Init();

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
