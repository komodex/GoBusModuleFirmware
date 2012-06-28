
#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CMD_READ  (0<<7)
#define CMD_WRITE (1<<7)

#define CMD_LINE1        0x01
#define CMD_LINE2        0x02



#include "main.h"
#include "intrinsics.h"
#include "iostm8s003f3.h"
#include "spi.h"
#include "characterlcd.h"

extern u8 ModuleID[];

#define SPI_MESSAGE_LENGTH 20

// IRQ
#define IRQ_ODR PD_ODR_ODR2
#define IRQ_DDR PD_DDR_DDR2
#define IRQ_CR1 PD_CR1_C12




#endif
