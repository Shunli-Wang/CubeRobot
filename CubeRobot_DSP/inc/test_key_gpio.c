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


void LED3_ON(void)//LED3--GP0_15
{
	GPIO_setOutput(0,15,0);
}

void LED3_OFF(void)//LED3--GP0_15 
{
	GPIO_setOutput(0,15,1);
}

void LED3_overturn( void )//LED3--GP0_15 
{
    UINT32 gpiodata;
	gpiodata=*((volatile UINT32 *)(GPIO_OUT_DATA01));
	gpiodata&=(1<<15);

	if(gpiodata>0)
		*((volatile UINT32 *)(GPIO_OUT_DATA01))&=~(UINT32)(1<<15);
	else 
		*((volatile UINT32 *)(GPIO_OUT_DATA01))|=(1<<15);
}

void LED4_ON(void)//LED4--GP6_11
{
	GPIO_setOutput(6,11,0);
}

void LED4_OFF(void)//LED4--GP6_11 
{
	GPIO_setOutput(6,11,1);
}

void LED4_overturn( void )//LED4--GP6_11
{
    UINT32 gpiodata;
	gpiodata=*((volatile UINT32 *)(GPIO_OUT_DATA67));
	gpiodata&=(1<<11);

	if(gpiodata>0)
		*((volatile UINT32 *)(GPIO_OUT_DATA67))&=~(UINT32)(1<<11);
	else 
		*((volatile UINT32 *)(GPIO_OUT_DATA67))|=(1<<11);
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
void KEY_init(void)//k1__GPIO0_0
{
	RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_GPIO, PSC_ENABLE);
	
	RK6748_pinmuxConfig(0, 0x0000000F, 0x00000008);//GP0_15
	GPIO_setDir(GPIO_BANK0,GPIO_PIN15,GPIO_OUTPUT);//GP0_15-LED3

	RK6748_pinmuxConfig(13, 0x000F0000, 0x00080000);//GP6_11
	GPIO_setDir(GPIO_BANK6,GPIO_PIN11,GPIO_OUTPUT);//GP6_11-LED4
	
	RK6748_pinmuxConfig(0, 0xf0000000, 0x80000000);//GP0_0
	GPIO_setDir(GPIO_BANK0,GPIO_PIN0,GPIO_INPUT);  //GP0_0-KEY1

	LED3_ON();
}
     
UINT8  KEY_read(void)
{   
  	UINT8 byKeyRBuff=0;	
	
	//KEY2--GP0-9
	if(!((*(volatile UINT32 *)(GPIO_IN_DATA01))&(1<<0)))
		byKeyRBuff = 0x01;
		
	return(byKeyRBuff);
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
UINT32 TEST_key_gpio(void)
{
   	printf("------------------------------------------------------------\r\n");
   	printf("              C6748 KEY_GPIO Test start...\r\n\r\n");
   
	KEY_init();
		
   	while (1)
   	{
   		if(KEY_read())
   		{
			MsDelay(100);
			if(KEY_read()) 
				LED3_overturn();
   		}
		MsDelay(50);
   	}

}

