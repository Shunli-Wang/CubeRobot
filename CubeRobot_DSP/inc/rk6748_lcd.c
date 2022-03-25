
#include "types.h"
#include "rk6748.h"
#include "rk6748_lcd.h"

#include <stdio.h>
#include <string.h>

#define FRAMEBUF_BASE               0xc1f00000

// =========================================================================
// Function: Complete the init of the hardware.
// Params: vaddr (addr of the display flash.)
// Return: Null
// =========================================================================
void RK6748_lcdInit (void)
{
		UINT32 reg;
		UINT16 *pdata;	
		UINT32 i;

		UINT32 *pbbpr;	
		pbbpr=(UINT32 *)0xb0000020;
		*pbbpr=0x10;
			

		/* Palette */
		pdata = (UINT16 *)FRAMEBUF_BASE;
		
		*pdata++ = 0x4000;
		for (i = 0; i < 15; i++)
		*pdata++ = 0x0000;

		RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_LCDC, PSC_ENABLE); // Enable
		MsDelay(5);
		//lcd2-7 
		RK6748_pinmuxConfig(16, 0xFFFFFF00, 0x22222200);
		//lcd0 1 10-15
		RK6748_pinmuxConfig(17, 0xFFFFFFFF, 0x22222222);
		//lcd8 9
		RK6748_pinmuxConfig(18, 0x000000FF, 0x00000022);
		//lcd_PCLK	MCLI
		RK6748_pinmuxConfig(18, 0xFF000000, 0x22000000);	
		//lcd_cs  VSYN	HSYN
		RK6748_pinmuxConfig(19, 0x0F0000FF, 0x02000022);

		//Lcd_BK
		RK6748_pinmuxConfig(18, 0xF0000000, 0x80000000);
		GPIO_setDir(8,10,0);//output
		GPIO_setOutput(8,10,1);
	
		g_ptSysconfig0Reg->MSTPRI[2] &= 0x0fffffff; // Highest priority
		MsDelay(5);
		g_ptSysconfig0Reg->MSTPRI[2] |= 0x10000000; // Highest priority
		// Turn raster controller off
	
		g_ptLcdcReg->RASTER_CTRL		&= 0xfffffffe;		   // Turn raster controller off
		MsDelay(5);
		g_ptLcdcReg->LCD_STAT  = 0x000003ff;	// Clear status bits
		g_ptLcdcReg->LCD_CTRL  = 0x00000601;   // PCLK = 150MHz / 17 = 8.824 MHz, raster mode
		g_ptLcdcReg->RASTER_TIMING_0  = (134<<24)+((16)<<16)+((10)<<10)+(39<<4); // HBP = 0x01; HFP = 0x02; HSW = 0x29(41); PPL = 0x1D???a0x13(19)
		g_ptLcdcReg->RASTER_TIMING_1  = ((11)<<24)+((32)<<16)+((2)<<10)+(LCD_SIZE_Y-1); // VBP = 0x3; VFP = 0x2; VSW = 0xA: LPP = 0x10F(271)???aEF(239);
		g_ptLcdcReg->RASTER_TIMING_2  = 0x02700000;
	
		g_ptLcdcReg->RASTER_SUBPANEL	 = 0x0;
		g_ptLcdcReg->LCDDMA_CTRL		 = 0x00000020; // low bit first
		
		g_ptLcdcReg->LCDDMA_FB0_BASE  	 = 0xc1f00000;   // Frame buffer start		
		g_ptLcdcReg->LCDDMA_FB0_CEILING  =	FRAMEBUF_BASE+LCD_SIZE_X*LCD_SIZE_Y*2+31;//( UINT32 ) (u8g_dsp_buffer + cn_frame_buffer_size - 1);

		MsDelay(5);
		g_ptLcdcReg->RASTER_CTRL  = 0x01100080;
		MsDelay(5);
		g_ptLcdcReg->RASTER_CTRL |= 0x00000001;    // Enable controller
		while(((g_ptLcdcReg->LCD_STAT)&0x40) == 0)
		{
			;
		}
		g_ptLcdcReg->RASTER_CTRL &= 0xfffffffe;    // Turn raster controller off
		g_ptLcdcReg->LCDDMA_FB0_BASE  = 0xc1f00020;
		MsDelay(5);
		g_ptLcdcReg->RASTER_CTRL  = 0x01200080;
		MsDelay(5);
		g_ptLcdcReg->RASTER_CTRL |= 0x00000001;    // Enable controller

		
		SetColor(0xffff); // clear screen (0x0000 for black and 0xffff for white)
		MsDelay(500);
}

void Lcd_BKOn(void)
{   
	GPIO_setOutput(8,10,1);
}   
  
void Lcd_BKOff(void)
{   
	 GPIO_setOutput(8,10,0);
}  

void Lcd_SetPixel(UINT8 *vaddr,UINT16 x,UINT16 y,UINT16 color)
{
	*((UINT16 *)(vaddr + y * (LCD_SIZE_X * 2) + (x << 1))) = color;

}

UINT8 Lcd_bmp(UINT16* addrBmp, UINT32 x,UINT32 y, UINT32 x_len,UINT32 y_len)
{
	UINT32 x1,y1;
	UINT16 *pDst;
		
		pDst = (UINT16 *)addrBmp;
		
		  for (y1 = 0; y1 < y_len; y1++)
		  	for (x1 = 0; x1 < x_len; x1++)
			 Lcd_SetPixel((UINT8 *)(0xc1f00000+32),x+x1, y+y1,*pDst++);

    return 0;
}

void SetColor(UINT16 color)
{
    UINT32 x, y;
    for (x = 0; x < 640; x++)
      for (y = 0; y < 480; y++)
         Lcd_SetPixel((UINT8 *)(0xc1f00000+32),x, y, color);
}

void DispXp1(void)
{
//	Lcd_bmp((UINT16 *)gImage_xp640480, 0, 0,640, 480); 
}

//-----------------------------------------------------------------------------
// Public Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// \brief   tests the nand.
//
// \param   none.
//
// \return  UINT32
//-----------------------------------------------------------------------------
UINT32 TEST_lcd(void)
{
   DebugPrintf("------------------------------------------------------------\r\n");
   DebugPrintf("                    C6748 lcd Test\r\n\r\n");

   //-------------------------------------
   // initialize the required bsl modules.
   //-------------------------------------
   DebugPrintf("lcd display pictures!\r\n\r\n");

   //DispXp1();
   //MsDelay(500);

   DebugPrintf("\r\n\r\n");
   DebugPrintf("                    C6748 lcd Test Over!\r\n\r\n");
   DebugPrintf("------------------------------------------------------------\r\n");
    
   return (ERR_NO_ERROR);
}
