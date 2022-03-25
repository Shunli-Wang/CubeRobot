#include "delay.h"
#include "bujin.h"
#include "sys.h"
#include "usart.h"

#include "public.h"
#include "gui.h"
#include "lcd_driver.h"

void bujin1(u8 fangxiang,u8 jiaodu)  // Direction: 0-clockwise 1-anticlockwise
{
	u16 time;
	time=450;
	if(fangxiang==0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
	}else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	}
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
	TIM_SetCompare1(TIM3,450);
	delay_ms(time);
	if(jiaodu==180)
	{
		delay_ms(time);
	}
	TIM_SetCompare1(TIM3,0);
	GPIO_ResetBits(GPIOC,GPIO_Pin_4);
}

void bujin2(u8 fangxiang,u8 jiaodu)
{
	u16 time;
	time=450;
	if(fangxiang==0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_1);
	}else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	}
	GPIO_SetBits(GPIOC,GPIO_Pin_5);
	TIM_SetCompare2(TIM3,450);
	delay_ms(time);
	if(jiaodu==180)
	{
		delay_ms(time);
	}
	TIM_SetCompare2(TIM3,0);
	GPIO_ResetBits(GPIOC,GPIO_Pin_5);
}

void bujin3(u8 fangxiang,u8 jiaodu)
{
	u16 time;
	time=450;
	if(fangxiang==0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_2);
	}else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	}
	GPIO_SetBits(GPIOC,GPIO_Pin_12);
	TIM_SetCompare3(TIM3,450);
	delay_ms(time);
	if(jiaodu==180)
	{
		delay_ms(time+5);
	}
	TIM_SetCompare3(TIM3,0);
	GPIO_ResetBits(GPIOC,GPIO_Pin_12);
}

void bujin4(u8 fangxiang,u8 jiaodu)
{
	u16 time;
	time=450;
	if(fangxiang==0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
	}else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	}
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	TIM_SetCompare4(TIM3,450);
	delay_ms(time);
	if(jiaodu==180)
	{
		delay_ms(time+2);
	}
	TIM_SetCompare4(TIM3,0);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void bujin13(u8 fangxiang1,u8 fangxiang3,u8 jiaodu)
{
	u16 time;
	time=5*jiaodu;
	if(fangxiang1==0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
	}else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	}
	if(fangxiang3==0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_2);
	}else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	}
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
	GPIO_SetBits(GPIOC,GPIO_Pin_12);
	TIM_SetCompare1(TIM3,45);
	TIM_SetCompare3(TIM3,45);
	delay_ms(time);
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	GPIO_ResetBits(GPIOC,GPIO_Pin_12);
}

void bujin24(u8 fangxiang2,u8 fangxiang4,u8 jiaodu)
{
	u16 time;
	time=5*jiaodu;
	if(fangxiang2==0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_1);
	}else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	}
	if(fangxiang4==0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
	}else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	}
	GPIO_SetBits(GPIOC,GPIO_Pin_5);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	TIM_SetCompare2(TIM3,45);
	TIM_SetCompare4(TIM3,45);
	delay_ms(time);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare4(TIM3,0);
	GPIO_ResetBits(GPIOC,GPIO_Pin_5);	
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void duoji1(double jiaodu)
{
	u16 time;
	time=(jiaodu/180+1)*720-1;
	TIM_SetCompare1(TIM5,time);
	delay_ms(350);
	TIM_SetCompare1(TIM5,0);
}

void duoji2(double jiaodu)
{
	u16 time;
	time=(jiaodu/180+1)*720-1;
	TIM_SetCompare2(TIM5,time);
	delay_ms(350);
	TIM_SetCompare2(TIM5,0);
}

void duoji3(double jiaodu)
{
	u16 time;
	time=(jiaodu/180+1)*720-1;
	TIM_SetCompare3(TIM5,time);
	delay_ms(350);
	TIM_SetCompare3(TIM5,0);
}

void duoji4(double jiaodu)
{
	u16 time;
	time=(jiaodu/180+1)*720-1;
	TIM_SetCompare4(TIM5,time);
	delay_ms(350);
	TIM_SetCompare4(TIM5,0);
}

void duoji13(double jiaodu1,double jiaodu3)
{
	u16 time1,time3;
	time1=(jiaodu1/180+1)*720-1;
	time3=(jiaodu3/180+1)*720-1;
	TIM_SetCompare1(TIM5,time1);
	TIM_SetCompare3(TIM5,time3);
	delay_ms(350);
	TIM_SetCompare1(TIM5,0);
	TIM_SetCompare3(TIM5,0);
}

void duoji24(double jiaodu2,double jiaodu4)
{
	u16 time2,time4;
	time2=(jiaodu2/180+1)*720-1;
	time4=(jiaodu4/180+1)*720-1;
	TIM_SetCompare2(TIM5,time2);
	TIM_SetCompare4(TIM5,time4);
	delay_ms(350);
	TIM_SetCompare2(TIM5,0);
	TIM_SetCompare4(TIM5,0);
}

void saomiao()
{
	USART_SendData(USART1, 0x30);
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{		
			USART_RX_STA=0;
			if(USART_RX_BUF[0]==0x30)
				{
					USART_RX_STA=0;
					break;
				}
			}
		USART_SendData(USART1, 0x30);
		delay_ms(100);
	}
	zhuangdong1();
	USART_SendData(USART1, 0x31);
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{			
			USART_RX_STA=0;
			if(USART_RX_BUF[0]==0x31)
				{
					USART_RX_STA=0;
					break;
				}
			}
		USART_SendData(USART1, 0x31);
		delay_ms(100);
	}
	zhuangdong2();
	USART_SendData(USART1, 0x32);
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{			
			USART_RX_STA=0;
			if(USART_RX_BUF[0]==0x32)
				{
					USART_RX_STA=0;
					break;
				}
			}
		USART_SendData(USART1, 0x32);
		delay_ms(100);		
	}
	zhuangdong3();
	USART_SendData(USART1, 0x33);
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{			
			USART_RX_STA=0;
			if(USART_RX_BUF[0]==0x33)
				{
					USART_RX_STA=0;
					break;
				}
			}
		USART_SendData(USART1, 0x33);
		delay_ms(100);		
	}
	zhuangdong4();
	USART_SendData(USART1, 0x34);
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{			
			USART_RX_STA=0;
			if(USART_RX_BUF[0]==0x34)
				{
					USART_RX_STA=0;
					break;
				}
			}
		USART_SendData(USART1, 0x34);
		delay_ms(100);		
	}
	zhuangdong5();
	USART_SendData(USART1, 0x35);
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{			
			USART_RX_STA=0;
			if(USART_RX_BUF[0]==0x35)
				{	
					USART_RX_STA=0;
					break;
				}
			}
		USART_SendData(USART1, 0x35);
		delay_ms(100);
	}
	zhuangdong6();
	USART_SendData(USART1, 0x36);
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{			
			USART_RX_STA=0;
			if(USART_RX_BUF[0]==0x36)
				{
					USART_RX_STA=0;
					break;
				}
			}
		USART_SendData(USART1, 0x36);
		delay_ms(100);
	}
	weizhichushi();
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{		
			USART_RX_STA=0;
			break;
		}
	}
	
}

void jieshou()
{
	USART_SendData(USART1, 0x37);
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{			
			USART_RX_STA=0;
			if(USART_RX_BUF[0]==0x37)
				{
					USART_RX_STA=0;
					break;
				}
			}
		USART_SendData(USART1, 0x37);
		delay_ms(100);
	}
	delay_ms(300);
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{		
			break;
		}
	}
}
//len=USART_RX_STA&0x3f;
void jiemofang(u8* result)
{
	u8 i=0;
	GUI_Show12Char(40, 60, "Steps to restore the cube:", RED, BLACK);
	GUI_Show12Char(40, 80,result, RED, BLACK);
	GUI_Show12Char(40, 140, "Solving......", RED, BLACK);
	while(result[i]!='\0')
	{
			switch(result[i])
			{		
				case 'F':
					F(result[i+1]-0x30);
					break;
				case 'B':
					B(result[i+1]-0x30);
					break;
				case 'U':
					U(result[i+1]-0x30);
					break;
				case 'D':
					D(result[i+1]-0x30);
					break;
				case 'L':
					L(result[i+1]-0x30);
					break;
				case 'R':
					R(result[i+1]-0x30);
					break;
				case 'X':
					X();
					break;
				case 'S':
					S();
					break;
			}
			i+=2;
	}
	GUI_Show12Char(40, 140, "Complete !         ", RED, BLACK);
}

void zhangkai(double jiaodu1,double jiaodu2,double jiaodu3,double jiaodu4)
{
	uint16_t time1,time2,time3,time4;
	time1=(jiaodu1/180+1)*720-1;
	time2=(jiaodu2/180+1)*720-1;
	time3=(jiaodu3/180+1)*720-1;
	time4=(jiaodu4/180+1)*720-1;
	TIM_SetCompare2(TIM5,time2);
	TIM_SetCompare1(TIM5,time1);
	TIM_SetCompare3(TIM5,time3);
	TIM_SetCompare4(TIM5,time4);
	delay_ms(1000);
	TIM_SetCompare1(TIM5,0);
	TIM_SetCompare2(TIM5,0);
	TIM_SetCompare3(TIM5,0);
	TIM_SetCompare4(TIM5,0);
}

void bihe(double jiaodu1,double jiaodu2,double jiaodu3,double jiaodu4)
{
	uint16_t time1,time2,time3,time4;
	time1=(jiaodu1/180+1)*720-1;
	time2=(jiaodu2/180+1)*720-1;
	time3=(jiaodu3/180+1)*720-1;
	time4=(jiaodu4/180+1)*720-1;
	TIM_SetCompare1(TIM5,time1);
	TIM_SetCompare2(TIM5,time2);
	TIM_SetCompare3(TIM5,time3);
	TIM_SetCompare4(TIM5,time4);
	delay_ms(1000);
	TIM_SetCompare1(TIM5,0);
	TIM_SetCompare2(TIM5,0);
	TIM_SetCompare3(TIM5,0);
	TIM_SetCompare4(TIM5,0);
}

void L(u8 num)
{	
	u8 fangxiang=1;
	if(num==3)
	{
		num=1;
		fangxiang=0;
	}
	bujin1(fangxiang,num*90);
	if(num!=2)
	{
		duoji1(kai1);//kai
		bujin1(1-fangxiang,num*90);
		duoji1(he1);//he
	}
}

void R(u8 num)
{
	u8 fangxiang=1;
	if(num==3)
	{
		num=1;
		fangxiang=0;
	}
	bujin3(fangxiang,num*90);
	if(num!=2)
	{
		duoji3(kai3);//kai
		bujin3(1-fangxiang,num*90);
		duoji3(he3);//he
	}
}

void D(u8 num)
{
	F(num);
}
void X()
{
	duoji24(kai2,kai4);//24kai
	bujin13(0,1,90);//13xaing 4 zhaung90
	duoji24(he2,he4);//24he
	duoji13(kai1,kai3);//13kai
	bujin13(1,0,90);//13xaing 2 zhaung90
	duoji13(he1,he3);//13he
}
void S()
{
	duoji24(kai2,kai4);//24kai
	bujin13(1,0,90);//13xaing 2 zhaung90
	duoji24(he2,he4);//24he
	duoji13(kai1,kai3);//13kai
	bujin13(0,1,90);//13xaing 4 zhaung90
	duoji13(he1,he3);//13he
}
void U(u8 num)
{
	B(num);
}

void B(u8 num)
{
	u8 fangxiang=1;
	if(num==3)
	{
		num=1;
		fangxiang=0;
	}
	bujin4(fangxiang,num*90);
	if(num!=2)
	{
		duoji4(kai4);//kai
		bujin4(1-fangxiang,num*90);
		duoji4(he4);//he
	}
}

void F(u8 num)
{
	u8 fangxiang=1;
	if(num==3)
	{
		num=1;
		fangxiang=0;
	}
	bujin2(fangxiang,num*90);
	if(num!=2)
	{
		duoji2(kai2);//kai
		bujin2(1-fangxiang,num*90);
		duoji2(he2);//he
	}
}

void zhuangdong1()
{
	duoji13(kai1,kai3);//13kai
	bujin13(0,1,90);//13xaing 4 zhaung90
	duoji13(he1,he3);//13he
	duoji24(kai1,kai2);//24kai
}

void zhuangdong2()
{
	bujin13(0,1,90);//13xiang 4 zhaung180
	bujin13(0,1,90);
}

void zhuangdong3()
{
	bujin13(1,0,90);//13xiang 2 zhaung90
	bujin24(1,0,90);//24xiang 3 zahung90
	duoji24(he2,he4);//24he
	duoji13(kai1,kai3);//13kai

}

void zhuangdong4()
{
	bujin24(1,0,90);//24xiang 3 zhaung180
	bujin24(1,0,90);
}

void zhuangdong5()
{
	bujin24(0,1,90);//24xiang 1 zhaung90
	duoji13(he1,he3);//13he
	duoji24(kai2,kai4);//24kai
	bujin24(1,0,90);//24xiang 3 zhaung90
	duoji24(he2,he4);//24he
	duoji13(kai1,kai3);//13kai	
}

void zhuangdong6()
{	
	bujin24(0,1,90);//24xiang 1 zhaung180
	bujin24(0,1,90);
}

void weizhichushi()
{
	bujin24(1,0,90);//24xiang 3 zhaung90
	duoji13(he1,he3);//13he
	duoji24(kai2,kai4);//24kai
	bujin13(1,0,90);//13xiang 2 zhaung90
	duoji24(he2,he4);//24he
	duoji13(kai1,kai3);//13kai	
	bujin13(1,0,90);//13xiang 2 zhaung90
	duoji13(he1,he3);//13he
}

void chuli(u8* result,u8 *f)
{
	u8 i=0,j=0,a,c[100];
	while(result[i]!='\0')
	{
		a=result[i];
		if((a==result[i+2])&&(result[i+1]+result[i+3]==0x63))
		{
			c[j]=result[i];
			c[j+1]=0x33;
			i+=2;
		}else
		{
			c[j]=result[i];
			c[j+1]=result[i+1];
		}
		j+=2;
		i+=2;		
	}
	c[j]='\0';
	i=0;
	j=0;
	a=2;
	while(c[i]!='\0')
	{
		if(c[i]=='U'||c[i]=='D')
		{
			if(a==2)
			{
				a=0;
			}
			if(a==0)
			{
				a=1;			
				f[j]='X';
				f[j+1]=0x31;
				j=j+2;
			}
		}
		if(c[i]=='F'||c[i]=='B')
		{
			if(a==1)
			{
				a=0;			
				f[j]='S';
				f[j+1]=0x31;
				j=j+2;
			}
		}
		f[j]=c[i];
		f[j+1]=c[i+1];
		i=i+2;
		j=j+2;
	}
	f[j]='\0';

}
