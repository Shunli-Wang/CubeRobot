//-----------------------------------------------------------------------------
// \file    rk6748_gpio.c
// \brief   implementation of the gpio driver for the tms320c6748.
//
//-----------------------------------------------------------------------------

#include "types.h"
#include "rk6748.h"


#include "rk6748_gpio.h"

//-----------------------------------------------------------------------------
// Private Defines and Macros
//-----------------------------------------------------------------------------
#define GPIO_ODD_BANK_PIN_ADDER     (16)

//-----------------------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------------------
static gpio_regs_t * getRegisterBankAndBit(UINT32 in_bank, UINT8 in_pin_num, UINT32 *reg_bit);


//-----------------------------------------------------------------------------
// Global Variable Initializations
//-----------------------------------------------------------------------------
const UINT32 bitval_u32[32] =
{
   0x00000001, 0x00000002, 0x00000004, 0x00000008,
   0x00000010, 0x00000020, 0x00000040, 0x00000080,
   0x00000100, 0x00000200, 0x00000400, 0x00000800,
   0x00001000, 0x00002000, 0x00004000, 0x00008000,
   0x00010000, 0x00020000, 0x00040000, 0x00080000,
   0x00100000, 0x00200000, 0x00400000, 0x00800000,
   0x01000000, 0x02000000, 0x04000000, 0x08000000,
   0x10000000, 0x20000000, 0x40000000, 0x80000000
};


//-----------------------------------------------------------------------------
// Public Function Definitions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// \brief   sets the direction (input/output) of the given gpio pin.
//
// \param   UINT32 in_bank - gpio bank for desired pin.
//
// \param   UINT8 in_pin_num - gpio pin within bank to be set.
//
// \param   UINT8 in_dir - input or output.
//
// \return  UINT32
//    ERR_NO_ERROR - input in bounds, gpio direction set.
//    ERR_INVALID_PARAMETER - input out of bounds.
//-----------------------------------------------------------------------------
UINT32 GPIO_setDir(UINT32 in_bank, UINT8 in_pin_num, UINT8 in_dir)
{
   UINT32 rtn = ERR_INVALID_PARAMETER;

   if ((in_bank < MAX_GPIO_BANK_NUM) && (in_pin_num < MAX_GPIO_PIN_NUM))
   {
      gpio_regs_t *gpio_bank;
      UINT32 gpio_bit;

      // get the register bank and bitmask for the input bank and pin.
      gpio_bank = getRegisterBankAndBit(in_bank, in_pin_num, &gpio_bit);

      if (GPIO_OUTPUT == in_dir)
      {
         // clear the bit to config pin for output.
         CLRBIT(gpio_bank->DIR, gpio_bit);
      }
      else
      {
         // set the bit to config pin for input.
         SETBIT(gpio_bank->DIR, gpio_bit);
      }
      
      rtn = ERR_NO_ERROR;
   }
   
   return (rtn);
}

//-----------------------------------------------------------------------------
// \brief   returns the current input of the given gpio pin.
//
// \param   UINT32 in_bank - gpio bank for desired pin.
//
// \param   UINT8 in_pin_num - gpio pin within bank to get input.
//
// \param   UINT8 *gpio_val - gpio pin data
//                      0 - pin is cleared.
//                      1 - pin is set.
//
// \return  UINT32
//    ERR_NO_ERROR - input in bounds, data returned in gpio_val.
//    ERR_INVALID_PARAMETER - input out of bounds.
//-----------------------------------------------------------------------------
UINT32 GPIO_getInput(UINT32 in_bank, UINT8 in_pin_num, UINT8 *gpio_val)
{
   UINT32 rtn = ERR_INVALID_PARAMETER;

   if ((in_bank < MAX_GPIO_BANK_NUM) && (in_pin_num < MAX_GPIO_PIN_NUM))
   {
      gpio_regs_t *gpio_bank;
      UINT32 gpio_bit;

      // get the register bank and bitmask for the input bank and pin.
      gpio_bank = getRegisterBankAndBit(in_bank, in_pin_num, &gpio_bit);

      if (CHKBIT(gpio_bank->IN_DATA, gpio_bit))
      {
         // in data is set, return 1.
         *gpio_val = 1;
      }
      else
      {
         // in data is clear, return 0.
         *gpio_val = 0;
      }
      
      rtn = ERR_NO_ERROR;
   }

   return (rtn);
}

//-----------------------------------------------------------------------------
// \brief   sets the given gpio pin output.
//
// \param   UINT32 in_bank - gpio bank for desired pin.
//
// \param   UINT8 in_pin_num - gpio pin within bank to be set.
//
// \param   UINT8 in_val - 0/1 to set or clear the pin.
//
// \return  UINT32
//    ERR_NO_ERROR - input in bounds, gpio pin set.
//    ERR_INVALID_PARAMETER - input out of bounds.
//-----------------------------------------------------------------------------
UINT32 GPIO_setOutput(UINT32 in_bank, UINT8 in_pin_num, UINT8 in_val)
{
   UINT32 rtn = ERR_INVALID_PARAMETER;

   if ((in_bank < MAX_GPIO_BANK_NUM) && (in_pin_num < MAX_GPIO_PIN_NUM))
   {
      gpio_regs_t *gpio_bank;
      UINT32 gpio_bit;

      // get the register bank and bitmask for the input bank and pin.
      gpio_bank = getRegisterBankAndBit(in_bank, in_pin_num, &gpio_bit);

      if (in_val)
         SETBIT(gpio_bank->OUT_DATA, gpio_bit);
      else
         CLRBIT(gpio_bank->OUT_DATA, gpio_bit);

      rtn = ERR_NO_ERROR;
   }
   
   return (rtn);
}


//-----------------------------------------------------------------------------
// Private Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// converts a bank (0-8) / pin (0-15) to a register bank (0-3) and bit (0-31).
//-----------------------------------------------------------------------------
static gpio_regs_t * getRegisterBankAndBit(UINT32 in_bank, UINT8 in_pin_num, UINT32 *reg_bit)
{
   gpio_regs_t *rtn;

   switch (in_bank)
   {
      case GPIO_BANK0:
         rtn = GPIO_BANK01;
         break;

      case GPIO_BANK1:
         rtn = GPIO_BANK01;
         in_pin_num += GPIO_ODD_BANK_PIN_ADDER;
         break;
      
      case GPIO_BANK2:
         rtn = GPIO_BANK23;
         break;
         
      case GPIO_BANK3:
         rtn = GPIO_BANK23;
         in_pin_num += GPIO_ODD_BANK_PIN_ADDER;
         break;
      
      case GPIO_BANK4:
         rtn = GPIO_BANK45;
         break;
         
      case GPIO_BANK5:
         rtn = GPIO_BANK45;
         in_pin_num += GPIO_ODD_BANK_PIN_ADDER;
         break;
      
      case GPIO_BANK6:
         rtn = GPIO_BANK67;
         break;
         
      case GPIO_BANK7:
         rtn = GPIO_BANK67;
         in_pin_num += GPIO_ODD_BANK_PIN_ADDER;
         break;

      case GPIO_BANK8:
         rtn = GPIO_BANK8_;
         break;
   }
   
   *reg_bit = bitval_u32[in_pin_num];

   return (rtn);
}



