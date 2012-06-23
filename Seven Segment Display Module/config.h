
#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CMD_READ  (0<<7)
#define CMD_WRITE (1<<7)

#define CMD_DISPLAYVALUE 0x01
#define CMD_BRIGHTNESS   0x02
#define CMD_COLON        0x03
#define CMD_APOSTROPHE   0x04



#include "main.h"
#include "intrinsics.h"
#include "iostm8s003f3.h"
#include "spi.h"
#include "sevensegment.h"

extern u8 ModuleID[];

// IRQ
#define IRQ_ODR PD_ODR_ODR2
#define IRQ_DDR PD_DDR_DDR2
#define IRQ_CR1 PD_CR1_C12




#endif
