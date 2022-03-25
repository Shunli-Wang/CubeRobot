#include "types.h"
#include "test_uart.h"
#include <stdio.h>
#include <string.h>
#include "interrupt.h"

#define DEBUG_PORT           (2)//uart1
#define DEBUG_PORT_BaudRate  (9600)//uart1

extern void RK6748_uartRxInt0(void);
extern void RK6748_uartRxInt1(void);
extern void RK6748_uartRxInt2(void);

static void SetupInt(void)
{	
	// Initialize the DSP INTC
	IntDSPINTCInit();
	// Enable DSP interrupts globally
	IntGlobalEnable();
}

static void ConfigureIntUART0(void)
{
	IntRegister(C674X_MASK_INT4, RK6748_uartRxInt0);
	IntEventMap(C674X_MASK_INT4, SYS_INT_UART0_INT);
	IntEnable(C674X_MASK_INT4);
}

static void ConfigureIntUART1(void)
{
	IntRegister(C674X_MASK_INT5, RK6748_uartRxInt1);
	IntEventMap(C674X_MASK_INT5, SYS_INT_UART1_INT);
	IntEnable(C674X_MASK_INT5);
}

static void ConfigureIntUART2(void)
{
	IntRegister(C674X_MASK_INT6, RK6748_uartRxInt2);
	IntEventMap(C674X_MASK_INT6, SYS_INT_UART2_INT);
	IntEnable(C674X_MASK_INT6);
}

void DebugUartInit(void)
{  
	RK6748_uartInit(1,115200);
	RK6748_uartIntEnable(1);
	SetupInt();
	ConfigureIntUART1();
}

void DSP_STM32_Uart2Init(void)
{
	RK6748_uartInit(DEBUG_PORT,DEBUG_PORT_BaudRate);
	RK6748_uartIntEnable(DEBUG_PORT);
	SetupInt();
	ConfigureIntUART2();
}

void DebugPrintf(UINT8 *pData)
{
	RK6748_uartSend(DEBUG_PORT,pData);
	printf(pData);
}

void Uart2Init(void)
{  
	RK6748_uartInit(2,57600);
	RK6748_uartIntEnable(2);
	SetupInt();
	ConfigureIntUART2();
}
