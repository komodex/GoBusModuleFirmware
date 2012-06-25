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

void HandleMessage(u8* rxBuffer, u8* txBuffer)
{

}
