#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "bujin.h"

#include "public.h"
#include "gui.h"
#include "lcd_driver.h"
#include "gui.h"
#include "flash.h"

#include "key.h"

/************************************
Steering engine: A 0123
Stepper motor:
	Direction: C0 C1 C2 C3
	Signal: C6 C7 C8 C9
	Enable: C4 C5 C12 C13 

cp+ up+ free+ +5v

1 90 157
2 75 142
3  95 162
4 50 117

************************************/
int main(void)
{
	uint8_t t,flag=0,flag1=0,flag2=0;
	u8 xulie[100];
	NVIC_Configuration();
	delay_init();
	uart_init(9600);

	KEY_Init();

	TFT_Init();
	FLASH_Init();
	TFT_ClearScreen(BLACK);
	GUI_Show16Chinese(80, 0, "Cube Restoration Robot", RED, BLACK);
	GUI_Show12Char(40, 40, "Initializing......", RED, BLACK);

	TIM5_PWM_Init(14399,100);
	TIM3_PWM_Init(899,39);
	delay_ms(50);
	GUI_Show12Char(40, 40, "Init ready        ", RED, BLACK);

/*	
1 90 157
2 75 142
3  95 162
4 50 117*/

	while(1)
	{	
		
		t=KEY_Scan(0);		
	  	if(t)
		{						   
			switch(t)
			{		
				case KEY_UP:
				if(flag1==0)
					{
						duoji13(kai1,kai3);//65 55 65 50
						flag1=1;
					}else
					{
						duoji24(kai2,kai4); //162  160 165 150
						flag1=0;
					}
					break;
				case KEY_LEFT:			
					saomiao();	
					jieshou();
				  chuli(USART_RX_BUF,xulie);
				  jiemofang(xulie);
					USART_RX_BUF[0]='\0';
				  xulie[0]='\0';
					break;
				case KEY_DOWN:	
					if(flag==0)
					{
						zhangkai(kai1,kai2,kai3,kai4);//65 55 65 50
						flag=1;
					}else
					{
						bihe(he1,he2,he3,he4); //162  160 165 150
						flag=0;
					}
					break;
				case KEY_RIGHT:
				if(flag2==0)
					{
						duoji13(he1,he3);//65 55 65 50
						flag2=1;
					}else
					{
						duoji24(he2,he4); //162  160 165 150
						flag2=0;
					}
					break;
				default:
					break;
			}
		}
		else 
			delay_ms(10); 		
	}
}
