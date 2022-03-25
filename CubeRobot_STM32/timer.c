#include "timer.h"
#include "usart.h"
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_Struct;
	TIM_OCInitTypeDef  TIM_OCstuct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0|GPIO_Pin_13|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);

  TIM_Struct.TIM_Prescaler=psc; 
	TIM_Struct.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_Struct.TIM_Period=arr;
	TIM_Struct.TIM_ClockDivision=TIM_CKD_DIV1;    
	TIM_TimeBaseInit(TIM3,&TIM_Struct);
   
	//PWM OUT
	
	TIM_OCstuct.TIM_OCMode=TIM_OCMode_PWM2; 
  TIM_OCstuct.TIM_OutputState=TIM_OutputState_Enable;          
  TIM_OCstuct.TIM_OCPolarity=TIM_OCPolarity_Low;    
	TIM_OC1Init(TIM3,&TIM_OCstuct);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_OCstuct.TIM_OCMode=TIM_OCMode_PWM2; 
  TIM_OCstuct.TIM_OutputState=TIM_OutputState_Enable;          
  TIM_OCstuct.TIM_OCPolarity=TIM_OCPolarity_Low;    
	TIM_OC2Init(TIM3,&TIM_OCstuct);
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_OCstuct.TIM_OCMode=TIM_OCMode_PWM2; 
  TIM_OCstuct.TIM_OutputState=TIM_OutputState_Enable;          
  TIM_OCstuct.TIM_OCPolarity=TIM_OCPolarity_Low;    
	TIM_OC3Init(TIM3,&TIM_OCstuct);
	
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_OCstuct.TIM_OCMode=TIM_OCMode_PWM2; 
  TIM_OCstuct.TIM_OutputState=TIM_OutputState_Enable;          
  TIM_OCstuct.TIM_OCPolarity=TIM_OCPolarity_Low;    
	TIM_OC4Init(TIM3,&TIM_OCstuct);

	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3,ENABLE);
	
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
}

void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_Struct;
	TIM_OCInitTypeDef  TIM_OCstuct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	

  TIM_Struct.TIM_Prescaler=psc; 
	TIM_Struct.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_Struct.TIM_Period=arr;
	TIM_Struct.TIM_ClockDivision=TIM_CKD_DIV1;    
	TIM_TimeBaseInit(TIM4,&TIM_Struct);
   
	//PWM OUT
	
	TIM_OCstuct.TIM_OCMode=TIM_OCMode_PWM2; 
  TIM_OCstuct.TIM_OutputState=TIM_OutputState_Enable;          
  TIM_OCstuct.TIM_OCPolarity=TIM_OCPolarity_Low;    
	TIM_OC1Init(TIM4,&TIM_OCstuct);
	
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	
	TIM_OCstuct.TIM_OCMode=TIM_OCMode_PWM2; 
  TIM_OCstuct.TIM_OutputState=TIM_OutputState_Enable;          
  TIM_OCstuct.TIM_OCPolarity=TIM_OCPolarity_Low;    
	TIM_OC3Init(TIM4,&TIM_OCstuct);
	
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_OCstuct.TIM_OCMode=TIM_OCMode_PWM2; 
  TIM_OCstuct.TIM_OutputState=TIM_OutputState_Enable;          
  TIM_OCstuct.TIM_OCPolarity=TIM_OCPolarity_Low;    
	TIM_OC4Init(TIM4,&TIM_OCstuct);

	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4,ENABLE);
	
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
}

void TIM5_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_Struct;
	TIM_OCInitTypeDef  TIM_OCstuct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

  TIM_Struct.TIM_Prescaler=psc; 
	TIM_Struct.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_Struct.TIM_Period=arr;
	TIM_Struct.TIM_ClockDivision=TIM_CKD_DIV1;    
	TIM_TimeBaseInit(TIM5,&TIM_Struct);
   
	//PWM OUT
	
	TIM_OCstuct.TIM_OCMode=TIM_OCMode_PWM2; 
  TIM_OCstuct.TIM_OutputState=TIM_OutputState_Enable;          
  TIM_OCstuct.TIM_OCPolarity=TIM_OCPolarity_Low;    
	TIM_OC1Init(TIM5,&TIM_OCstuct);
	
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	TIM_OCstuct.TIM_OCMode=TIM_OCMode_PWM2; 
  TIM_OCstuct.TIM_OutputState=TIM_OutputState_Enable;          
  TIM_OCstuct.TIM_OCPolarity=TIM_OCPolarity_Low;    
	TIM_OC2Init(TIM5,&TIM_OCstuct);
	
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	
	TIM_OCstuct.TIM_OCMode=TIM_OCMode_PWM2; 
  TIM_OCstuct.TIM_OutputState=TIM_OutputState_Enable;          
  TIM_OCstuct.TIM_OCPolarity=TIM_OCPolarity_Low;    
	TIM_OC3Init(TIM5,&TIM_OCstuct);
	
	TIM_OC3PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	TIM_OCstuct.TIM_OCMode=TIM_OCMode_PWM2; 
  TIM_OCstuct.TIM_OutputState=TIM_OutputState_Enable;          
  TIM_OCstuct.TIM_OCPolarity=TIM_OCPolarity_Low;    
	TIM_OC4Init(TIM5,&TIM_OCstuct);

	TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM5,ENABLE);
	
	TIM_SetCompare1(TIM5,0);
	TIM_SetCompare2(TIM5,0);
	TIM_SetCompare3(TIM5,0);
	TIM_SetCompare4(TIM5,0);

}
