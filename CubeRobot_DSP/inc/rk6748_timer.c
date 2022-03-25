//-----------------------------------------------------------------------------
// \file    rk6748_timer.c
// \brief   implementation of a timer driver for tms320c6748.
//
//-----------------------------------------------------------------------------
#include "types.h"
#include "rk6748.h"

#include "rk6748_timer.h"

//-----------------------------------------------------------------------------
// Private Defines and Macros
//-----------------------------------------------------------------------------
#define TIMER_DIV       (12)
#define TICKS_PER_US    (2)


#define AUX1_TIMER_CLK 2500000

void MsDelay(int number)
{
   // stop the timer, clear int stat, and clear timer value.
   CLRBIT(TMR1->TGCR, TIM34RS);
   TMR1->TCR = 0x00000000;
   SETBIT(TMR1->INTCTLSTAT, PRDINTSTAT34);
   TMR1->TIM34 = 0x00000000;

   TMR1->PRD34 = AUX1_TIMER_CLK/1000*number;
   
   // start timer1 - 3:4 to run once up to the period.
   SETBIT(TMR1->TCR, ENAMODE34_ONETIME);
   SETBIT(TMR1->TGCR, TIM34RS);
   
   // wait for the signal that we have hit our period.
   while (!CHKBIT(TMR1->INTCTLSTAT, PRDINTSTAT34))
   {
      asm("nop");
   }
}

//

//-----------------------------------------------------------------------------
// Public Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// \brief   initialize the microsecond timer.
//
// \param   none.
//
// \return  UINT32
//    ERR_NO_ERROR - everything is ok...us timer ready to use.
//    ERR_INIT_FAIL - something happened during initialization.
//-----------------------------------------------------------------------------
UINT32 USTIMER_init(void)
{
	// configure timer 0 for free run.
	// 32-bit unchained mode, timer3:4 /12 prescaler.

	// enable muxed pins as gpio outputs and disable all related interrupts.
	// would need to also setup the pinmux register to select the gpio
	// function of these pins in order to use as gpio.
   TMR0->GPINT_GPEN = GPENO12 | GPENI12;
   TMR0->GPDATA_GPDIR = GPDIRO12 | GPDIRI12;

   // stop and reset timer.
   TMR0->TGCR = 0x00000000;
   TMR0->TCR = 0x00000000;

   // disable interrupts and set emulation to free run.
   TMR0->INTCTLSTAT = 0;
   SETBIT(TMR0->EMUMGT, SOFT | FREE);

   // config timer0 in 32-bit unchained mode.
   // remove timer0 - 3:4 from reset.
   SETBIT(TMR0->TGCR, PRESCALER(TIMER_DIV - 1) | TIMMODE_32BIT_UNCHAINED | TIM34RS );

   // init timer0 - 1:2 period....use full range of counter.
   TMR0->TIM34 = 0x00000000;
   TMR0->PRD34 = 0xFFFFFFFF;

   // start timer0 - 3:4.
   SETBIT(TMR0->TCR, ENAMODE34_CONT);

   // configure timer 1 for start/stop.
	// 32-bit unchained mode, timer3:4 /12 prescaler.

	// enable muxed pins as gpio outputs and disable all related interrupts.
	// would need to also setup the pinmux register to select the gpio
	// function of these pins in order to use as gpio.
   TMR1->GPINT_GPEN = GPENO12 | GPENI12;
   TMR1->GPDATA_GPDIR = GPDIRO12 | GPDIRI12;

   // stop and reset timer.
   TMR1->TGCR = 0x00000000;
   TMR1->TCR = 0x00000000;

   // disable interrupts and set emulation to free run.
   TMR1->INTCTLSTAT = 0;
   SETBIT(TMR1->EMUMGT, SOFT | FREE);

   // config timer1 in 32-bit unchained mode.
   SETBIT(TMR1->TGCR, PRESCALER(TIMER_DIV - 1) | TIMMODE_32BIT_UNCHAINED);

   // init timer1 - 3:4 period....0 until someone calls delay().
   TMR1->TIM34 = 0x00000000;
   TMR1->PRD34 = 0x00000000;
   
   return (ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
// \brief   halts execution for "in_delay" number of microseconds.
//
// \param   UINT32 in_delay - the number of us to delay.
//
// \return  none.
//-----------------------------------------------------------------------------
void USTIMER_delay(UINT32 in_delay)
{
   // stop the timer, clear int stat, and clear timer value.
   CLRBIT(TMR1->TGCR, TIM34RS);
   TMR1->TCR = 0x00000000;
   SETBIT(TMR1->INTCTLSTAT, PRDINTSTAT34);
   TMR1->TIM34 = 0x00000000;

   // setup compare time.
   // NOTE: not checking for possible rollover here...do not pass in a
   // value > 0x7FFFFFFF....would result in a much shorter delay than expected.
   TMR1->PRD34 = TICKS_PER_US * in_delay;
   
   // start timer1 - 3:4 to run once up to the period.
   SETBIT(TMR1->TCR, ENAMODE34_ONETIME);
   SETBIT(TMR1->TGCR, TIM34RS);
   
   // wait for the signal that we have hit our period.
   while (!CHKBIT(TMR1->INTCTLSTAT, PRDINTSTAT34))
   {
//      asm("nop");
   }
//   UINT32 i;
//   for (i = 0; i < in_delay * 1; i++) {}
}

//-----------------------------------------------------------------------------
// \brief   resets the timer to 0.
//
// \param   none.
//
// \return  none.
//-----------------------------------------------------------------------------
void USTIMER_reset(void)
{
   CLRBIT(TMR0->TGCR, TIM34RS);
   TMR0->TIM34 = 0x00000000;
   SETBIT(TMR0->TGCR, TIM34RS);
}

//-----------------------------------------------------------------------------
// \brief   returns the current timer value, in microseconds.
//
// \param   none.
//
// \return  UINT32 - timer value, in us.
//-----------------------------------------------------------------------------
//UINT32 USTIMER_get(void)
//{
//   return (TMR0->TIM34 / TICKS_PER_US);
//}

//-----------------------------------------------------------------------------
// \brief   sets the timer value, in microseconds.
//
// \param   UINT32 in_time - value to set the timer, in us.
//
// \return  none.
//-----------------------------------------------------------------------------
void USTIMER_set(UINT32 in_time)
{
   TMR0->TIM34 = TICKS_PER_US * in_time;
}
