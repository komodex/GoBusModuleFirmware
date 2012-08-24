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
    // Backlight color
    case CMD_READ | CMD_COLOR:
      txBuffer[1] = CMD_READ | CMD_COLOR;
      CharacterLCD_GetColor(txBuffer, 2);
      SendIRQ();
      break;

    case CMD_WRITE | CMD_COLOR:
      CharacterLCD_SetColor(rxBuffer[2], rxBuffer[3], rxBuffer[4]);
      break;

    // Raw Commands
    case CMD_READ | CMD_RAW:
      txBuffer[1] = CMD_READ | CMD_RAW;
      CharacterLCD_GetRaw(txBuffer, 2);
      SendIRQ();
      break;

    case CMD_WRITE | CMD_RAW:
      CharacterLCD_SendRaw(rxBuffer[2], rxBuffer[3], rxBuffer[4]);
      break;

    // Line value
    case CMD_READ | CMD_LINE:
      txBuffer[0] = CMD_READ | CMD_LINE;
      txBuffer[1] = rxBuffer[2];
      CharacterLCD_GetLine(rxBuffer[2], txBuffer, 2);
      SendIRQ();
      break;

    case CMD_WRITE | CMD_LINE:
      CharacterLCD_SetLine(rxBuffer[2], rxBuffer, 3, 16);
      break;

    // Custom characters
    case CMD_READ | CMD_CUSTOMCHAR:
      txBuffer[0] = CMD_READ | CMD_CUSTOMCHAR;
      txBuffer[1] = rxBuffer[2];
      CharacterLCD_GetCustomChar(rxBuffer[2], txBuffer, 2);
      SendIRQ();
      break;

    case CMD_WRITE | CMD_CUSTOMCHAR:
      CharacterLCD_SetCustomChar(rxBuffer[2], rxBuffer, 3);
      break;

  }
}
