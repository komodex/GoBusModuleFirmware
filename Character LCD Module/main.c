#include "config.h"

int main( void )
{
  // Set up the clock
  CLK_CKDIVR_CPUDIV = 0;
  CLK_CKDIVR_HSIDIV = 0;

  SPI_Init();
  SPI_Reset();

  __enable_interrupt();

  CharacterLCD_Init();

  while(1)
  {
    CharacterLCD_ProcessLoop();
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
    // Line 1
    case CMD_READ | CMD_LINE1:
      txBuffer[1] = CMD_READ | CMD_LINE1;
      CharacterLCD_GetLine1(txBuffer, 2);
      SendIRQ();
      break;

    case CMD_WRITE | CMD_LINE1:
      CharacterLCD_SetLine1(rxBuffer, 2, 16);
      break;

    // Line 2
    case CMD_READ | CMD_LINE2:
      txBuffer[1] = CMD_READ | CMD_LINE2;
      CharacterLCD_GetLine2(txBuffer, 2);
      SendIRQ();
      break;

    case CMD_WRITE | CMD_LINE2:
      CharacterLCD_SetLine2(rxBuffer, 2, 16);
      break;

  }
}
