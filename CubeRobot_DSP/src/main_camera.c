#include "types.h"
#include "stdio.h"
#include "test_led.h"
#include "rk6748_vpif.h"
#include "rk6748.h"
#include <stdio.h>
#include <string.h>
int Cube_Solve_Order1[100]={
	1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,};
char Cube_Solve_Order2[100];

void Uart_Single_Get(int face)
{
	int i,check;
	char out=0;
	   MsDelay(500);
	   CLRBIT(VPIF->CH0CTRL, CHANEN);  // Disable VPIF channel
	   CLRBIT(VPIF->CH1CTRL, CHANEN);
	   Grid_On_All();  // Draw grids on the LCD screen
	   MsDelay(500);
			printf("The %d-th face: \n", face);
			check=Colorget_Cubeslove(face);  // Get all colors
			if((face==6)&&(check))  // If successfuly get all colors
			{
   				MsDelay(100);
   				RK6748_uartSendByte(2,0x36);
   				RK6748_uartSendByte(2,0x0D);
   				RK6748_uartSendByte(2,0x0A);
   				MsDelay(100);
   				RK6748_uartSendByte(2,0x36);
   				RK6748_uartSendByte(2,0x0D);
   				RK6748_uartSendByte(2,0x0A);
   				MsDelay(100);
   				RK6748_uartSendByte(2,0x36);
   				RK6748_uartSendByte(2,0x0D);
   				RK6748_uartSendByte(2,0x0A);

				face=0;check=0;
				Cube_Solve_Order_Transmission(Cube_Solve_Order1);
				printf("Yes!!!\n");
				for(i=0;i<80;i+=2)
				{
					printf("%c%d ",Cube_Solve_Order1[i],Cube_Solve_Order1[i+1]);
				}

				while(1)
				{
					RK6748_uartRx(2,&out);
					if(out==0x37)
					{
		   				MsDelay(100);
		   				RK6748_uartSendByte(2,0x37);
		   				RK6748_uartSendByte(2,0x0D);
		   				RK6748_uartSendByte(2,0x0A);
		   				MsDelay(100);


		   				for(i=0;i<100;i+=2)
		   				{
		   					Cube_Solve_Order2[i]=Cube_Solve_Order1[i];
		   					if(Cube_Solve_Order1[i+1]==1)
		   						Cube_Solve_Order2[i+1]=0x31;
		   					if(Cube_Solve_Order1[i+1]==2)
		   						Cube_Solve_Order2[i+1]=0x32;
		   					if(Cube_Solve_Order1[i+1]==3)
		   						Cube_Solve_Order2[i+1]=0x33;
		   				}
		   				RK6748_uartSend(2,Cube_Solve_Order2);
		   				RK6748_uartSendByte(2,0x0D);
		   				RK6748_uartSendByte(2,0x0A);

		   				break;
					}
				}
			}
			printf("\n");
	   SETBIT(VPIF->CH0CTRL, CHANEN);  // Enable the VPIF channel
	   SETBIT(VPIF->CH1CTRL, CHANEN);
}

void main(void)
{
	int i=0,face=0,check,Cube_Solve_Order[100];
	char out=0;
	USTIMER_init();
	KEY_init();				// Init key
	LED_init();				// Init LED
	DebugUartInit();		// Debug serial communication
	DSP_STM32_Uart2Init();	// Debug serial communication
	RK6748_lcdInit();		// Enable LCD screen
	TEST_lcd();				// LCD test
	TEST_imageSensor();		// Enable camera
	// CLRBIT(VPIF->CH0CTRL, CHANEN);	// Disable VPIF channel
	// CLRBIT(VPIF->CH1CTRL, CHANEN);


	while(1) // if DSP receive 0x30 from STM32 and ready, send 0x30 back to STM32
	{
		RK6748_uartRx(2,&out);
		if(out==0x30)
		{
			MsDelay(500);
			RK6748_uartSendByte(2,0x30);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);

			RK6748_uartSendByte(2,0x30);
			MsDelay(100);
			RK6748_uartSendByte(2,0x0D);
			MsDelay(100);
			RK6748_uartSendByte(2,0x0A);
			MsDelay(100);

			RK6748_uartSendByte(2,0x30);
			MsDelay(100);
			RK6748_uartSendByte(2,0x0D);
			MsDelay(100);
			RK6748_uartSendByte(2,0x0A);
			break;
		}
	}
	while(1) // STM32 turn the cube to the first face and send 0x31
	{
		RK6748_uartRx(2,&out);
		if(out==0x31)
		{
			Uart_Single_Get(1);
			MsDelay(100);
			RK6748_uartSendByte(2,0x31);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);

			MsDelay(100);
			RK6748_uartSendByte(2,0x31);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);

			MsDelay(100);
			RK6748_uartSendByte(2,0x31);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			break;
		}
	}
	while(1) // STM32 turn the cube to the second face and send 0x32
	{
		RK6748_uartRx(2,&out);
		if(out==0x32)
		{
			Uart_Single_Get(2);
			MsDelay(100);
			RK6748_uartSendByte(2,0x32);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			MsDelay(100);
			RK6748_uartSendByte(2,0x32);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			MsDelay(100);
			RK6748_uartSendByte(2,0x32);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			break;
		}
	}
	while(1) // STM32 turn the cube to the 3-th face and send 0x33
	{
		RK6748_uartRx(2,&out);
		if(out==0x33)
		{
			Uart_Single_Get(3);
			MsDelay(100);
			RK6748_uartSendByte(2,0x33);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			MsDelay(100);
			RK6748_uartSendByte(2,0x33);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			MsDelay(100);
			RK6748_uartSendByte(2,0x33);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			break;
		}
	}
	while(1) // STM32 turn the cube to the 4-th face and send 0x34
	{
		RK6748_uartRx(2,&out);
		if(out==0x34)
		{
			Uart_Single_Get(4);
			MsDelay(100);
			RK6748_uartSendByte(2,0x34);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			MsDelay(100);
			RK6748_uartSendByte(2,0x34);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			MsDelay(100);
			RK6748_uartSendByte(2,0x34);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			break;
		}
	}
	while(1) // STM32 turn the cube to the 5-th face and send 0x35
	{
		RK6748_uartRx(2,&out);
		if(out==0x35)
		{
			Uart_Single_Get(5);
			MsDelay(100);
			RK6748_uartSendByte(2,0x35);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			MsDelay(100);
			RK6748_uartSendByte(2,0x35);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			MsDelay(100);
			RK6748_uartSendByte(2,0x35);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			break;
		}
	}
	while(1) // STM32 turn the cube to the 6-th face and send 0x36
	{
		RK6748_uartRx(2,&out);
		if(out==0x36)
		{
			Uart_Single_Get(6);
			MsDelay(100);
			RK6748_uartSendByte(2,0x36);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			MsDelay(100);
			RK6748_uartSendByte(2,0x36);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			MsDelay(100);
			RK6748_uartSendByte(2,0x36);
			RK6748_uartSendByte(2,0x0D);
			RK6748_uartSendByte(2,0x0A);
			break;
		}
	}

	TEST_led();
}
