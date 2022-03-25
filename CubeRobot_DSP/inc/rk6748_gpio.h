//-----------------------------------------------------------------------------
// \file    rk6748_gpio.h
// \brief   rk6748 general purpose io registers, bit definitions, and
//          function prototypes.
//
//-----------------------------------------------------------------------------


#include "types.h"

#ifndef RK6748_GPIO_H
#define RK6748_GPIO_H

//-----------------------------------------------------------------------------
// Register Structure & Defines
//-----------------------------------------------------------------------------
typedef struct
{
   volatile UINT32 DIR;
   volatile UINT32 OUT_DATA;
   volatile UINT32 SET_DATA;
   volatile UINT32 CLR_DATA;
   volatile UINT32 IN_DATA;
   volatile UINT32 SET_RIS_TRIG;
   volatile UINT32 CLR_RIS_TRIG;
   volatile UINT32 SET_FAL_TRIG;
   volatile UINT32 CLR_FAL_TRIG;
   volatile UINT32 IRQ_STAT;
} gpio_regs_t;

// define all the available gpio peripherals for the processor.
#define GPIO_BANK01              ((gpio_regs_t *)GPIO_BANK01_BASE)
#define GPIO_BANK23              ((gpio_regs_t *)GPIO_BANK23_BASE)
#define GPIO_BANK45              ((gpio_regs_t *)GPIO_BANK45_BASE)
#define GPIO_BANK67              ((gpio_regs_t *)GPIO_BANK67_BASE)
#define GPIO_BANK8_              ((gpio_regs_t *)GPIO_BANK8_BASE)

//-----------------------------------------------------------------------------
// Public Defines and Macros
//-----------------------------------------------------------------------------
#define GPIO_BANK0            (0)
#define GPIO_BANK1            (1)
#define GPIO_BANK2            (2)
#define GPIO_BANK3            (3)
#define GPIO_BANK4            (4)
#define GPIO_BANK5            (5)
#define GPIO_BANK6            (6)
#define GPIO_BANK7            (7)
#define GPIO_BANK8            (8)
#define MAX_GPIO_BANK_NUM     (9)

#define GPIO_PIN0             (0)
#define GPIO_PIN1             (1)
#define GPIO_PIN2             (2)
#define GPIO_PIN3             (3)
#define GPIO_PIN4             (4)
#define GPIO_PIN5             (5)
#define GPIO_PIN6             (6)
#define GPIO_PIN7             (7)
#define GPIO_PIN8             (8)
#define GPIO_PIN9             (9)
#define GPIO_PIN10            (10)
#define GPIO_PIN11            (11)
#define GPIO_PIN12            (12)
#define GPIO_PIN13            (13)
#define GPIO_PIN14            (14)
#define GPIO_PIN15            (15)
#define MAX_GPIO_PIN_NUM      (16)

#define GPIO_OUTPUT           (0)
#define GPIO_INPUT            (1)

#define OUTPUT_LOW            (0)
#define OUTPUT_HIGH           (1)

//-----------------------------------------------------------------------------
// Public Function Prototypes
//-----------------------------------------------------------------------------
UINT32 GPIO_setDir(UINT32 in_bank, UINT8 in_pin_num, UINT8 in_dir);
UINT32 GPIO_getInput(UINT32 in_bank, UINT8 in_pin_num, UINT8 *gpio_val);
UINT32 GPIO_setOutput(UINT32 in_bank, UINT8 in_pin_num, UINT8 in_val);

#endif
