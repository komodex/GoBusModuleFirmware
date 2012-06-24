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

  CharacterLCD_SendData('H');
  CharacterLCD_SendData('e');
  CharacterLCD_SendData('l');
  CharacterLCD_SendData('l');
  CharacterLCD_SendData('o');
  CharacterLCD_SendData(' ');
  CharacterLCD_SendData('w');
  CharacterLCD_SendData('o');
  CharacterLCD_SendData('r');
  CharacterLCD_SendData('l');
  CharacterLCD_SendData('d');
  CharacterLCD_SendData('!');

  while(1)
  {
  }
}

void HandleMessage(u8* rxBuffer, u8* txBuffer)
{

}
