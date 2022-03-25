//-----------------------------------------------------------------------------
// \file    rk6748_timer.c
// \brief   implementation of a timer driver for RK6748.
//
//-----------------------------------------------------------------------------
#include "types.h"
#include "rk6748.h"

#include "rk6748_gpio.h"
#include "rk6748_timer.h"

#include <stdio.h>
#include <string.h>

void LED1_ON(void)//LED1--GP2_4      
{
	GPIO_setOutput(2,0,1);
}

void LED1_OFF(void)//LED1--GP2_4     
{
	GPIO_setOutput(2,0,0);
}

void LED2_ON(void)//LED2--GP2_8  
{
	GPIO_setOutput(2,8,1);
}

void LED2_OFF(void)//LED2--GP2_8  
{
	GPIO_setOutput(2,8,0);
}

//-----------------------------------------------------------------------------
// \brief   initialize the leds for use.
//
// \param   none.
//
// \return  UINT32
//    ERR_NO_ERROR - everything is ok...leds ready to use.
//    ERR_INIT_FAIL - something happened during initialization.
//-----------------------------------------------------------------------------
void LED_init(void)
{
	RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_GPIO, PSC_ENABLE);
	RK6748_pinmuxConfig(6, 0xf0000000, 0x80000000);//GP2_0
	RK6748_pinmuxConfig(5, 0xf0000000, 0x80000000);//GP2_8
  	GPIO_setDir(GPIO_BANK2,GPIO_PIN0,GPIO_OUTPUT);  //GP2_0-OUT -LED1
  	GPIO_setDir(GPIO_BANK2,GPIO_PIN8,GPIO_OUTPUT);  //GP2_8-OUT-LED2
	LED1_OFF();
	LED2_OFF();
}


//-----------------------------------------------------------------------------
// Static Variable Declarations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// \brief   tests the leds and pushbuttons. lights each led.
//          prints message to stdout for pushbutton changes.
//
// \param   none.
//
// \return  UINT32
//-----------------------------------------------------------------------------
UINT32 TEST_led(void)
{
	USTIMER_init();
	
   	printf("------------------------------------------------------------\r\n");
   	printf("              C6748 LED Test\r\n\r\n");
   
  	LED_init();
  
   	printf("loop forever \r\n\r\n");
   	while (1)
   	{
      	MsDelay(500);
		LED1_ON();
		MsDelay(500);
		LED1_OFF();
   	}

}
