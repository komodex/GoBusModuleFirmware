
#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CMD_READ  (0<<7)
#define CMD_WRITE (1<<7)

#define CMD_COLOR        0x01
#define CMD_RAW          0x02
#define CMD_LINE         0x03



#include "main.h"
#include "intrinsics.h"
#include "iostm8s003f3.h"
#include "spi.h"
#include "characterlcd.h"

extern u8 ModuleID[];

#define SPI_MESSAGE_LENGTH 20

// IRQ
#define IRQ_ODR PC_ODR_ODR4
#define IRQ_DDR PC_DDR_DDR4
#define IRQ_CR1 PC_CR1_C14




#endif
