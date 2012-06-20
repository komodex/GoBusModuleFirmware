
#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CMD_READ  (0<<7)
#define CMD_WRITE (1<<7)

#define CMD_DISPLAYVALUE 0x01
#define CMD_BRIGHTNESS   0x02
#define CMD_COLON        0x03
#define CMD_APOSTROPHE   0x04


typedef unsigned char u8;
typedef unsigned short u16;

#include "intrinsics.h"
#include "iostm8s003f3.h"
#include "spi.h"
#include "sevensegment.h"

extern u8 ModuleID[];

// IRQ
#define IRQ_ODR PD_ODR_ODR2
#define IRQ_DDR PD_DDR_DDR2
#define IRQ_CR1 PD_CR1_C12


/////////////////////////////////////////////////////////////////////////////
// Interrupt Vectors

//      RESET_IRQ                   (-2 + 2)  // Reset
#define TRAP_IRQ                    (-1 + 2)  // Software Interrupt
#define TLI_IRQ                     ( 0 + 2)  // External Top Level Interrupt
#define AWU_IRQ                     ( 1 + 2)  // Auto Wake Up from Halt
#define CLK_IRQ                     ( 2 + 2)  // Clock Controller
#define EXTI0_IRQ                   ( 3 + 2)  // Port A External Interrupts
#define EXTI1_IRQ                   ( 4 + 2)  // Port B External Interrupts
#define EXTI2_IRQ                   ( 5 + 2)  // Port C External Interrupts
#define EXTI3_IRQ                   ( 6 + 2)  // Port D External Interrupts
#define EXTI4_IRQ                   ( 7 + 2)  // Port E External Interrupts
// Reserved                         ( 8 + 2)
// Reserved                         ( 9 + 2)
#define SPI_IRQ                     (10 + 2)  // SPI End of Transfer
#define TIM1_UPD_OVF_TRG_BRK_IRQ    (11 + 2)  // TIM1 Update/Overflow/Trigger/Break
#define TIM1_CAP_COM_IRQ            (12 + 2)  // TIM1 Capture/Compare
#define TIM2_UPD_OVF_IRQ            (13 + 2)  // TIM2 Update/Overflow
#define TIM2_CAP_COM_IRQ            (14 + 2)  // TIM2 Capture/Compare
// Reserved                         (15 + 2)
// Reserved                         (16 + 2)
#define UART1_TX_IRQ                (17 + 2)  // UART1 Transmitter Interrupts
#define UART1_RX_IRQ                (18 + 2)  // UART1 Receiver Interrupts
#define I2C_IRQ                     (19 + 2)  // I2C Interrupt
// Reserved                         (20 + 2)
// Reserved                         (21 + 2)
#define ADC1_IRQ                    (22 + 2)  // ADC1 End of Conversion/Analog Watchdog
#define TIM4_UPD_OVF_IRQ            (23 + 2)  // TIM4 Update/Overflow
#define EEPROM_EOP_WR_PG_DIS_IRQ    (24 + 2)  // Flash End of Programming/Write Protected Page

// Interrupt Handler
//
// Usage: INTERRUPT_HANDLER(EXTI0_IRQ)
//
#define __PRAGMA(x) _Pragma(#x)

#define INTERRUPT_HANDLER(irq)  \
  __PRAGMA(vector = irq)        \
  __interrupt void (irq##_Handler)(void)

/////////////////////////////////////////////////////////////////////////////

#endif
