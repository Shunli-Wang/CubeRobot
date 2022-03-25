#ifndef __USART2_H
#define __USART2_H
#include "stdio.h"	
#include "sys.h" 

#define USART2_REC_LEN  		200
#define EN_USART2_RX 			1
	  	
extern u8  USART2_RX_BUF[USART2_REC_LEN];
extern u16 USART2_RX_STA;

void uart2_init(u32 bound);
#endif
