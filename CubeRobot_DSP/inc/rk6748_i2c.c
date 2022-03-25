//-----------------------------------------------------------------------------
// \file    evmc6748_i2c.c
// \brief   implementation of a i2c driver for C6748.
//
//-----------------------------------------------------------------------------

#include "stdio.h"
#include "types.h"
#include "rk6748.h"
#include "rk6748_timer.h"
#include "rk6748_i2c.h"

//-----------------------------------------------------------------------------
// Private Defines and Macros
//-----------------------------------------------------------------------------

// pinmux defines.
#define PINMUX_I2C0_REG       (4)
#define PINMUX_I2C0_MASK      (0x0000FF00)
#define PINMUX_I2C0_VAL       (0x00002200)
#define PINMUX_I2C1_REG       (4)
#define PINMUX_I2C1_MASK      (0x00FF0000)
#define PINMUX_I2C1_VAL       (0x00440000)
// i2c bus timeout.
#define I2C_TIMEOUT           (500000)

//-----------------------------------------------------------------------------
// Static Variable Declarations
//-----------------------------------------------------------------------------
// maintain the clock rate set during init.
static i2c_clk_e g_clock_rate;

//-----------------------------------------------------------------------------
// Public Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// \brief   initialize the given i2c port.
//
// \param   i2c_regs_t *i2c - pointer to reg struct for the desired i2c port.
//
// \param   i2c_clk_e in_clock_rate - desired clock rate.
//
// \return  UINT32
//    ERR_NO_ERROR - everything is ok...i2c ready to use.
//    ERR_INIT_FAIL - something happened during initialization.
//-----------------------------------------------------------------------------
UINT32 I2C_init(i2c_regs_t *i2c, i2c_clk_e in_clock_rate)
{
   // set the pinmux for the given i2c port.
   switch ((UINT32)i2c)
   {
      case I2C0_REG_BASE:
         RK6748_pinmuxConfig(PINMUX_I2C0_REG, PINMUX_I2C0_MASK, PINMUX_I2C0_VAL);
         break;

      case I2C1_REG_BASE:
         RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_I2C1, PSC_ENABLE);
         RK6748_pinmuxConfig(PINMUX_I2C1_REG, PINMUX_I2C1_MASK, PINMUX_I2C1_VAL);
         break;

      default:
         return (ERR_INIT_FAIL);
   }
   
   // set global clock rate for future use.
   g_clock_rate = in_clock_rate;

   // put i2c in reset.
   i2c->ICMDR = 0;
   
   // configure clocks.
   // set prescaler for ~8MHz interal i2c clock.
   i2c->ICPSC = 2;
   
   switch (in_clock_rate)
   {
      // set prescaler and clock dividers to precomputed values for
      // input clock rate.
      case I2C_CLK_100K:
         i2c->ICCLKL = 35;
         i2c->ICCLKH = 35;
         break;
      
      case I2C_CLK_400K:
         i2c->ICCLKL = 5;
         i2c->ICCLKH = 5;
         break;
   }
   
   // release i2c from reset.
   SETBIT(i2c->ICMDR, IRS);

   return (ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
// \brief   read data from i2c bus.
//
// \param   i2c_regs_t *i2c - pointer to reg struct for the desired i2c port.
//
// \param   UINT16 in_addr - i2c address to read from.
//
// \param   UINT8 *dest_buffer - pointer to memory to copy the data being received.
//
// \param   UINT16 in_length - number of bytes to receive.
//
// \return  UINT32
//    ERR_NO_ERROR - input in bounds, data received.
//    ERR_INVALID_PARAMETER - null pointers.
//-----------------------------------------------------------------------------
UINT32 I2C_read(i2c_regs_t *i2c, UINT16 in_addr, UINT8 *dest_buffer, UINT16 in_length, UINT8 chk_busy)
{
   UINT32 rtn = ERR_INVALID_PARAMETER;

   if ((i2c != NULL) && (dest_buffer != NULL))
   {
      UINT32 cnt = 0;
      UINT16 i;

      // wait for bus to be clear...we may want to skip this depending on which
      // device we are talking to. see device datasheets for more info.
      USTIMER_delay(1000);
      if (chk_busy)
         while (CHKBIT(i2c->ICSTR, BB)) {}

      // set byte count and slave address.
      i2c->ICCNT = in_length;
      i2c->ICSAR = in_addr;

      // configure i2c for master receive mode and release from reset.
      i2c->ICMDR = STT | MST | ICMDR_FREE | IRS;

      // receive data one byte at a time.
      for (i = 0; i < in_length; i++)
      {
         // do not want to send an ack on last byte.
         if (i == (in_length - 1))
         {
            SETBIT(i2c->ICMDR, NACKMOD);
         }

         // wait for data to be received.
         cnt = 0;
         do
         {
            if (cnt++ > I2C_TIMEOUT)
            {
               // timed out waiting for data...reinit and return error.
               I2C_init(i2c, g_clock_rate);
               return (ERR_TIMEOUT);
            }
         } while (!CHKBIT(i2c->ICSTR, ICRRDY));

         dest_buffer[i] = i2c->ICDRR;
      }

      // send stop condition.
      SETBIT(i2c->ICMDR, STP);

      rtn = ERR_NO_ERROR;
   }

   return (rtn);
}

//-----------------------------------------------------------------------------
// \brief   write data onto i2c bus.
//
// \param   i2c_regs_t *i2c - pointer to reg struct for the desired i2c port.
//
// \param   UINT16 in_addr - i2c address to write to.
//
// \param   UINT8 *src_buffer - pointer to the data to write.
//
// \param   UINT16 in_length - number of bytes to transmit.
//
// \return  UINT32
//    ERR_NO_ERROR - input in bounds, data transmitted.
//    ERR_INVALID_PARAMETER - null pointers.
//-----------------------------------------------------------------------------
UINT32 I2C_write(i2c_regs_t *i2c, UINT16 in_addr, UINT8 *src_buffer, UINT16 in_length, UINT8 set_stop)
{
   UINT32 rtn = ERR_INVALID_PARAMETER;

   if ((i2c != NULL) && (src_buffer != NULL))
   {
      UINT32 cnt = 0;
      UINT16 i;

      // wait for bus to be clear.
      USTIMER_delay(1000);
      while (CHKBIT(i2c->ICSTR, BB)) {}

      // set byte count and slave address.
      i2c->ICCNT = in_length;
      i2c->ICSAR = in_addr;

      // configure i2c for master transmit mode and release from reset.
      i2c->ICMDR = STT | MST | ICMDR_FREE | TRX | IRS;

      USTIMER_delay(10);

      // transmit data one byte at a time.
      for (i = 0; i < in_length; i++)
      {
         i2c->ICDXR = src_buffer[i];

         // wait for data to be copied to shift register.
         cnt = 0;
         do
         {
            if (cnt++ > I2C_TIMEOUT)
            {
               // timed out waiting for data...reinit and return error.
               I2C_init(i2c, g_clock_rate);
               return (ERR_TIMEOUT);
            }
         } while (!CHKBIT(i2c->ICSTR, ICXRDY));
      }

      // send stop condition...we may want to skip this depending on which
      // device we are talking to. see device datasheets for more info.
      if (set_stop)
         SETBIT(i2c->ICMDR, STP);

      rtn = ERR_NO_ERROR;
   }

   return (rtn);
}

