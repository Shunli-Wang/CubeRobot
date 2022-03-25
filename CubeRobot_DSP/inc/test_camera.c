#include "stdio.h"
#include "types.h"
#include "rk6748.h"
#include "rk6748_timer.h"
#include "rk6748_gpio.h"
#include "rk6748_i2c.h"
#include "rk6748_vpif.h"
#include "test_camera.h"
#define IMAGE_SIZE_X       (640)
#define IMAGE_SIZE_Y       (480)

void camera_outtest(void)
{
	unsigned short *input_raw_10bit;
	unsigned short *input_rawbuf_10bit;
	unsigned long  i,j;

	input_raw_10bit    = (unsigned short *)0xc1f00020; // Start position
	input_rawbuf_10bit = (unsigned short *)0xc1000000; // Destination position
	for(i=0;i<IMAGE_SIZE_Y;i++)
	{
		for(j=0;j<IMAGE_SIZE_X;j++)
		{
			*input_rawbuf_10bit++=*input_raw_10bit++;
		}
	}
}

// RGB565 Testing
// RGB data will be shown in LCD screen

void rgb565_test(void)
{ 
	// Auto focus
	OV5640_RGB565_Mode();	// RGB565 mode
	OV5640_Focus_Init();
	
	OV5640_Light_Mode(0);	// Auto
	OV5640_Color_Saturation(3); // Color Saturation
	OV5640_Brightness(4);	// Brightness
	OV5640_Contrast(3);		// Contrast ratio
	OV5640_Sharpness(33);	// Automatic sharpness
	OV5640_Focus_Constant();// Start continuous focus
 	OV5640_OutSize_Set(4,0,640,480); 
} 

UINT32 TEST_imageSensor(void)
{
   UINT32 rtn = ERR_NO_ERROR;
   UINT32 i=0;

   DebugPrintf("------------------------------------------------------------\r\n");
   DebugPrintf("                C6748 Image Sensor OV5640 Test\r\n\r\n");
   DebugPrintf("Initialize the Required BSL Modules\r\n");
   DebugPrintf("-----------------------------------\r\n\r\n");

   RK6748_configCache();
   OV5640_Init();
   rgb565_test(); 

   MsDelay(50);
   rtn = VPIF_initReceive(VIDEO_CONN_CAMERA);

   /*
   MsDelay(1000);
   MsDelay(1000);
   MsDelay(1000);
   MsDelay(1000);
   MsDelay(1000);
   OV5640_Flash_Ctrl(1); // Light on
   MsDelay(500);
   camera_outtest();
   OV5640_Flash_Ctrl(0); // Light off
   CLRBIT(VPIF->CH0CTRL, CHANEN);
   CLRBIT(VPIF->CH1CTRL, CHANEN);
   SetColor(0xffff); // Clear screen (0x0000 for black and 0xffff for white)
   MsDelay(1000);
   MsDelay(1000);
   MsDelay(1000);
   Lcd_bmp((UINT16 *)0xC1000000, 0, 0,640, 480); // Show freeze frame photos
   while(1);
   */
   if (rtn != ERR_NO_ERROR)
   {
      DebugPrintf("error initializing vpif receive!\r\n");
      return (rtn);
   }

   DebugPrintf("\r\n\r\n");
   DebugPrintf("				C6748 Image Sensor OV5640 Test OK!\r\n\r\n");
   DebugPrintf("------------------------------------------------------------\r\n");

   return (rtn);
}
