// spi.h

#ifndef _SPI_H_
#define _SPI_H_

// Fixing an error in iostm8s003f3.h
#define SPI_CR2_CRCEN SPI_CR2_CECEN

#define GO_FRAME_PREFIX 0x2A

#define SPI_Enable() SPI_CR1_SPE = 1
#define SPI_Disable() SPI_CR1_SPE = 0

void SPI_Init();
void SPI_Reset();



#endif
