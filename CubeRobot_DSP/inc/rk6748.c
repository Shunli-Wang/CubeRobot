//-----------------------------------------------------------------------------
// \file    rk6748.c
// \brief   implementation of initialization functions for tms320c6748.
//
//-----------------------------------------------------------------------------

#include "types.h"
#include "rk6748.h"

#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#include "stdio.h"
#endif



//-----------------------------------------------------------------------------
// Private Defines and Macros
//-----------------------------------------------------------------------------

#define PINMUX_GPIO_UI_IO_EXP_REG   (6)
#define PINMUX_GPIO_UI_IO_EXP_MASK  (0x0000000F)
#define PINMUX_GPIO_UI_IO_EXP_VAL   (0x00000008)
#define GPIO_UI_IO_EXP_BANK         (2)
#define GPIO_UI_IO_EXP_PIN          (7)



//-----------------------------------------------------------------------------
// Static Variable Declarations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------------------

static UINT32 init_clocks(void);
UINT32 init_psc(void);
void RK6748_lpscTransition(psc_regs_t *psc, UINT32 in_domain, UINT8 in_module, UINT8 in_next_state);

//-----------------------------------------------------------------------------
// Public Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// \brief   initializes psc, pll, and pinmuxes.
//
// \param   none.
//
// \return  UINT32
//    ERR_NO_ERROR - everything is ok...cpu ready to use.
//    ERR_INIT_FAIL - something happened during initialization.
//-----------------------------------------------------------------------------
UINT32 RK6748_init(void)
{
   UINT32 rtn = 0;

   // configure power, sysconifg, and clocks.
   rtn = init_psc();
//   rtn |= init_clocks();
   
   if (rtn)
      return (ERR_INIT_FAIL);
   else
      return (ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
// \brief   initializes ram on EMIFB.
//
// \param   none.
//
// \return  UINT32
//    ERR_NO_ERROR - everything is ok...ram ready to use.
//    ERR_INIT_FAIL - something happened during initialization.
//-----------------------------------------------------------------------------
UINT32 RK6748_initRAM(void)
{
   UINT32 rtn = 0;
   
   // unlock the system config registers and set the ddr 2x clock source.
   SYSCONFIG->KICKR[0] = KICK0R_UNLOCK;
   SYSCONFIG->KICKR[1] = KICK1R_UNLOCK;
   CLRBIT(SYSCONFIG->CFGCHIP[3], CLK2XSRC);
   
   // enable emif3a clock.
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_EMIF3A, PSC_ENABLE);
   
   // check if vtp calibration is enabled.
   if (CHKBIT(VTPIO_CTL, 0x00000040))
   {
      // vtp cal disabled, begin cal.

      // enable input buffer and vtp.
      SETBIT(VTPIO_CTL, 0x00004000);
      CLRBIT(VTPIO_CTL, 0x00000040);
      
      // pulse clrz to init vtp cal.
      SETBIT(VTPIO_CTL, 0x00002000);
      CLRBIT(VTPIO_CTL, 0x00002000);
      SETBIT(VTPIO_CTL, 0x00002000);
      
      // poll ready bit to wait for cal to complete.
      while (!CHKBIT(VTPIO_CTL, 0x00008000)) {}
      
      // set lock and power save bits.
      SETBIT(VTPIO_CTL, 0x00000180);
   }

   // config ddr timing.
   DDR->DDRPHYCTL1 = 0x000000C4;
   DDR->SDCR = 0x0893C622;
   DDR->SDCR &= ((DDR->SDCR & 0xFF0FFFFF) | 0x00800000);
   DDR->SDCR = ((DDR->SDCR & 0xFF0FFFFF) | 0x02000000);
   DDR->SDCR &= (~0x00008000);
   
   DDR->SDTIMR1 = 0x20923A89;
   DDR->SDTIMR2 = 0x0015C720;
   DDR->SDCR2 = 0x0;
   DDR->SDRCR = 0x00000492;
   
   // set ddr2 to sync reset.
   SETBIT(DDR->SDRCR, 0xC0000000);
   
   // sync reset the ddr clock.
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_EMIF3A, PSC_SYNCRESET);
   
   // enable the clock.
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_EMIF3A, PSC_ENABLE);
   
   // disable self refresh.
   CLRBIT(DDR->SDRCR, 0xC0000000);

   if (rtn)
      return (ERR_INIT_FAIL);
   else
      return (ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
// \brief   releases the dsp core from reset.
//
// \param   none.
//
// \return  none.
//-----------------------------------------------------------------------------
void RK6748_enableDsp(void)
{
   // power dsp core.
   RK6748_lpscTransition(PSC0, DOMAIN0, LPSC_DSP, PSC_ENABLE);

   // wake up dsp core and release from reset.
   SETBIT(PSC0->MDCTL[LPSC_DSP], LRST);
}

//-----------------------------------------------------------------------------
// \brief   configures the desired pin mux register.
//
// \param   UINT32 in_reg - pin mux register to be configured.
//
// \param   UINT32 in_mask - bits to be set in pin mux register.
//
// \param   UINT32 in_val - value to set the pin mux register.
//
// \return  none.
//-----------------------------------------------------------------------------
void RK6748_pinmuxConfig(UINT32 in_reg, UINT32 in_mask, UINT32 in_val)
{
   // unlock the system config registers.
   SYSCONFIG->KICKR[0] = KICK0R_UNLOCK;
   SYSCONFIG->KICKR[1] = KICK1R_UNLOCK;
   
   // make sure the pinmux register is cleared for the mask bits before
   // setting the value.
   CLRBIT(SYSCONFIG->PINMUX[in_reg], in_mask);
   SETBIT(SYSCONFIG->PINMUX[in_reg], in_val);
   
   // lock the system config registers.
   SYSCONFIG->KICKR[0] = KICK0R_LOCK;
   SYSCONFIG->KICKR[1] = KICK1R_LOCK;
}

//-----------------------------------------------------------------------------
// \brief   transitions a local psc module to a new state.
//
// \param   psc_regs_t *psc - psc register that contains the local module.
//
// \param   UINT32 in_domain - input power domain (always on / internal).
//
// \param   UINT8 in_module - module to be set.
//
// \param   UINT8 in_next_state - next state for the local module.
//
// \return  none.
//-----------------------------------------------------------------------------
void RK6748_lpscTransition(psc_regs_t *psc, UINT32 in_domain, UINT8 in_module, UINT8 in_next_state)
{
   // spin until existing transitions are done.
   while (CHKBIT(psc->PTSTAT, in_domain)) {}

   // if we are already in the requested state...just return.
   if (CHKBIT(psc->MDSTAT[in_module], MASK_STATE) == in_next_state)
   {
      return;
   }

   // setup the transition...clear the bits before setting the next state.
   CLRBIT(psc->MDCTL[in_module], NEXT);
   SETBIT(psc->MDCTL[in_module], in_next_state);

   // kick off the transition.
   SETBIT(psc->PTCMD, in_domain);

   // spin until transition is done.
   while (CHKBIT(psc->PTSTAT, in_domain)) {}

   while (CHKBIT(psc->MDSTAT[in_module], MASK_STATE) != in_next_state) {}
}

void RK6748_configCache(void)
{
  CSL_CacheRegsOvly cacheRegs = (CSL_CacheRegsOvly)CSL_CACHE_0_REGS;
  volatile unsigned int stall;

  // The below writes to the CFG registers are followed by a dummy read.  Mode
  // switches require that a read is performed immediately after the write.  The
  // read stalls the cpu to ensure the mode change completes.

  // Set L1P size to 32K
  cacheRegs->L1PCFG=0x00000004u;//,CACHE_L1PCFG_MODE,32K);
  stall = cacheRegs->L1PCFG;

  // Set L1D size to 32K
 // CSL_FINST(cacheRegs->L1DCFG,CACHE_L1DCFG_MODE,32K);
  cacheRegs->L1DCFG=0x00000003u;
  stall = cacheRegs->L1DCFG;

  // Set L2 size to 64k and normal opperation
  cacheRegs->L2CFG =0x00000001u;//CSL_FMKT(CACHE_L2CFG_MODE,64K)
                  // | CSL_FMKT(CACHE_L2CFG_L2CC,NORMAL);
  stall = cacheRegs->L2CFG;

  // The MAR registers set the cachability of memory spaces external to the
  // megamodule.  Below is an example of turning on cachability for two ranges.
  // Reference spru871H for a complete list the MAR ranges.

  // Set MAR[192] range 0xC0000000-0xC0FFFFFF as cacheable
  //CSL_FINST(cacheRegs->MAR[192],CACHE_MAR_PC,CACHEABLE);
  cacheRegs->MAR[194]=0x00000001u;

}

//-----------------------------------------------------------------------------
// helper function to initialize power and sleep config module.
//-----------------------------------------------------------------------------
UINT32 init_psc(void)
{
   //-----------------------------------------
   // PSC0, domain 0 - all modules, always on.
   //-----------------------------------------

   // configure the next state for psc0 modules.
   
   RK6748_lpscTransition(PSC0, DOMAIN0, LPSC_EMIFA, PSC_ENABLE);
   RK6748_lpscTransition(PSC0, DOMAIN0, LPSC_SPI0, PSC_ENABLE);
   RK6748_lpscTransition(PSC0, DOMAIN0, LPSC_MMCSD0, PSC_ENABLE); 
   RK6748_lpscTransition(PSC0, DOMAIN0, LPSC_AINTC, PSC_ENABLE);
   RK6748_lpscTransition(PSC0, DOMAIN0, LPSC_UART0, PSC_ENABLE);
   RK6748_lpscTransition(PSC0, DOMAIN0, LPSC_SCR0, PSC_ENABLE);
   RK6748_lpscTransition(PSC0, DOMAIN0, LPSC_SCR1, PSC_ENABLE);
   RK6748_lpscTransition(PSC0, DOMAIN0, LPSC_SCR2, PSC_ENABLE);

   //-----------------------------------------
   // PSC1, domain 0 - all modules, always on.
   //-----------------------------------------

   // configure the next state for psc1 modules.
   
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_USB0, PSC_ENABLE); 
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_USB1, PSC_ENABLE); 
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_GPIO, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_HPI, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_EMAC, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_DDR2, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_MCASP0, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_SATA, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_VPIF, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_SPI1, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_I2C1, PSC_ENABLE); 
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_UART1, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_UART2, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_MCBSP0, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_MCBSP1, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_LCDC, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_PWM, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_MMCSD1, PSC_ENABLE); 
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_RPI, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_ECAP, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_SCR8, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_SCR7, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_SCR12, PSC_ENABLE);
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_SHRAM, PSC_ENABLE);
   
   return (ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
// helper function to initialize cpu, system, and pheripheral clocks.
// configure arm and dsp to 300 MHz and emif to 133MHz.
//-----------------------------------------------------------------------------
UINT32 init_clocks(void)
{
   UINT32 rtn=0;
   
   // unlock the system config registers.
   SYSCONFIG->KICKR[0] = KICK0R_UNLOCK;
   SYSCONFIG->KICKR[1] = KICK1R_UNLOCK;
   
  // rtn = config_pll0(0,24,1,0,1,11,5);
  // rtn |= config_pll1(24,1,0,1,2);

   // enable 4.5 divider PLL and set it as the EMIFA clock source.
//    SETBIT(SYSCONFIG->CFGCHIP[3], DIV4P5ENA | EMA_CLKSRC);
   
   return (rtn);
}

#if 0
UINT32 config_pll0(UINT32 clkmode, UINT32 pllm, UINT32 postdiv, UINT32 plldiv1, UINT32 plldiv2, UINT32 plldiv3, UINT32 plldiv7)
{
   UINT32 i;
   
   // unlock the system config registers.
   SYSCONFIG->KICKR[0] = KICK0R_UNLOCK;
	SYSCONFIG->KICKR[1] = KICK1R_UNLOCK;

   // unlock pll regs.
   CLRBIT(SYSCONFIG->CFGCHIP[0], PLL0_MASTER_LOCK);
   
   // prepare to enable pll (PLLENSRC must be clear for PLLEN to have effect).
   CLRBIT(PLL0->PLLCTL, PLLENSRC);
   
   // disable external clock source.
   CLRBIT(PLL0->PLLCTL, EXTCLKSRC);
   
   // switch to bypass mode...wait 4 cycles to ensure it switches properly.
   CLRBIT(PLL0->PLLCTL, PLLEN);
   for (i = 0; i < 4; i++) {}
   
   // select clock mode (on-chip oscillator or external).
	CLRBIT(PLL0->PLLCTL, CLKMODE);
	SETBIT(PLL0->PLLCTL, (clkmode << CLKMODE_SHIFT));
   
   // reset the pll.
   CLRBIT(PLL0->PLLCTL, PLLRST);
   
   // disable the pll...set disable bit.
   SETBIT(PLL0->PLLCTL, PLLDIS);
   
   // PLL initialization sequence
   //----------------------------
   // power up the pll...clear power down bit.
   CLRBIT(PLL0->PLLCTL, PLLPWRDN);   
   
   // enable the pll...clear disable bit.
   CLRBIT(PLL0->PLLCTL, PLLDIS);
   
   /*PLL stabilisation time- take out this step , not required here when PLL in bypassmode*/
   for(i = 0; i < PLL_STABILIZATION_TIME; i++) {;}
   
   // program the required multiplier value.
   PLL0->PLLM = pllm;
   
   // program postdiv ratio.
   PLL0->POSTDIV = DIV_ENABLE | postdiv;
   
   // spin until all transitions are complete.
   while (CHKBIT(PLL0->PLLSTAT, GOSTAT)) {}
   
   // program the divisors.
   PLL0->PLLDIV1 = DIV_ENABLE | plldiv1;
   PLL0->PLLDIV2 = DIV_ENABLE | plldiv2;
   PLL0->PLLDIV3 = DIV_ENABLE | plldiv3;
   PLL0->PLLDIV4 = DIV_ENABLE | (((plldiv1 + 1) * 4) - 1);
   PLL0->PLLDIV6 = DIV_ENABLE | plldiv1;
   PLL0->PLLDIV7 = DIV_ENABLE | plldiv7;
   
   // kick off the transitions and spin until they are complete.
   SETBIT(PLL0->PLLCMD, GOSET);
   while (CHKBIT(PLL0->PLLSTAT, GOSTAT)) {}
   
   /*Wait for PLL to reset properly. See PLL spec for PLL reset time - This step is not required here -step11*/
   for(i = 0; i < PLL_RESET_TIME_CNT; i++) {;}   /*128 MXI Cycles*/
   
   // bring pll out of reset and wait for pll to lock.
   SETBIT(PLL0->PLLCTL, PLLRST);
   for (i = 0; i < PLL_LOCK_CYCLES; i++) {}
   
   // exit bypass mode.
   SETBIT(PLL0->PLLCTL, PLLEN);
   
   // lock pll regs.
   SETBIT(SYSCONFIG->CFGCHIP[0], PLL0_MASTER_LOCK);
   
   return (ERR_NO_ERROR);
}

UINT32 config_pll1(UINT32 pllm, UINT32 postdiv, UINT32 plldiv1, UINT32 plldiv2, UINT32 plldiv3)
{
   UINT32 i;
   
   // unlock the system config registers.
   SYSCONFIG->KICKR[0] = KICK0R_UNLOCK;
	SYSCONFIG->KICKR[1] = KICK1R_UNLOCK;
   
   // unlock pll regs.
   CLRBIT(SYSCONFIG->CFGCHIP[3], PLL1_MASTER_LOCK);
   
   // prepare to enable pll (PLLENSRC must be clear for PLLEN to have effect).
   CLRBIT(PLL1->PLLCTL, PLLENSRC);
   CLRBIT(PLL1->PLLCTL, EXTCLKSRC);
   
   // switch to bypass mode...wait 4 cycles to ensure it switches properly.
   CLRBIT(PLL1->PLLCTL, PLLEN);
   for (i = 0; i < 4; i++) {}
   
   // reset the pll.
   CLRBIT(PLL1->PLLCTL, PLLRST);
   
   // disable the pll...set disable bit.
   SETBIT(PLL1->PLLCTL, PLLDIS);
   
   // PLL initialization sequence
   //----------------------------
   // power up the pll...clear power down bit.
   CLRBIT(PLL1->PLLCTL, PLLPWRDN);
   
   // enable the pll...clear disable bit.
   CLRBIT(PLL1->PLLCTL, PLLDIS);
   
   /*PLL stabilisation time- take out this step , not required here when PLL in bypassmode*/
   for(i = 0; i < PLL_STABILIZATION_TIME; i++) {;}
   
	PLL1->OCSEL=0x14;		//************************************************************
	PLL1->OSCDIV=(1<<15);	//************************************************************
   
   // program the required multiplier value.
   PLL1->PLLM = pllm;
   
   // program postdiv ratio.
   PLL1->POSTDIV = DIV_ENABLE | postdiv;
   
   // spin until all transitions are complete.
   while (CHKBIT(PLL1->PLLSTAT, GOSTAT)) {}
   
   // program the divisors.
   PLL1->PLLDIV1 = DIV_ENABLE | plldiv1;
   PLL1->PLLDIV2 = DIV_ENABLE | plldiv2;
   PLL1->PLLDIV3 = DIV_ENABLE | plldiv3;
   
   // kick off the transitions and spin until they are complete.
   SETBIT(PLL1->PLLCMD, GOSET);
   while (CHKBIT(PLL1->PLLSTAT, GOSTAT)) {}
   
   /*Wait for PLL to reset properly. See PLL spec for PLL reset time - This step is not required here -step11*/
   for(i = 0; i < PLL_RESET_TIME_CNT; i++) {;}
   
   // bring pll out of reset and wait for pll to lock.
   SETBIT(PLL1->PLLCTL, PLLRST);
   for (i = 0; i < PLL_LOCK_CYCLES; i++) {}
   
   // exit bypass mode.
   SETBIT(PLL1->PLLCTL, PLLEN);
   
   // lock pll regs.
   SETBIT(SYSCONFIG->CFGCHIP[3], PLL1_MASTER_LOCK);
   
   return (ERR_NO_ERROR);
}

#endif

//-----------------------------------------------------------------------------
// prints a chunk of flash data in a readable format.
//-----------------------------------------------------------------------------

void UTIL_printMem(UINT32 begin_addr, UINT8 *buffer, UINT32 length, UINT8 continuation)
{
#define BYTES_PER_LINE  16
   UINT32 i, j, line_end;

   if (!continuation)
   {
      printf("\r\n\r\nPrint Data\r\n");
      printf("----------\r\n");

      // print idices across the top.
      printf("address     ");
      for (i = 0; i < BYTES_PER_LINE; i++)
      {
         printf("%02X ", i);
      }
      printf("\r\n");
   }

   // print data.
   for (i = 0; i < length; i += BYTES_PER_LINE)
   {
      if (length > (i + BYTES_PER_LINE))
      {
         line_end = (i + BYTES_PER_LINE);
      }
      else
      {
         line_end = length;
      }

      printf("\n%08X    ", (begin_addr + i));
      for (j = i; j < line_end; j++)
         printf("%02X ", buffer[j]);
   }

   printf("\r\n");
}


void DumpBuffer(UINT8 *data, UINT32 len)
{
	int i;
	UINT8 printfbuf[100];
	for (i=0;i<len;i++)
	{
		if ((i%16) ==  0)
		{
			sprintf(printfbuf,"\r\n%04x:  ", i);
			DebugPrintf(printfbuf);

		//	DebugPrintf("\n");
	
		//	printf("%04x:  ", i);
			
		}
		sprintf(printfbuf,"%02x ", data[i]);
		DebugPrintf(printfbuf);
	}
	DebugPrintf("\n\n");
}


