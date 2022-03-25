/**
 * \file  interrupt.h
 *
 * \brief Contains DSP interrupt related API declarations and system interrupt
 *        event numbers. (Note: event numbers are device-specific.)
 */

/*
* Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/ 
*
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
** 							INTERNAL TYPE DEFINITIONS
******************************************************************************/
typedef void (*c674xISR)(void);


/******************************************************************************
** 							EXTERNAL MACRO DEFINITIONS
******************************************************************************/
/* API Parameter: cpuINT, ecmINTx
 *
 * Brief: Used to select DSP CPU maskable interrupt.
 *
 * Functions:
 *		IntRegister
 *		IntUnRegister
 *		IntEventMap
 *		IntEventCombineInit
 *		IntEnable
 *		IntDisable */
#define C674X_MASK_INT4 4
#define C674X_MASK_INT5 5
#define C674X_MASK_INT6 6
#define C674X_MASK_INT7 7
#define C674X_MASK_INT8 8
#define C674X_MASK_INT9 9
#define C674X_MASK_INT10 10
#define C674X_MASK_INT11 11
#define C674X_MASK_INT12 12
#define C674X_MASK_INT13 13
#define C674X_MASK_INT14 14
#define C674X_MASK_INT15 15
/* Functions:
 *		IntRegister
 *		IntUnRegister  */
#define C674X_MASK_NMI 1
#define C674X_MASK_EXC 1
#define C674X_MASK_RSV2 2
#define C674X_MASK_RSV3 3

/* API Parameter: ecmINTx ONLY
 *
 * Brief: Used to specify unused Event Combiner system events
 *
 * Functions:
 * 		IntEventCombineInit */
#define ECM0_UNUSED -1
#define ECM1_UNUSED -1
#define ECM2_UNUSED -1
#define ECM3_UNUSED -1

/* API Parameter: sysINT
 *
 * Brief: Used to select system interrupts.
 *
 * Functions:
 * 		IntEventMap
 * 		IntEventSet
 * 		IntEventClear
 * 		IntEventCombineAdd
 * 		IntEventCombineRemove
 * 		IntEventCombineRegister
 * 		ExcCombineAdd
 * 		ExcCombineRemove */
 
/*			Event Combiners */
#define SYS_INT_EVT0 				0
#define SYS_INT_EVT1 				1
#define SYS_INT_EVT2 				2
#define SYS_INT_EVT3 				3

/*			Timer Interrupts */
#define SYS_INT_T64P0_TINT12 		4
#define SYS_INT_T64P0_TINT34 		64
#define SYS_INT_T64P1_TINT12 		40
#define SYS_INT_T64P1_TINT34 		48
#define SYS_INT_T64P2_TINTALL 		25
#define SYS_INT_T64P3_TINTALL 		86

#define SYS_INT_T64P2_CMPINT0 		78
#define SYS_INT_T64P2_CMPINT1 		79
#define SYS_INT_T64P2_CMPINT2 		80
#define SYS_INT_T64P2_CMPINT3 		81
#define SYS_INT_T64P2_CMPINT4 		82
#define SYS_INT_T64P2_CMPINT5 		83
#define SYS_INT_T64P2_CMPINT6 		84
#define SYS_INT_T64P2_CMPINT7 		85

/*			Syscfg Interrupts */
#define SYS_INT_SYSCFG_CHIPINT2 	5
#define SYS_INT_SYSCFG_CHIPINT3 	67
#define SYS_INT_PROTERR 			74

/*			PRU Interrupts */
#define SYS_INT_PRU_EVTOUT0 		6
#define SYS_INT_PRU_EVTOUT1 		17
#define SYS_INT_PRU_EVTOUT2 		22
#define SYS_INT_PRU_EVTOUT3 		35
#define SYS_INT_PRU_EVTOUT4 		66
#define SYS_INT_PRU_EVTOUT5 		39
#define SYS_INT_PRU_EVTOUT6 		44
#define SYS_INT_PRU_EVTOUT7 		50

/*			EHRPWM Interrupts */
#define SYS_INT_EHRPWM0 			7
#define SYS_INT_EHRPWM0TZ 			10
#define SYS_INT_EHRPWM1 			18
#define SYS_INT_EHRPWM1TZ 			23

/*			EDMA Interrupts */
#define SYS_INT_EDMA3_0_CC0_INT1 	8
#define SYS_INT_EDMA3_0_CC0_ERRINT 	56
#define SYS_INT_EDMA3_0_TC0_ERRINT 	57
#define SYS_INT_EDMA3_0_TC1_ERRINT 	58
#define SYS_INT_EDMA3_1_CC0_INT1 	91
#define SYS_INT_EDMA3_1_CC0_ERRINT 	92 
#define SYS_INT_EDMA3_1_TC0_ERRINT 	93

/*			EMU Interrupts */
#define SYS_INT_EMU_DTDMA 			9
#define SYS_INT_EMU_RTDXRX 			11
#define SYS_INT_EMU_RTDXTX 			12

/*			IDMA Interrupts */
#define SYS_INT_IDMAINT0 			13
#define SYS_INT_IDMAINT1 			14

/*			MMCSD Interrupts */
#define SYS_INT_MMCSD0_INT0 		15
#define SYS_INT_MMCSD0_INT1 		16
#define SYS_INT_MMCSD1_INT0 		68
#define SYS_INT_MMCSD1_INT1 		53

/*			USB Interrupts */
#define SYS_INT_USB0     			19
#define SYS_INT_USB1_HCINT 			20
#define SYS_INT_USB1_RWAKEUP 		21

/*			SATA Interrupts */
#define SYS_INT_SATA_INT 			24

/*			EMAC Interrupts */
#define SYS_INT_EMAC_C0RXTHRESH 	26
#define SYS_INT_EMAC_C0RX 			27
#define SYS_INT_EMAC_C0TX 			28
#define SYS_INT_EMAC_C0MISC 		29
#define SYS_INT_EMAC_C1RXTHRESH 	30
#define SYS_INT_EMAC_C1RX 			31
#define SYS_INT_EMAC_C1TX 			32
#define SYS_INT_EMAC_C1MISC 		33

/*			HPI Interrupts */
#define SYS_INT_UHPI_DSPINT 		34

/*			I2C Interrupts */
#define SYS_INT_I2C0_INT 			36
#define SYS_INT_I2C1_INT 			42

/*			SPI Interrupts */
#define SYS_INT_SPI0_INT 			37
#define SYS_INT_SPI1_INT 			43

/*			UART Interrupts */
#define SYS_INT_UART0_INT 			38
#define SYS_INT_UART1_INT 			46
#define SYS_INT_UART2_INT 			69

/*			GPIO Interrupts */
#define SYS_INT_GPIO_B0INT 			65
#define SYS_INT_GPIO_B1INT 			41
#define SYS_INT_GPIO_B2INT 			49
#define SYS_INT_GPIO_B3INT 			52
#define SYS_INT_GPIO_B4INT 			54
#define SYS_INT_GPIO_B5INT 			59
#define SYS_INT_GPIO_B6INT 			62
#define SYS_INT_GPIO_B7INT 			72
#define SYS_INT_GPIO_B8INT 			75

/*			ECAP Interrupts */
#define SYS_INT_ECAP0 				45
#define SYS_INT_ECAP1 				47
#define SYS_INT_ECAP2 				51

/*			EMIF Interrupts */
#define SYS_INT_EMIFA_INT 			55

/*			DDR Interrupts */
#define SYS_INT_DDR2_MEMERR 		60

/*			MCASP Interrupts */
#define SYS_INT_MCASP0_INT 			61

/*			RTC Interrupts */
#define SYS_INT_RTC_IRQS 			63

/*			PSC Interrupts */
#define SYS_INT_PSC0_ALLINT 		70
#define SYS_INT_PSC1_ALLINT 		71

/*			LCD Interrupts */
#define SYS_INT_LCDC_INT 			73

/*			MCBSP Interrupts */
#define SYS_INT_MCBSP0_RINT 		87
#define SYS_INT_MCBSP0_XINT 		88
#define SYS_INT_MCBSP1_RINT 		89
#define SYS_INT_MCBSP1_XINT 		90

/*			UPP Interrupts */
#define SYS_INT_UPP_INT 			94

/*			VPIF Interrupts */
#define SYS_INT_VPIF_INT 			95

/*			INTC Interrupts */
#define SYS_INT_INTERR 				96

/*			EMC Interrupts */
#define SYS_INT_EMC_IDMAERR 		97
#define SYS_INT_EMC_CMPA 			126
#define SYS_INT_EMC_BUSERR 			127

/*			PMC Interrupts */
#define SYS_INT_PMC_ED 				113
#define SYS_INT_PMC_CMPA 			120
#define SYS_INT_PMC_DMPA 			121

/*			UMC Interrupts */
#define SYS_INT_UMC_ED1 			116
#define SYS_INT_UMC_ED2 			117
#define SYS_INT_UMC_CMPA 			124
#define SYS_INT_UMC_DMPA 			125

/*			PDC Interrupts */
#define SYS_INT_PDC_INT 			118

/*			SYS Interrupts */
#define SYS_INT_SYS_CMPA 			119

/*			DMC Interrupts */
#define SYS_INT_DMC_CMPA 			122
#define SYS_INT_DMC_DMPA 			123

#ifndef SYS_INT_USBSSINT
#define SYS_INT_USBSSINT    255
#endif



/******************************************************************************
**                      PERIPHERAL INSTANCE COUNT
******************************************************************************/

/** \brief Number of UPP  instances                                           */
#define SOC_UPP_PER_CNT                     1

/** \brief Number of UHPI instances                                           */
#define SOC_HPI_PER_CNT                     1

/** \brief Number of McASP instances                                          */
#define SOC_MCASP_PER_CNT                   1

/** \brief Number of TIMER instances                                          */
#define SOC_TMR_PER_CNT                     4

/** \brief Number of PSC instances                                            */
#define SOC_PSC_PER_CNT                     2

/** \brief Number of UART instances                                           */
#define SOC_UART_PER_CNT                    3

/** \brief Number of SPI instances                                            */
#define SOC_SPI_PER_CNT                     2

/** \brief Number of I2C instances                                            */
#define SOC_I2C_PER_CNT                     2

/** \brief Number of PLL instances                                            */
#define SOC_PLLC_PER_CNT                    2

/** \brief Number of MMCSD instances                                          */
#define SOC_MMCSD_PER_CNT                   2

/** \brief Number of LCDC instances                                           */
#define SOC_LCDC_PER_CNT                    1

/** \brief Number of Mcbsp instances                                          */
#define SOC_MCBSP_PER_CNT                   2

/** \brief Number of EDMA3 CC instances                                       */
#define SOC_EDMA3CC_CNT                     2

/** \brief Number of EDMA3 TC instances                                       */
#define SOC_EDMA3TC_CNT                     3

/** \brief Number of EMIFA instances                                          */
#define SOC_EMIFA_PER_CNT                   1

/** \brief Number of EMIFB instances                                          */
#define SOC_EMIFB_PER_CNT                   1

/** \brief Number of EMAC instances                                           */
#define SOC_EMAC_PER_CNT                    1

/** \brief Number of MDIO instances                                           */
#define SOC_MDIO_PER_CNT                    1

/** \brief Number of EHRPWM instances                                         */
#define SOC_EHRPWM_PER_CNT                  2

/** \brief Number of ECAP instances                                           */
#define SOC_ECAP_PER_CNT                    3

/** \brief Number of CPGMAC instances                                         */
#define SOC_CPGMACSSR_PER_CNT               1

/** \brief Number of CPPI instances                                           */
#define SOC_CPPI_PER_CNT                    1

/** \brief Number of USB instances                                            */
#define SOC_USB_PER_CNT                     2

/** \brief Number of VPIF instances                                           */
#define SOC_VPIF_PER_CNT                    1

/** \brief Number of INTC instances                                           */
#define SOC_INTC_PER_CNT                    1

/** \brief Number of AINTC instances                                          */
#define SOC_AINTC_PER_CNT                   1

/** \brief Number of SATA instances                                           */
#define SOC_SATA_PER_CNT                    1

/** \brief Number of RTC instances                                            */
#define SOC_RTC_PER_CNT                     1

/** \brief Number of GPIO instances                                           */
#define SOC_GPIO_PER_CNT                    1

/** \brief Number of SYSCFG instances                                         */
#define SOC_SYSCFG_PER_CNT                  2
/******************************************************************************
**                      PERIPHERAL INSTANCE DEFINITIONS
******************************************************************************/

/** \brief Peripheral Instances of UHPI instances                             */
#define SOC_HPI                             (0)

/** \brief Peripheral Instances of McASP instances                            */
#define SOC_MCASP_0                         (0)

/** \brief Peripheral Instance of EDMA CC instances                           */
#define SOC_EDMA3CC_0                       (0)
#define SOC_EDMA3CC_1                       (1)

/** \brief Peripheral Instance of EDMA TC instances                           */
#define SOC_EDMA3TC_0                       (0)
#define SOC_EDMA3TC_1                       (1)

/** \brief Peripheral Instance of Timer 64 instances                          */
#define SOC_TMR_0                           (0)
#define SOC_TMR_1                           (1)
#define SOC_TMR_2                           (2)
#define SOC_TMR_3                           (3)

/** \brief Peripheral Instances of PSC instances                              */
#define SOC_PSC_0                           (0)
#define SOC_PSC_1                           (1)

/** \brief Peripheral Instances of UART instances                             */
#define SOC_UART_0                          (0)
#define SOC_UART_1                          (1)
#define SOC_UART_2                          (2)

/** \brief Peripheral Instances of SPI instances                              */
#define SOC_SPI_0                           (0)
#define SOC_SPI_1                           (1)

/** \brief Peripheral Instances of I2C instances                              */
#define SOC_I2C_0                           (0)
#define SOC_I2C_1                           (1)

/** \brief Peripheral Instances of MMCSD instances                            */
#define SOC_MMCSD_0                         (0)
#define SOC_MMCSD_1                         (1)

/** \brief Peripheral Instances of LCDC instances                              */
#define SOC_LCDC                            (0)

/** \brief Instance number of PLL controller                                  */
#define SOC_PLLC_0                          (0)
#define SOC_PLLC_1                          (1)

/** \brief Peripheral Instance of EMIFA instances                             */
#define SOC_EMIFA                           (0)

/** \brief Peripheral Instance of EMAC instances                              */
#define SOC_EMAC                            (0)

/** \brief Peripheral Instance of MDIO instances                              */
#define SOC_MDIO                            (0)

/** \brief Peripheral Instance of EHRPWM instances                            */
#define SOC_EHRPWM_0                        (0)
#define SOC_EHRPWM_1                        (1)

/** \brief Peripheral Instance of ECAP instances                              */
#define SOC_ECAP_0                          (0)
#define SOC_ECAP_1                          (1)
#define SOC_ECAP_2                          (2)

/** \brief Peripheral Instance of USB instances                               */
#define SOC_USB_0                           (0)
#define SOC_USB_1                           (1)

/** \brief Peripheral Instance of PRU CORE instances                          */
#define SOC_PRUCORE_0                       (0)
#define SOC_PRUCORE_1                       (1)

/** \brief Peripheral Instance of PRUINTC instances                           */
#define SOC_PRUINTC                         (0)

/** \brief Peripheral Instances of VPIF instances                            */
#define SOC_VPIF                            (0)

/** \brief Peripheral Instance of INTC instances                              */
#define SOC_INTC                            (0)

/** \brief Peripheral Instance of AINTC instances                             */
#define SOC_AINTC                           (0)

/** \brief Peripheral Instance of RTC instances                               */
#define SOC_RTC                             (0)

/** \brief Peripheral Instance of GPIO instances                              */
#define SOC_GPIO                            (0)
/** \brief GPIO pin and bank information                                      */
#define SOC_GPIO_NUM_PINS                   (144)
#define SOC_GPIO_NUM_BANKS                  ((SOC_GPIO_NUM_PINS + 15)/16)

/** \brief Peripheral Instance of ECTL instances                              */
#define SOC_ECTL                            (0)

/** \brief Peripheral Instance of SYSCFG instances                            */
#define SOC_SYSCFG                          (2)

/******************************************************************************
**                      PERIPHERAL BASE ADDRESS
******************************************************************************/

/** \brief Base address of INTC memory mapped registers                       */
#define SOC_INTC_0_REGS                     (0x01800000)

/** \brief Base address of PDC memory mapped registers                        */
#define SOC_PWRDWN_PDC_REGS                 (0x01810000)

/** \brief Base address of SYS - Security ID register                         */
#define SOC_SYS_0_SECURITY_ID_REGS          (0x01811000)

/** \brief Base address of SYS - Revision ID register                         */
#define SOC_SYS_0_REV_ID_REGS               (0x01812000)

/** \brief IDMA Module memory mapped address  */
#define SOC_IDMA_0_REGS                     (0x01820000)

/** \brief EMC Module memory mapped address                                   */
#define SOC_EMC_0_REGS                      (0x01820000)

/** \brief Cache Module memory mapped address                                 */
#define SOC_CACHE_0_REGS                    (0x01840000)

/** \brief Base address of Channel controller  memory mapped registers        */
#define SOC_EDMA30CC_0_REGS                 (0x01C00000)

/** \brief Base address of Transfer controller  memory mapped registers       */
#define SOC_EDMA30TC_0_REGS                 (0x01C08000)
#define SOC_EDMA30TC_1_REGS                 (0x01C08400)

/** \brief Base address of PSC memory mapped registers                        */
#define SOC_PSC_0_REGS                      (0x01C10000)

/** \brief PLL controller instance o module address                           */
#define SOC_PLLC_0_REGS                     (0x01C11000)

/** \brief Base address of DEV memory mapped registers                        */
#define SOC_SYSCFG_0_REGS                   (0x01C14000)

/** \brief Base address of TIMER memory mapped registers                      */
#define SOC_TMR_0_REGS                      (0x01C20000)
#define SOC_TMR_1_REGS                      (0x01C21000)

/** \brief Base address of I2C memory mapped registers                        */
#define SOC_I2C_0_REGS                      (0x01C22000)

/** \brief Base address of RTC memory                                         */
#define SOC_RTC_0_REGS                      (0x01C23000)

/** \brief Base address of MMCSD memory mapped registers                      */
#define SOC_MMCSD_0_REGS                    (0x01C40000)

/** \brief Base address of SPI memory mapped registers                        */
#define SOC_SPI_0_REGS                      (0x01C41000)

/** \brief Base address of UART memory mapped registers                       */
#define SOC_UART_0_REGS                     (0x01C42000)

/** \brief Base address of McASP memory mapped registers                      */
#define SOC_MCASP_0_CTRL_REGS               (0x01D00000)
#define SOC_MCASP_0_FIFO_REGS               (0x01D01000)
#define SOC_MCASP_0_DATA_REGS               (0x01D02000)

/** \brief Base address of UART memory mapped registers                       */
#define SOC_UART_1_REGS                     (0x01D0C000)
#define SOC_UART_2_REGS                     (0x01D0D000)

/** \brief Base address of McBSP memory mapped registers                      */
#define SOC_MCBSP_0_CTRL_REGS               (0x01D10000)
#define SOC_MCBSP_0_FIFO_REGS               (0x01D10800)
#define SOC_MCBSP_0_DATA_REGS               (0x01F10000)

/** \brief Base address of McASP memory mapped registers                      */
#define SOC_MCBSP_1_CTRL_REGS               (0x01D11000)
#define SOC_MCBSP_1_FIFO_REGS               (0x01D11800)
#define SOC_MCBSP_1_DATA_REGS               (0x01F11000)

#define SOC_MPU_0_REGS                      (0x01E14000)
#define SOC_MPU_1_REGS                      (0x01E15000)

/** \brief Base address of USB memory                                         */
#define SOC_USB_0_REGS                      (0x01E00000)
#define SOC_USB_1_REGS                      (0x01E25000)

/** \brief Base address of HPI memory mapped registers                        */
#define SOC_HPI_0_REGS                      (0x01E10000)

/** \brief Base address of LCDC memory mapped registers                       */
#define SOC_LCDC_0_REGS                     (0x01E13000)

/** \brief Base address of UPP memory mapped registers                        */
#define SOC_UPP_0_REGS                      (0x01E16000)

/** \brief Base address of VPIF memory mapped registers                       */
#define SOC_VPIF_0_REGS                     (0x01E17000)

/** \brief Base address of SATA memory mapped registers                       */
#define SOC_SATA_0_REGS                     (0x01E18000)

/** \brief PLL controller instance 1 module address                           */
#define SOC_PLLC_1_REGS                     (0X01E1A000)

/** \brief Base address of MMCSD memory mapped registers                      */
#define SOC_MMCSD_1_REGS                    (0x01E1B000)

/** \brief Base address of EMAC memory                                        */
#define SOC_EMAC_DSC_CTRL_MOD_RAM           (0x01E20000)
#define SOC_EMAC_DSC_CTRL_MOD_REG           (0x01E22000)
#define SOC_EMAC_DSC_CONTROL_REG            (0x01E23000)
#define SOC_MDIO_0_REGS                     (0x01E24000)

/** \brief Base address of PRU Core Regsiters                                 */
#define SOC_PRUCORE_0_REGS                  (0x01C37000)
#define SOC_PRUCORE_1_REGS                  (0x01C37800)

/** \brief Base address of PRU Interrupt Controller Registers                 */
#define SOC_PRUINTC_0_REGS                  (0x01C34000)

/** \brief Base address of MUSB memmory mapped Registers                 */
#define SOC_USB_0_BASE              		(0x01E00400)

/** \brief Base address of  OTG  memmory mapped Registers                 */
#define SOC_USB_0_OTG_BASE             		(0x01E00000)

/** \brief USB 0 Phy regsister( CFGCHIP2 register) address				*/
#define SOC_USB_0_PHY_REGS					(0x01C14184)

/** \brief Base address of GPIO memory mapped registers                       */
#define SOC_GPIO_0_REGS                     (0x01E26000)

/** \brief Base address of PSC memory mapped registers                        */
#define SOC_PSC_1_REGS                      (0x01E27000)

/** \brief Base address of I2C memory mapped registers                        */
#define SOC_I2C_1_REGS                      (0x01E28000)

/** \brief Base address of syscfg registers                                   */
#define SOC_SYSCFG_1_REGS                   (0x01E2C000)

/** \brief Base address of Channel controller  memory mapped registers        */
#define SOC_EDMA31CC_0_REGS                 (0x01E30000)

/** \brief Base address of Transfer controller  memory mapped registers       */
#define SOC_EDMA31TC_0_REGS                 (0x01E38000)

/** \brief Base address of EPWM memory mapped registers                       */
#define SOC_EHRPWM_0_REGS                   (0x01F00000)
#define SOC_EHRPWM_1_REGS                   (0x01F02000)

/** \brief Base address of EPWM memory mapped registers                       */
#define SOC_HRPWM_0_REGS                    (0x01F01000)
#define SOC_HRPWM_1_REGS                    (0x01F03000)

/** \brief Base address of ECAP memory mapped registers                       */
#define SOC_ECAP_0_REGS                     (0x01F06000)
#define SOC_ECAP_1_REGS                     (0x01F07000)
#define SOC_ECAP_2_REGS                     (0x01F08000)

/** \brief Base address of TIMER memory mapped registers                      */
#define SOC_TMR_2_REGS                      (0x01F0C000)
#define SOC_TMR_3_REGS                      (0x01F0D000)

/** \brief Base address of SPI memory mapped registers                        */
#define SOC_SPI_1_REGS                      (0x01F0E000)

/** \brief Base address of EMIFA memory mapped registers                      */
#define SOC_EMIFA_0_REGS                    (0x68000000)

/** \brief Base address of EMIFA_CS0 memory                                   */
#define SOC_EMIFA_CS0_ADDR                  (0x40000000)

/** \brief Base address of EMIFA_CS2 memory                                   */
#define SOC_EMIFA_CS2_ADDR                  (0x60000000)

/** \brief Base address of EMIFA_CS3 memory                                   */
#define SOC_EMIFA_CS3_ADDR                  (0x62000000)

/** \brief Base address of EMIFA_CS4 memory                                   */
#define SOC_EMIFA_CS4_ADDR                  (0x64000000)

/** \brief Base address of EMIFA_CS5 memory                                   */
#define SOC_EMIFA_CS5_ADDR                  (0x66000000)

/** \brief Base address of DDR memory mapped registers                        */
#define SOC_DDR2_0_CTRL_REGS                (0xB0000000)
#define SOC_DDR2_0_DATA_REGS                (0xC0000000)

/** \brief Base address of AINTC memory mapped registers                      */
#define SOC_AINTC_0_REGS                    (0xFFFEE000)

/** \brief Base address of UMC Memory protection registers                    */
#define SOC_MEMPROT_L2_REGS                 (0x00800000)

/** \brief Base address of PMC memory Protection registers                    */
#define SOC_MEMPROT_L1P_REGS                (0x00E00000)

/** \brief Base address of DMC memory protection registers                    */
#define SOC_MEMPROT_L1D_REGS                (0x00F00000)

/******************************************************************************
**                      EDMA RELATED DEFINITIONS
******************************************************************************/

/* Parameterizable Configuration: These are fed directly from the RTL
 * parameters for the given SOC */

#define SOC_EDMA3_NUM_DMACH                 32
#define SOC_EDMA3_NUM_QDMACH                8
#define SOC_EDMA3_NUM_PARAMSETS             128
#define SOC_EDMA3_NUM_EVQUE                 2
#define SOC_EDMA3_CHMAPEXIST                0
#define SOC_EDMA3_NUM_REGIONS               4
#define SOC_EDMA3_MEMPROTECT                0

/******************************************************************************
**                      CHANNEL INSTANCE COUNT
******************************************************************************/
#define SOC_EDMA3_CHA_CNT                   (SOC_EDMA3_NUM_DMACH + \
                                             SOC_EDMA3_NUM_QDMACH)


/* QDMA channels */
#define    SOC_EDMA3_QCHA_BASE              SOC_EDMA3_NUM_DMACH         /* QDMA Channel Base */
#define    SOC_EDMA3_QCHA_0                 (SOC_EDMA3_QCHA_BASE + 0)   /* QDMA Channel 0 */
#define    SOC_EDMA3_QCHA_1                 (SOC_EDMA3_QCHA_BASE + 1)   /* QDMA Channel 1 */
#define    SOC_EDMA3_QCHA_2                 (SOC_EDMA3_QCHA_BASE + 2)   /* QDMA Channel 2 */
#define    SOC_EDMA3_QCHA_3                 (SOC_EDMA3_QCHA_BASE + 3)   /* QDMA Channel 3 */
#define    SOC_EDMA3_QCHA_4                 (SOC_EDMA3_QCHA_BASE + 4)   /* QDMA Channel 4 */
#define    SOC_EDMA3_QCHA_5                 (SOC_EDMA3_QCHA_BASE + 5)   /* QDMA Channel 5 */
#define    SOC_EDMA3_QCHA_6                 (SOC_EDMA3_QCHA_BASE + 6)   /* QDMA Channel 6 */
#define    SOC_EDMA3_QCHA_7                 (SOC_EDMA3_QCHA_BASE + 7)   /* QDMA Channel 7 */


/* Enumerations for EDMA Controlleres */
#define  SOC_EDMACC_ANY       -1 /* Any instance of EDMACC module*/
#define  SOC_EDMACC_0          0 /* EDMACC Instance 0            */


/* Enumerations for EDMA Event Queues */
#define  SOC_EDMA3_QUE_0     0 /* Queue 0                     */
#define  SOC_EDMA3_QUE_1     1 /* Queue 1                     */

/* Enumerations for EDMA Transfer Controllers
 *
 * There are 2 Transfer Controllers. Typically a one to one mapping exists
 * between Event Queues and Transfer Controllers. */
#define  SOC_EDMATC_ANY  -1 /* Any instance of EDMATC                */
#define  SOC_EDMATC_0    0  /* EDMATC Instance 0                     */
#define  SOC_EDMATC_1    1  /* EDMATC Instance 1                     */


#define SOC_EDMA3_REGION_GLOBAL            (-1)
#define SOC_EDMA3_REGION_0                  0
#define SOC_EDMA3_REGION_1                  1
#define SOC_EDMA3_REGION_2                  2
#define SOC_EDMA3_REGION_3                  3


/******************************************************************************
**                      DAT RELATED DEFINITIONS
******************************************************************************/

/* Parameterizable Configuration:- These are fed directly from the RTL
 * parameters for the given SOC */

 /******************************************************************************
**                      CHANNEL INSTANCE COUNT
******************************************************************************/
/** \brief Number of Generic Channel instances                                */


/** \brief Enumerations for EDMA channels
 *
 * There are 8 QDMA channels -
 */

#define    SOC_DAT_QCHA_0                   0 /**<   QDMA Channel 0           */
#define    SOC_DAT_QCHA_1                   1 /**<   QDMA Channel 1           */
#define    SOC_DAT_QCHA_2                   2 /**<   QDMA Channel 2           */
#define    SOC_DAT_QCHA_3                   3 /**<   QDMA Channel 3           */
#define    SOC_DAT_QCHA_4                   4 /**<   QDMA Channel 4           */
#define    SOC_DAT_QCHA_5                   5 /**<   QDMA Channel 5           */
#define    SOC_DAT_QCHA_6                   6 /**<   QDMA Channel 6           */
#define    SOC_DAT_QCHA_7                   7 /**<   QDMA Channel 7           */

/** \brief Enumerations for EDMA Event Queues
*
*  There are two Event Queues. Q0 is the highest priority and Q1 is the least
*  priority
*
*/
#define    SOC_DAT_PRI_DEFAULT    0 /* Queue 0 is default          */
#define    SOC_DAT_PRI_0          0 /* Queue 0                     */
#define    SOC_DAT_PRI_1          1 /* Queue 1                     */

/** \brief Enumeration for EDMA Regions
*
*
*/

#define SOC_DAT_REGION_GLOBAL              (-1)       /* Global Region        */
#define SOC_DAT_REGION_0                    0         /* EDMA Region 0        */
#define SOC_DAT_REGION_1                    1         /* EDMA Region 1        */
#define SOC_DAT_REGION_2                    2         /* EDMA Region 2        */
#define SOC_DAT_REGION_3                    3         /* EDMA Region 3        */

/** \brief Enumeration for peripheral frequencies
*
*
*/

#define SOC_SYSCLK_1_FREQ                   (300000000)
#define SOC_SYSCLK_2_FREQ                   (SOC_SYSCLK_1_FREQ/2)
#define SOC_SYSCLK_3_FREQ                   (SOC_SYSCLK_1_FREQ/3)
#define SOC_SYSCLK_4_FREQ                   (SOC_SYSCLK_1_FREQ/4)

#define SOC_ASYNC_2_FREQ                    (24000000)

/** I2C      */
#define SOC_I2C_0_MODULE_FREQ               (SOC_ASYNC_2_FREQ)
#define SOC_I2C_1_MODULE_FREQ               (SOC_SYSCLK_4_FREQ)

/** MCBSP    */
#define SOC_MCBSP_0_MODULE_FREQ             (SOC_SYSCLK_2_FREQ)
#define SOC_MCBSP_1_MODULE_FREQ             (SOC_SYSCLK_2_FREQ)

/** LCDC     */
#define SOC_LCDC_0_MODULE_FREQ              (SOC_SYSCLK_2_FREQ)

/** SPI      */
#define SOC_SPI_0_MODULE_FREQ               (SOC_SYSCLK_2_FREQ)
#define SOC_SPI_1_MODULE_FREQ               (SOC_SYSCLK_2_FREQ)

/** UART     */
#define SOC_UART_0_MODULE_FREQ              (SOC_SYSCLK_2_FREQ)
#define SOC_UART_1_MODULE_FREQ              (SOC_SYSCLK_2_FREQ)
#define SOC_UART_2_MODULE_FREQ              (SOC_SYSCLK_2_FREQ)

/** EHRPWM	*/
#define SOC_EHRPWM_0_MODULE_FREQ	    (SOC_SYSCLK_2_FREQ)
#define SOC_EHRPWM_1_MODULE_FREQ	    (SOC_SYSCLK_2_FREQ)



/******************************************************************************
**                      DSP INTC REGISTER OFFSETS
******************************************************************************/
/**
 * \brief	Macros used in conjunction with DSP interrupt controller
 *			base address for register addressing
 *
 * \param	n - Register instance
 *
 * \note	Minimum unit = 1 byte; Registers are 4 bytes
 */
#define DSPINTC_EVTFLAG(n)		(0x00000 + ((n)*4))
#define DSPINTC_EVTSET(n)		(0x00020 + ((n)*4))
#define DSPINTC_EVTCLR(n)		(0x00040 + ((n)*4))
#define DSPINTC_EVTMASK(n)		(0x00080 + ((n)*4))
#define DSPINTC_MEVTFLAG(n)		(0x000A0 + ((n)*4))
#define DSPINTC_EXPMASK(n)		(0x000C0 + ((n)*4))
#define DSPINTC_MEXPFLAG(n)		(0x000E0 + ((n)*4))
#define DSPINTC_INTMUX(n)		(0x00100 + ((n)*4))
#define DSPINTC_INTXSTAT		(0x00180)
#define DSPINTC_INTXCLR			(0x00184)
#define DSPINTC_INTDMASK		(0x00188)
#define DSPINTC_AEGMUX(n)		(0x10140 + ((n)*4))


/******************************************************************************
**                      FIELD DEFINITION MACROS
******************************************************************************/
/**
 * \registers	EVENT REGISTERS
 *
 * \brief		These registers manage the system events that are received by
 *				the controller. These include flag, set, and clear registers
 *				covering all system events.
 *
 * \param		n - Any system event
 *
 * \note		Shifting by (n & 31) ensures 0x1 does not shift by more than
 *				31 bits for system event IDs larger than 31. The proper event
 *				register must first be identified.
 */

/* Event Flag */
#define DSPINTC_EVTFLAG_EF(n)			(0x1 << ((n) & 31))

/* Event Set */
#define DSPINTC_EVTSET_ES(n)			(0x1 << ((n) & 31))

/* Event Clear */
#define DSPINTC_EVTCLR_EC(n)			(0x1 << ((n) & 31))


/**
 * \registers	EVENT COMBINER REGISTERS
 *
 * \brief		These registers allow up to 32 events to be combined into a
 *				single combined event which can then be used by the interrupt
 *				selector.
 *
 * \param		n - Any system event
 *
 * \note		Shifting by (n & 31) ensures 0x1 does not shift by more than
 *				31 bits for system event IDs larger than 31. The proper event
 *				combiner register must first be identified.
 */

/* Event Mask */
#define DSPINTC_EVTMASK_EM(n)			(0x1 << ((n) & 31))

/* Masked Event Flag */
#define DSPINTC_MEVTFLAG_MEF(n)			(0x1 << ((n) & 31))


/**
 * \registers	CPU INTERRUPT SELECTOR REGISTERS
 *
 * \brief		These registers manage which system events trigger the
 *				available CPU interrupts and also provide interrupt exception
 *				information.
 *
 * \param		n - Any CPU maskable interrupt
 */

/* Interrupt Mux */
#define DSPINTC_INTMUX_INTSEL_SHIFT(n)	(((n) & 0x3) * 8)
#define DSPINTC_INTMUX_INTSEL(n)		(0x7F << DSPINTC_INTMUX_INTSEL_SHIFT(n))

/* Interrupt Exception Status */
#define DSPINTC_INTXSTAT_SYSINT			(0xFF000000u)
#define DSPINTC_INTXSTAT_SYSINT_SHIFT	(0x00000018u)
#define DSPINTC_INTXSTAT_CPUINT			(0x00FF0000u)
#define DSPINTC_INTXSTAT_CPUINT_SHIFT	(0x00000010u)
#define DSPINTC_INTXSTAT_DROP			(0x00000001u)
#define DSPINTC_INTXSTAT_DROP_SHIFT		(0x00000000u)

/* Interrupt Exception Clear */
#define DSPINTC_INTXCLR_CLEAR			(0x00000001u)
#define DSPINTC_INTXCLR_CLEAR_SHIFT		(0x00000000u)

/* Dropped Interrupt Mask */
#define DSPINTC_INTDMASK_IDM(n)			(0x1 << (n))


//*****************************************************************************
//
// Macros for hardware access, both direct and via the bit-band region.
//
//*****************************************************************************
#define HWREG(x)                                                              \
        (*((volatile unsigned int *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile unsigned short *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile unsigned char *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((unsigned int)(x) & 0xF0000000) | 0x02000000 |                \
              (((unsigned int)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((unsigned int)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned int)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((unsigned int)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned int)(x) & 0x000FFFFF) << 5) | ((b) << 2))
               
//*****************************************************************************
//
// Prototype for the function that is called when an invalid argument is passed
// to an API.  This is only used when doing a DEBUG build.
//
//*****************************************************************************
extern void __error__(char *pcFilename, unsigned int ulLine);

//*****************************************************************************
//
// The ASSERT macro, which does the actual assertion checking.  Typically, this
// will be for procedure arguments.
//
//*****************************************************************************
#ifdef DEBUG
#define ASSERT(expr) {                                      \
                         if(!(expr))                        \
                         {                                  \
                             __error__(__FILE__, __LINE__); \
                         }                                  \
                     }
#else
#define ASSERT(expr)
#endif


/******************************************************************************
** 							FUNCTION DEFINITIONS
******************************************************************************/
extern void IntDSPINTCInit (void);
extern void IntRegister (unsigned int cpuINT, void (*userISR)(void));
extern void IntUnRegister (unsigned int cpuINT);
extern void IntEventMap (unsigned int cpuINT, unsigned int sysINT);
extern void IntEventSet (unsigned int sysINT);
extern void IntEventClear(unsigned int sysINT);
extern void IntEventCombineInit(int ecmINT0, int ecmINT1, int ecmINT2, int ecmINT3);
extern void IntEventCombineAdd(unsigned int sysINT);
extern void IntEventCombineRemove(unsigned int sysINT);
extern void IntEventCombineRegister(unsigned int sysINT, void (*userISR)(void));
extern void IntEnable (unsigned int cpuINT);
extern void IntDisable (unsigned int cpuINT);
extern void IntReset (void);
extern void IntGlobalEnable (void);
extern unsigned int IntGlobalDisable (void);
extern void IntGlobalRestore (unsigned int restoreValue);
extern void ExcGlobalEnable (void);
extern void ExcCombineAdd(unsigned int sysINT);
extern void ExcCombineRemove(unsigned int sysINT);

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_H_ */
