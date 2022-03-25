#ifndef RK6748_H
#define RK6748_H

#ifdef __cplusplus
extern "C" {
#endif

#define Uint32    unsigned int
#define Uint16    unsigned short
#define Uint8     unsigned char
#define Int32     int
#define Int16     short
#define Int8      char

#define SZ_1K                           0x00000400
#define SZ_4K                           0x00001000
#define SZ_8K                           0x00002000
#define SZ_16K                          0x00004000
#define SZ_32K                     		 0x00008000
#define SZ_64K                          0x00010000
#define SZ_128K                         0x00020000
#define SZ_256K                         0x00040000
#define SZ_512K                         0x00080000

#define SZ_1M                           0x00100000
#define SZ_2M                           0x00200000
#define SZ_4M                           0x00400000
#define SZ_8M                           0x00800000
#define SZ_16M                          0x01000000
#define SZ_32M                          0x02000000
#define SZ_64M                          0x04000000
#define SZ_128M                         0x08000000
#define SZ_256M                         0x10000000
#define SZ_512M                         0x20000000

#define SZ_1G                           0x40000000
#define SZ_2G                           0x80000000

#define SYS_CLK_IN 	25000000 
#define SYS_CLK1 	400000000 	 /*Diveder-1    1  	400MHZ*/	
#define SYS_CLK2 	200000000    /*Diveder-2    2  	200MHZ*/	
#define SYS_CLK3 	133000000    /*Diveder-3    3 	133MHZ*/	
#define SYS_CLK4 	100000000    /*Divider 4     4 	100MHZ*/    
//#define SYS_CLK5 	100000000    /*Divider 5     3 	133MHZ*/    not use
#define SYS_CLK6 	400000000    /*Divider 6     1 	400MHZ*/    
#define SYS_CLK7 	 50000000    /*Divider 7     8 	50MHZ*/     
#define AUX_CLK 	 25000000


//#define SW_BREAKPOINT       asm( " SWBP 0" );

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Device System Controller                                                *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define SYS_BASE            0x01C14000
#define SYS_REVID           (SYS_BASE + 0x000)  
#define DIEIDR0             (SYS_BASE + 0x008)
#define DIEIDR1             (SYS_BASE + 0x00C)
#define DIEIDR2             (SYS_BASE + 0x010)
#define DIEIDR3             (SYS_BASE + 0x014)
#define DEVIDR0             (SYS_BASE + 0x018)
#define DEVIDR1             (SYS_BASE + 0x01C)
#define SYS_BOOTCFG         (SYS_BASE + 0x020)
#define CHIPREVIDR          (SYS_BASE + 0x024)
#define KICK0R              (SYS_BASE + 0x038)  
#define KICK1R              (SYS_BASE + 0x03c)  
#define SYS_HOST0CFG        (SYS_BASE + 0x040)
#define SYS_HOST1CFG        (SYS_BASE + 0x044)
#define SYS_IRAWSTAT        (SYS_BASE + 0x0E0)  
#define SYS_IENSTAT         (SYS_BASE + 0x0E4)  
#define SYS_IENSET          (SYS_BASE + 0x0E8)  
#define SYS_IENCLR          (SYS_BASE + 0x0EC)  
#define SYS_EOI             (SYS_BASE + 0x0F0)  
#define SYS_FLTADDRR        (SYS_BASE + 0x0F4)  
#define SYS_FLTSTAT         (SYS_BASE + 0x0F8)  
#define MSTPRI0             (SYS_BASE + 0x110)  
#define MSTPRI1             (SYS_BASE + 0x114)  
#define MSTPRI2             (SYS_BASE + 0x118) 
#define PINMUX0				(SYS_BASE + 0x120)
#define PINMUX1				(SYS_BASE + 0x124)
#define PINMUX2				(SYS_BASE + 0x128)
#define PINMUX3				(SYS_BASE + 0x12C)
#define PINMUX4				(SYS_BASE + 0x130)
#define PINMUX5				(SYS_BASE + 0x134)
#define PINMUX6				(SYS_BASE + 0x138)
#define PINMUX7				(SYS_BASE + 0x13C)
#define PINMUX8				(SYS_BASE + 0x140)
#define PINMUX9				(SYS_BASE + 0x144)
#define PINMUX10			(SYS_BASE + 0x148)
#define PINMUX11			(SYS_BASE + 0x14C)
#define PINMUX12			(SYS_BASE + 0x150)
#define PINMUX13			(SYS_BASE + 0x154)
#define PINMUX14			(SYS_BASE + 0x158)
#define PINMUX15			(SYS_BASE + 0x15C)
#define PINMUX16			(SYS_BASE + 0x160)
#define PINMUX17			(SYS_BASE + 0x164)
#define PINMUX18			(SYS_BASE + 0x168)
#define PINMUX19			(SYS_BASE + 0x16C)
#define SYS_SUSPSRC		 	(SYS_BASE + 0x170) 
#define SYS_CHIPSIG	        (SYS_BASE + 0x174) 
#define SYS_CHIPSIG_CLR     (SYS_BASE + 0x178) 
#define CFGCHIP0            (SYS_BASE + 0x17C) 
#define CFGCHIP1            (SYS_BASE + 0x180) 
#define CFGCHIP2            (SYS_BASE + 0x184) 
#define CFGCHIP3           	(SYS_BASE + 0x188) 
#define CFGCHIP4		 	(SYS_BASE + 0x18C) 

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  GPIO Control                                                            *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define GPIO_BASE               0x01E26000

#define GPIO_PCR               ( GPIO_BASE + 0x04 )
#define GPIO_BINTEN            ( GPIO_BASE + 0x08 )


// For GPIO[0:31]
#define GPIO_DIR01             ( GPIO_BASE + 0x10 )
#define GPIO_OUT_DATA01        ( GPIO_BASE + 0x14 )
#define GPIO_SET_DATA01        ( GPIO_BASE + 0x18 )
#define GPIO_CLR_DATA01        ( GPIO_BASE + 0x1C )
#define GPIO_IN_DATA01         ( GPIO_BASE + 0x20 )
#define GPIO_SET_RIS_TRIG01    ( GPIO_BASE + 0x24 )
#define GPIO_CLR_RIS_TRIG01    ( GPIO_BASE + 0x28 )
#define GPIO_SET_FAL_TRIG01    ( GPIO_BASE + 0x2C )
#define GPIO_CLR_FAL_TRIG01    ( GPIO_BASE + 0x30 )
#define GPIO_INSTAT01          ( GPIO_BASE + 0x34 )

// For GPIO[32:63]
#define GPIO_DIR23             ( GPIO_BASE + 0x38 )
#define GPIO_OUT_DATA23        ( GPIO_BASE + 0x3C )
#define GPIO_SET_DATA23        ( GPIO_BASE + 0x40 )
#define GPIO_CLR_DATA23        ( GPIO_BASE + 0x44 )
#define GPIO_IN_DATA23         ( GPIO_BASE + 0x48 )
#define GPIO_SET_RIS_TRIG23    ( GPIO_BASE + 0x4C )
#define GPIO_CLR_RIS_TRIG23    ( GPIO_BASE + 0x50 )
#define GPIO_SET_FAL_TRIG23    ( GPIO_BASE + 0x54 )
#define GPIO_CLR_FAL_TRIG23    ( GPIO_BASE + 0x58 )
#define GPIO_INSTAT23          ( GPIO_BASE + 0x5C )

// For GPIO[64:70]
#define GPIO_DIR45             ( GPIO_BASE + 0x60 )
#define GPIO_OUT_DATA45        ( GPIO_BASE + 0x64 )
#define GPIO_SET_DATA45        ( GPIO_BASE + 0x68 )
#define GPIO_CLR_DATA45        ( GPIO_BASE + 0x6C )
#define GPIO_IN_DATA45         ( GPIO_BASE + 0x70 )
#define GPIO_SET_RIS_TRIG45    ( GPIO_BASE + 0x74 )
#define GPIO_CLR_RIS_TRIG45    ( GPIO_BASE + 0x78 )
#define GPIO_SET_FAL_TRIG45    ( GPIO_BASE + 0x7C )
#define GPIO_CLR_FAL_TRIG45    ( GPIO_BASE + 0x80 )
#define GPIO_INSTAT45          ( GPIO_BASE + 0x84 )

// For GPIO[71:101]
#define GPIO_DIR67             ( GPIO_BASE + 0x88 )
#define GPIO_OUT_DATA67        ( GPIO_BASE + 0x8C )
#define GPIO_SET_DATA67        ( GPIO_BASE + 0x90 )
#define GPIO_CLR_DATA67        ( GPIO_BASE + 0x94 )
#define GPIO_IN_DATA67         ( GPIO_BASE + 0x98 )
#define GPIO_SET_RIS_TRIG67    ( GPIO_BASE + 0x9C )
#define GPIO_CLR_RIS_TRIG67    ( GPIO_BASE + 0xA0 )
#define GPIO_SET_FAL_TRIG67    ( GPIO_BASE + 0xA4 )
#define GPIO_CLR_FAL_TRIG67    ( GPIO_BASE + 0xA8 )
#define GPIO_INSTAT67          ( GPIO_BASE + 0xAC )

#define GPIO_DIR8              ( GPIO_BASE + 0xB0 )
#define GPIO_OUT_DATA8         ( GPIO_BASE + 0xB4 )
#define GPIO_SET_DATA8         ( GPIO_BASE + 0xB8 )
#define GPIO_CLR_DATA8         ( GPIO_BASE + 0xBC )
#define GPIO_IN_DATA8          ( GPIO_BASE + 0xC0 )
#define GPIO_SET_RIS_TRIG8     ( GPIO_BASE + 0xC4 )
#define GPIO_CLR_RIS_TRIG8     ( GPIO_BASE + 0xC8 )
#define GPIO_SET_FAL_TRIG8     ( GPIO_BASE + 0xCC )
#define GPIO_CLR_FAL_TRIG8     ( GPIO_BASE + 0xD0 )
#define GPIO_INSTAT8           ( GPIO_BASE + 0xD4 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  INTC controller                                                         *
 *      Controls the Interrupts                                             *
 *                                                                          *
 * ------------------------------------------------------------------------ */
//	ARM Interrupt Controller (AINTC) Registers Map
#define     AINTC_BASE          0xFFFEE000					//AINTC base address
#define		AINTC_REVID 		( AINTC_BASE + 0x0    )      //Revision Identification Register 
#define		AINTC_CR 			( AINTC_BASE + 0x4    )      //Control Register 
#define		AINTC_GER 			( AINTC_BASE + 0x10   )      //Global Enable Register 
#define		AINTC_GNLR 			( AINTC_BASE + 0x1C   )      //Global Nesting Level Register 
#define		AINTC_SISR 			( AINTC_BASE + 0x20   )      //System Interrupt Status Indexed Set Register 
#define		AINTC_SICR 			( AINTC_BASE + 0x24   )      //System Interrupt Status Indexed Clear Register 
#define		AINTC_EISR 			( AINTC_BASE + 0x28   )      //System Interrupt Enable Indexed Set Register 
#define		AINTC_EICR 			( AINTC_BASE + 0x2C   )      //System Interrupt Enable Indexed Clear Register 
#define		AINTC_HIEISR 		( AINTC_BASE + 0x34   )      //Host Interrupt Enable Indexed Set Register 
#define		AINTC_HIEICR 		( AINTC_BASE + 0x38   )      //Host Interrupt Enable Indexed Clear Register 
#define		AINTC_VBR 			( AINTC_BASE + 0x50   )      //Vector Base Register 
#define		AINTC_VSR 			( AINTC_BASE + 0x54   )      //Vector Size Register 
#define		AINTC_VNR 			( AINTC_BASE + 0x58   )      //Vector Null Register 
#define		AINTC_GPIR 			( AINTC_BASE + 0x80   )      //Global Prioritized Index Register 
#define		AINTC_GPVR 			( AINTC_BASE + 0x84   )      //Global Prioritized Vector Register 
#define		AINTC_SRSR1 		( AINTC_BASE + 0x200  )      //System Interrupt Status Raw/Set Register 1 
#define		AINTC_SRSR2 		( AINTC_BASE + 0x204  )      //System Interrupt Status Raw/Set Register 2 
#define		AINTC_SRSR3 		( AINTC_BASE + 0x208  )      //System Interrupt Status Raw/Set Register 3 
#define		AINTC_SRSR4 		( AINTC_BASE + 0x20C  )      //System Interrupt Status Raw/Set Register 4 
#define		AINTC_SECR1 		( AINTC_BASE + 0x280  )      //System Interrupt Status Enabled/Clear Register 1 
#define		AINTC_SECR2 		( AINTC_BASE + 0x284  )      //System Interrupt Status Enabled/Clear Register 2 
#define		AINTC_SECR3 		( AINTC_BASE + 0x288  )      //System Interrupt Status Enabled/Clear Register 3 
#define		AINTC_SECR4 		( AINTC_BASE + 0x28C  )      //System Interrupt Status Enabled/Clear Register 4
#define		AINTC_ESR1 			( AINTC_BASE + 0x300  )      //System Interrupt Enable Set Register 1 
#define		AINTC_ESR2 			( AINTC_BASE + 0x304  )      //System Interrupt Enable Set Register 2 
#define		AINTC_ESR3 			( AINTC_BASE + 0x308  )      //System Interrupt Enable Set Register 3 
#define		AINTC_ESR4 			( AINTC_BASE + 0x30C  )      //System Interrupt Enable Set Register 4 
#define		AINTC_ECR1 			( AINTC_BASE + 0x380  )      //System Interrupt Enable Clear Register 1 
#define		AINTC_ECR2 			( AINTC_BASE + 0x384  )      //System Interrupt Enable Clear Register 2 
#define		AINTC_ECR3 			( AINTC_BASE + 0x388  )      //System Interrupt Enable Clear Register 3 
#define		AINTC_ECR4 			( AINTC_BASE + 0x38C  )      //System Interrupt Enable Clear Register 4 
#define		AINTC_CMR0			( AINTC_BASE + 0x400  )      //Channel Map Registers 0-22 
#define		AINTC_HIPIR1 		( AINTC_BASE + 0x900  )      //Host Interrupt Prioritized Index Register 1 
#define		AINTC_HIPIR2 		( AINTC_BASE + 0x904  )      //Host Interrupt Prioritized Index Register 2 
#define		AINTC_HINLR1 		( AINTC_BASE + 0x1100 )      //Host Interrupt Nesting Level Register 1 
#define		AINTC_HINLR2 		( AINTC_BASE + 0x1104 )      //Host Interrupt Nesting Level Register 2 
#define		AINTC_HIER 			( AINTC_BASE + 0x1500 )      //Host Interrupt Enable Register 
#define		AINTC_HIPVR1 		( AINTC_BASE + 0x1600 )      //Host Interrupt Prioritized Vector Register 1 
#define		AINTC_HIPVR2 		( AINTC_BASE + 0x1604 )      //Host Interrupt Prioritized Vector Register 2 

// ESR1 PENDING BIT
#define BIT_COMMTX 							(0x1<<31)
#define BIT_COMMRX 							(0x1<<30)
#define BIT_NINT 							(0x1<<29)
#define BIT_Reserved3						(0x1<<28)
#define BIT_Reserved4					    (0x1<<27)
#define BIT_Reserved5						(0x1<<26)
#define BIT_Reserved6						(0x1<<25)
#define BIT_Reserved7						(0x1<<24)
#define BIT_Reserved8						(0x1<<23)
#define BIT_Reserved9						(0x1<<22)
#define BIT_Reserved10						(0x1<<21)
#define BIT_EDMA3_CC0_CCINT 				(0x1<<20)
#define BIT_EDMA3_CC0_CCERRINT 				(0x1<<19)
#define BIT_EDMA3_TC0_TCERRINT 				(0x1<<18)
#define BIT_EMIFA_INT 						(0x1<<17)
#define BIT_IIC0_INT 						(0x1<<16)
#define BIT_MMCSD_INT0 						(0x1<<15)
#define BIT_MMCSD_INT1 						(0x1<<14)
#define BIT_PSC0_ALLINT 					(0x1<<13)
#define BIT_RTC_IRQS    					(0x1<<12)
#define BIT_SPI0_INT 						(0x1<<11)
#define BIT_T64P0_TINT12 					(0x1<<10)
#define BIT_T64P0_TINT34 					(0x1<<9)
#define BIT_T64P1_TINT12 					(0x1<<8)
#define BIT_T64P1_TINT34 					(0x1<<7)
#define BIT_UART0_INT 						(0x1<<6)
#define BIT_Reserved26          			(0x1<<5)
#define BIT_PROTERR 						(0x1<<4)
#define BIT_SYSCFG_CHIPINT0 				(0x1<<3)
#define BIT_SYSCFG_CHIPINT1 			  	(0x1<<2)
#define BIT_SYSCFG_CHIPINT2 			  	(0x1<<1)
#define BIT_SYSCFG_CHIPINT3 			  	(0x1)

// ESR2 PENDING BIT                     
#define BIT_EDMA3_TC1_TCERRINT 				(0x1<<31)
#define BIT_EMAC_C0RXTHRESH 			    (0x1<<30)
#define BIT_EMAC_C0RX 					    (0x1<<29)
#define BIT_EMAC_C0TX 					    (0x1<<28)
#define BIT_EMAC_C0MISC 				    (0x1<<27)
#define BIT_EMAC_C1RXTHRESH 			    (0x1<<26)
#define BIT_EMAC_C1RX 					    (0x1<<25)
#define BIT_EMAC_C1TX 					    (0x1<<24)
#define BIT_EMAC_C1MISC 				    (0x1<<23)
#define BIT_EMIF_MEMERR 				    (0x1<<22)
#define BIT_GPIO_B0INT 					    (0x1<<21)
#define BIT_GPIO_B1INT 					    (0x1<<20)
#define BIT_GPIO_B2INT 					    (0x1<<19)
#define BIT_GPIO_B3INT 					    (0x1<<18)
#define BIT_GPIO_B4INT 					    (0x1<<17)
#define BIT_GPIO_B5INT 					    (0x1<<16)
#define BIT_GPIO_B6INT 					    (0x1<<15)
#define BIT_GPIO_B7INT 					    (0x1<<14)
#define BIT_Reserved50					    (0x1<<13)
#define BIT_IIC1_INT 					    (0x1<<12)
#define BIT_LCDC_INT 					    (0x1<<11)
#define BIT_UART_INT1 					    (0x1<<10)
#define BIT_MCASP_INT 					    (0x1<<9) 
#define BIT_PSC1_ALLINT 				    (0x1<<8) 
#define BIT_SPI1_INT 					    (0x1<<7) 
#define BIT_UHPI_ARMINT 				    (0x1<<6) 
#define BIT_USB0_INT 					    (0x1<<5) 
#define BIT_USB1_HCINT 					    (0x1<<4) 
#define BIT_USB1_RWAKEUP 				    (0x1<<3) 
#define BIT_UART2_INT 					    (0x1<<2) 
#define BIT_Reserved62					    (0x1<<1) 
#define BIT_EHRPWM0 						(0x1)    

// ESR3 PENDING BIT                     
//#define BIT_Reserved		                (0x1<<31)
//#define BIT_Reserved		                (0x1<<30)
//#define BIT_Reserved		                (0x1<<29)
//#define BIT_Reserved		                (0x1<<28)
#define BIT_EHRPWM0TZ 				        (0x1<<27)
#define BIT_EHRPWM1 				        (0x1<<26)
#define BIT_EHRPWM1TZ 				        (0x1<<25)
#define BIT_EHRPWM2 				        (0x1<<24)
#define BIT_EHRPWM2TZ 				        (0x1<<23)
#define BIT_ECAP0 					        (0x1<<22)
#define BIT_ECAP1 			   		        (0x1<<21)
#define BIT_ECAP2 			   		        (0x1<<20)
#define BIT_EQEP0 			   		        (0x1<<19)
#define BIT_EQEP1 			   		        (0x1<<18)
#define BIT_T64P0_CMPINT0      		        (0x1<<17)
#define BIT_T64P0_CMPINT1      		        (0x1<<16)
#define BIT_T64P0_CMPINT2      		        (0x1<<15)
#define BIT_T64P0_CMPINT3      		        (0x1<<14)
#define BIT_T64P0_CMPINT4      		        (0x1<<13)
#define BIT_T64P0_CMPINT5      		        (0x1<<12)
#define BIT_T64P0_CMPINT6      		        (0x1<<11)
#define BIT_T64P0_CMPINT7      		        (0x1<<10)
#define BIT_T64P1_CMPINT0      		        (0x1<<9) 
#define BIT_T64P1_CMPINT1      		        (0x1<<8) 
#define BIT_T64P1_CMPINT2      		        (0x1<<7) 
#define BIT_T64P1_CMPINT3      		        (0x1<<6) 
#define BIT_T64P1_CMPINT4      		        (0x1<<5) 
#define BIT_T64P1_CMPINT5   		        (0x1<<4) 
#define BIT_T64P1_CMPINT6   		        (0x1<<3) 
#define BIT_T64P1_CMPINT7   		        (0x1<<2) 
#define BIT_ARMCLKSTOPREQ   		        (0x1<<1) 
//#define BIT_Reserved		                (0x1)    

#define INT_LVL_COMMTX 				0		//ARM                                                                         
#define INT_LVL_COMMRX 				1		//ARM                                                                         
#define INT_LVL_NINT 					2		//ARM                                                                           
#define INT_LVL_Reserved3				3		//Reserved                                                                         
#define INT_LVL_Reserved4				4		//Reserved                                                                         
#define INT_LVL_Reserved5				5		//Reserved                                                                         
#define INT_LVL_Reserved6				6		//Reserved                                                                         
#define INT_LVL_Reserved7				7		//Reserved                                                                         
#define INT_LVL_Reserved8				8		//Reserved                                                                         
#define INT_LVL_Reserved9				9		//Reserved                                                                         
#define INT_LVL_Reserved10				10  	//Reserved                                                                        
#define INT_LVL_EDMA3_CC0_CCINT 		11  	//EDMA CC Region 0                                                  
#define INT_LVL_EDMA3_CC0_CCERRINT 	12  	//EDMA CC                                                        
#define INT_LVL_EDMA3_TC0_TCERRINT 	13  	//EDMA TC0                                                       
#define INT_LVL_EMIFA_INT 				14  	//EMIFA                                                                   
#define INT_LVL_IIC0_INT 				15  	//I2C0                                                                     
#define INT_LVL_MMCSD_INT0 			16  	//MMCSD                                                                  
#define INT_LVL_MMCSD_INT1 			17  	//MMCSD                                                                  
#define INT_LVL_PSC0_ALLINT 			18  	//PSC0                                                                  
#define INT_LVL_RTC_IRQS    			19  	//RTC                                                                 
#define INT_LVL_SPI0_INT 				20  	//SPI0                                                                     
#define INT_LVL_T64P0_TINT12 			21  	//Timer64P0 Interrupt 12                                               
#define INT_LVL_T64P0_TINT34 			22  	//Timer64P0 Interrupt 34                                               
#define INT_LVL_T64P1_TINT12 			23  	//Timer64P1 Interrupt 12                                               
#define INT_LVL_T64P1_TINT34 			24  	//Timer64P1 Interrupt 34                                               
#define INT_LVL_UART0_INT 				25  	//UART0                                                                   
#define INT_LVL_Reserved26          	26      //Reserved                                              
#define INT_LVL_PROTERR 				27  	//SYSCFG Protection Shared Interrupt                                        
#define INT_LVL_SYSCFG_CHIPINT0 		28  	//SYSCFG CHIPSIG Register                                           
#define INT_LVL_SYSCFG_CHIPINT1 		29  	//SYSCFG CHIPSIG Register                                           
#define INT_LVL_SYSCFG_CHIPINT2 		30  	//SYSCFG CHIPSIG Register                                           
#define INT_LVL_SYSCFG_CHIPINT3 		31  	//SYSCFG CHIPSIG Register                                           
#define INT_LVL_EDMA3_TC1_TCERRINT 	32  	//EDMA TC1                                                       
#define INT_LVL_EMAC_C0RXTHRESH 		33  	//EMAC - Core 0 Receive Threshold Interrupt                         
#define INT_LVL_EMAC_C0RX 				34  	//EMAC - Core 0 Receive Interrupt                                         
#define INT_LVL_EMAC_C0TX 				35  	//EMAC - Core 0 Transmit Interrupt                                        
#define INT_LVL_EMAC_C0MISC 			36  	//EMAC - Core 0 Miscellaneous Interrupt                                 
#define INT_LVL_EMAC_C1RXTHRESH 		37  	//EMAC - Core 1 Receive Threshold Interrupt                         
#define INT_LVL_EMAC_C1RX 				38  	//EMAC - Core 1 Receive Interrupt                                         
#define INT_LVL_EMAC_C1TX 				39  	//EMAC - Core 1 Transmit Interrupt                                        
#define INT_LVL_EMAC_C1MISC 			40  	//EMAC - Core 1 Miscellaneous Interrupt   
#define INT_LVL_DDR2_DCCI				41		//DDR2 - Controller Interrupt
//#define INT_LVL_EMIF_MEMERR 			41  	//EMIFB                                                                 
#define INT_LVL_GPIO_B0INT 			42  	//GPIO Bank 0 Interrupt                                                  
#define INT_LVL_GPIO_B1INT 			43  	//GPIO Bank 1 Interrupt                                                  
#define INT_LVL_GPIO_B2INT 			44  	//GPIO Bank 2 Interrupt                                                  
#define INT_LVL_GPIO_B3INT 			45  	//GPIO Bank 3 Interrupt                                                  
#define INT_LVL_GPIO_B4INT 			46  	//GPIO Bank 4 Interrupt                                                  
#define INT_LVL_GPIO_B5INT 			47  	//GPIO Bank 5 Interrupt                                                  
#define INT_LVL_GPIO_B6INT 			48  	//GPIO Bank 6 Interrupt                                                  
#define INT_LVL_GPIO_B7INT 			49  	//GPIO Bank 7 Interrupt      
#define INT_LVL_GPIO_B8INT 			50  	//GPIO Bank 8 Interrupt                                                  
#define INT_LVL_IIC1_INT 				51  	//I2C1                                                                     
#define INT_LVL_LCDC_INT 				52  	//LCD Controller                                                           
#define INT_LVL_UART1_INT	 			53  	//UART1                                                                   
#define INT_LVL_MCASP_INT 				54  	//McASP0, 1, 2 Combined RX / TX Interrupts                                
#define INT_LVL_PSC1_ALLINT 			55  	//PSC1                                                                  
#define INT_LVL_SPI1_INT 				56  	//SPI1                                                                     
#define INT_LVL_UHPI_ARMINT	 		57  	//HPI Arm Interrupt                                                     
#define INT_LVL_USB0_INT 				58  	//USB0 Interrupt                                                           
#define INT_LVL_USB1_HCINT 			59  	//USB1 OHCI Host Controller Interrupt                                    
#define INT_LVL_USB1_RWAKEUP 			60  	//USB1 Remote Wakeup Interrupt                                         
#define INT_LVL_UART2_INT 				61  	//UART2                                                                   
#define INT_LVL_Reserved62				62  	//Reserved                                                                        
#define INT_LVL_EHRPWM0 				63  	//HiResTimer / PWM0 Interrupt                                               
#define INT_LVL_EHRPWM0TZ 				64  	//HiResTimer / PWM0 Trip Zone Interrupt                                   
#define INT_LVL_EHRPWM1 				65  	//HiResTimer / PWM1 Interrupt                                               
#define INT_LVL_EHRPWM1TZ 				66  	//HiResTimer / PWM1 Trip Zone Interrupt                                   
//#define INT_LVL_EHRPWM2 				67  	//HiResTimer / PWM2 Interrupt                                               
//#define INT_LVL_EHRPWM2TZ 				68  	//HiResTimer / PWM2 Trip Zone Interrupt       
#define INT_LVL_SATA_INT				67
#define INT_LVL_T64P2_ALL				68
#define INT_LVL_ECAP0 					69  	//ECAP0                                                                       
#define INT_LVL_ECAP1 					70  	//ECAP1                                                                       
#define INT_LVL_ECAP2 					71  	//ECAP2                                                                       
//#define INT_LVL_EQEP0 					72  	//EQEP0                                                                       
//#define INT_LVL_EQEP1 					73  	//EQEP1      
#define INT_LVL_MMCSD1_INT0				72
#define INT_LVL_MMCSD1_INT1				73
#define INT_LVL_T64P0_CMPINT0 			74  	//Timer64P0 - Compare 0                                               
#define INT_LVL_T64P0_CMPINT1 			75  	//Timer64P0 - Compare 1                                               
#define INT_LVL_T64P0_CMPINT2 			76  	//Timer64P0 - Compare 2                                               
#define INT_LVL_T64P0_CMPINT3 			77  	//Timer64P0 - Compare 3                                               
#define INT_LVL_T64P0_CMPINT4 			78  	//Timer64P0 - Compare 4                                               
#define INT_LVL_T64P0_CMPINT5 			79  	//Timer64P0 - Compare 5                                               
#define INT_LVL_T64P0_CMPINT6 			80  	//Timer64P0 - Compare 6                                               
#define INT_LVL_T64P0_CMPINT7 			81  	//Timer64P0 - Compare 7                                               
#define INT_LVL_T64P1_CMPINT0 			82  	//Timer64P1 - Compare 0                                               
#define INT_LVL_T64P1_CMPINT1 			83  	//Timer64P1 - Compare 1                                               
#define INT_LVL_T64P1_CMPINT2 			84  	//Timer64P1 - Compare 2                                               
#define INT_LVL_T64P1_CMPINT3 			85  	//Timer64P1 - Compare 3                                               
#define INT_LVL_T64P1_CMPINT4 			86  	//Timer64P1 - Compare 4                                               
#define INT_LVL_T64P1_CMPINT5 			87  	//Timer64P1 - Compare 5                                               
#define INT_LVL_T64P1_CMPINT6 			88  	//Timer64P1 - Compare 6                                               
#define INT_LVL_T64P1_CMPINT7 			89  	//Timer64P1 - Compare 7                                               
#define	INT_LVL_ARMCLKSTOPREQ 			90  	//PSC0    
#define INT_LVL_UPP_ALLINT				91
#define INT_LVL_VPIF_ALLINT				92
#define INT_LVL_EDMA31_CC0_INT0			93
#define INT_LVL_EDMA31_CC0_ERRINT			94
#define INT_LVL_EDMA31_TC0_ERRINT			95
#define INT_LVL_T64P3_ALL					96
#define INT_LVL_MCBSP0_RINT				97
#define INT_LVL_MCBSP0_XINT				98
#define INT_LVL_MCBSP1_RINT				99
#define INT_LVL_MCBSP1_XINT				100

#define INT_VEC_COMMTX 				IVEC_TO_INUM(INT_LVL_COMMTX 			)	
#define INT_VEC_COMMRX 				IVEC_TO_INUM(INT_LVL_COMMRX 			)
#define INT_VEC_NINT 					IVEC_TO_INUM(INT_LVL_NINT 				)
#define INT_VEC_Reserved3				IVEC_TO_INUM(INT_LVL_Reserved3			)
#define INT_VEC_Reserved4				IVEC_TO_INUM(INT_LVL_Reserved4			)
#define INT_VEC_Reserved5				IVEC_TO_INUM(INT_LVL_Reserved5			)
#define INT_VEC_Reserved6				IVEC_TO_INUM(INT_LVL_Reserved6			)
#define INT_VEC_Reserved7				IVEC_TO_INUM(INT_LVL_Reserved7			)
#define INT_VEC_Reserved8				IVEC_TO_INUM(INT_LVL_Reserved8			)
#define INT_VEC_Reserved9				IVEC_TO_INUM(INT_LVL_Reserved9			)
#define INT_VEC_Reserved10				IVEC_TO_INUM(INT_LVL_Reserved10		)
#define INT_VEC_EDMA3_CC0_CCINT 		IVEC_TO_INUM(INT_LVL_EDMA3_CC0_CCINT 	)
#define INT_VEC_EDMA3_CC0_CCERRINT 	IVEC_TO_INUM(INT_LVL_EDMA3_CC0_CCERRINT )
#define INT_VEC_EDMA3_TC0_TCERRINT 	IVEC_TO_INUM(INT_LVL_EDMA3_TC0_TCERRINT )
#define INT_VEC_EMIFA_INT 				IVEC_TO_INUM(INT_LVL_EMIFA_INT 		)
#define INT_VEC_IIC0_INT 				IVEC_TO_INUM(INT_LVL_IIC0_INT 			)
#define INT_VEC_MMCSD_INT0 			IVEC_TO_INUM(INT_LVL_MMCSD_INT0 		)
#define INT_VEC_MMCSD_INT1 			IVEC_TO_INUM(INT_LVL_MMCSD_INT1 		)
#define INT_VEC_PSC0_ALLINT 			IVEC_TO_INUM(INT_LVL_PSC0_ALLINT 		)
#define INT_VEC_RTC_IRQS    			IVEC_TO_INUM(INT_LVL_RTC_IRQS    		)
#define INT_VEC_SPI0_INT 				IVEC_TO_INUM(INT_LVL_SPI0_INT 			)
#define INT_VEC_T64P0_TINT12 			IVEC_TO_INUM(INT_LVL_T64P0_TINT12 		)
#define INT_VEC_T64P0_TINT34 			IVEC_TO_INUM(INT_LVL_T64P0_TINT34 		)
#define INT_VEC_T64P1_TINT12 			IVEC_TO_INUM(INT_LVL_T64P1_TINT12 		)
#define INT_VEC_T64P1_TINT34 			IVEC_TO_INUM(INT_LVL_T64P1_TINT34 		)
#define INT_VEC_UART0_INT 				IVEC_TO_INUM(INT_LVL_UART0_INT 		)
#define INT_VEC_Reserved26         	IVEC_TO_INUM(INT_LVL_Reserved26         )
#define INT_VEC_PROTERR 				IVEC_TO_INUM(INT_LVL_PROTERR 			)
#define INT_VEC_SYSCFG_CHIPINT0 		IVEC_TO_INUM(INT_LVL_SYSCFG_CHIPINT0 	)
#define INT_VEC_SYSCFG_CHIPINT1 		IVEC_TO_INUM(INT_LVL_SYSCFG_CHIPINT1 	)
#define INT_VEC_SYSCFG_CHIPINT2 		IVEC_TO_INUM(INT_LVL_SYSCFG_CHIPINT2 	)
#define INT_VEC_SYSCFG_CHIPINT3 		IVEC_TO_INUM(INT_LVL_SYSCFG_CHIPINT3 	)
#define INT_VEC_EDMA3_TC1_TCERRINT 	IVEC_TO_INUM(INT_LVL_EDMA3_TC1_TCERRINT )
#define INT_VEC_EMAC_C0RXTHRESH 		IVEC_TO_INUM(INT_LVL_EMAC_C0RXTHRESH 	)
#define INT_VEC_EMAC_C0RX 				IVEC_TO_INUM(INT_LVL_EMAC_C0RX 		)
#define INT_VEC_EMAC_C0TX 				IVEC_TO_INUM(INT_LVL_EMAC_C0TX 		)
#define INT_VEC_EMAC_C0MISC 			IVEC_TO_INUM(INT_LVL_EMAC_C0MISC 		)
#define INT_VEC_EMAC_C1RXTHRESH 		IVEC_TO_INUM(INT_LVL_EMAC_C1RXTHRESH 	)
#define INT_VEC_EMAC_C1RX 				IVEC_TO_INUM(INT_LVL_EMAC_C1RX 		)
#define INT_VEC_EMAC_C1TX 				IVEC_TO_INUM(INT_LVL_EMAC_C1TX 		)
#define INT_VEC_EMAC_C1MISC 			IVEC_TO_INUM(INT_LVL_EMAC_C1MISC 		)
//#define INT_VEC_EMIF_MEMERR 			IVEC_TO_INUM(INT_LVL_EMIF_MEMERR 		)
#define INT_VEC_DDR2_DCCI				IVEC_TO_INUM(INT_LVL_DDR2_DCCI		)
#define INT_VEC_GPIO_B0INT 			IVEC_TO_INUM(INT_LVL_GPIO_B0INT 		)
#define INT_VEC_GPIO_B1INT 			IVEC_TO_INUM(INT_LVL_GPIO_B1INT 		)
#define INT_VEC_GPIO_B2INT 			IVEC_TO_INUM(INT_LVL_GPIO_B2INT 		)
#define INT_VEC_GPIO_B3INT 			IVEC_TO_INUM(INT_LVL_GPIO_B3INT 		)
#define INT_VEC_GPIO_B4INT 			IVEC_TO_INUM(INT_LVL_GPIO_B4INT 		)
#define INT_VEC_GPIO_B5INT 			IVEC_TO_INUM(INT_LVL_GPIO_B5INT 		)
#define INT_VEC_GPIO_B6INT 			IVEC_TO_INUM(INT_LVL_GPIO_B6INT 		)
#define INT_VEC_GPIO_B7INT 			IVEC_TO_INUM(INT_LVL_GPIO_B7INT 		)
#define INT_VEC_GPIO_B8INT			IVEC_TO_INUM(INT_LVL_GPIO_B8INT)
//#define INT_VEC_Reserved50				IVEC_TO_INUM(INT_LVL_Reserved50		)
#define INT_VEC_IIC1_INT 				IVEC_TO_INUM(INT_LVL_IIC1_INT 			)
#define INT_VEC_LCDC_INT 				IVEC_TO_INUM(INT_LVL_LCDC_INT 			)
#define INT_VEC_UART1_INT 				IVEC_TO_INUM(INT_LVL_UART1_INT		)
#define INT_VEC_MCASP_INT 				IVEC_TO_INUM(INT_LVL_MCASP_INT 		)
#define INT_VEC_PSC1_ALLINT 			IVEC_TO_INUM(INT_LVL_PSC1_ALLINT 		)
#define INT_VEC_SPI1_INT 				IVEC_TO_INUM(INT_LVL_SPI1_INT 			)
#define INT_VEC_UHPI_ARMINT	 		IVEC_TO_INUM(INT_LVL_UHPI_ARMINT	 	)
#define INT_VEC_USB0_INT 				IVEC_TO_INUM(INT_LVL_USB0_INT 			)
#define INT_VEC_USB1_HCINT 			IVEC_TO_INUM(INT_LVL_USB1_HCINT 		)
#define INT_VEC_USB1_RWAKEUP 			IVEC_TO_INUM(INT_LVL_USB1_RWAKEUP 		)
#define INT_VEC_UART2_INT 				IVEC_TO_INUM(INT_LVL_UART2_INT 		)
#define INT_VEC_Reserved62				IVEC_TO_INUM(INT_LVL_Reserved62		)
#define INT_VEC_EHRPWM0 				IVEC_TO_INUM(INT_LVL_EHRPWM0 			)
#define INT_VEC_EHRPWM0TZ 				IVEC_TO_INUM(INT_LVL_EHRPWM0TZ 		)
#define INT_VEC_EHRPWM1 				IVEC_TO_INUM(INT_LVL_EHRPWM1 			)
#define INT_VEC_EHRPWM1TZ 				IVEC_TO_INUM(INT_LVL_EHRPWM1TZ 		)
#define INT_VEC_SATA_INT				IVEC_TO_INUM(INT_LVL_SATA_INT		)
#define INT_VEC_T64P2_ALL				IVEC_TO_INUM(INT_LVL_T64P2_ALL		)
//#define INT_VEC_EHRPWM2 				IVEC_TO_INUM(INT_LVL_EHRPWM2 			)
//#define INT_VEC_EHRPWM2TZ 				IVEC_TO_INUM(INT_LVL_EHRPWM2TZ 		)
#define INT_VEC_ECAP0 					IVEC_TO_INUM(INT_LVL_ECAP0 			)
#define INT_VEC_ECAP1 					IVEC_TO_INUM(INT_LVL_ECAP1 			)
#define INT_VEC_ECAP2 					IVEC_TO_INUM(INT_LVL_ECAP2 			)
#define INT_VEC_MMCSD1_INT0			IVEC_TO_INUM(INT_LVL_MMCSD1_INT0	)
#define INT_VEC_MMCSD1_INT1			IVEC_TO_INUM(INT_LVL_MMCSD1_INT1	)
//#define INT_VEC_EQEP0 					IVEC_TO_INUM(INT_LVL_EQEP0 			)
//#define INT_VEC_EQEP1 					IVEC_TO_INUM(INT_LVL_EQEP1 			)
#define INT_VEC_T64P0_CMPINT0 			IVEC_TO_INUM(INT_LVL_T64P0_CMPINT0 	)
#define INT_VEC_T64P0_CMPINT1 			IVEC_TO_INUM(INT_LVL_T64P0_CMPINT1 	)
#define INT_VEC_T64P0_CMPINT2 			IVEC_TO_INUM(INT_LVL_T64P0_CMPINT2 	)
#define INT_VEC_T64P0_CMPINT3 			IVEC_TO_INUM(INT_LVL_T64P0_CMPINT3 	)
#define INT_VEC_T64P0_CMPINT4 			IVEC_TO_INUM(INT_LVL_T64P0_CMPINT4 	)
#define INT_VEC_T64P0_CMPINT5 			IVEC_TO_INUM(INT_LVL_T64P0_CMPINT5 	)
#define INT_VEC_T64P0_CMPINT6 			IVEC_TO_INUM(INT_LVL_T64P0_CMPINT6 	)
#define INT_VEC_T64P0_CMPINT7 			IVEC_TO_INUM(INT_LVL_T64P0_CMPINT7 	)
#define INT_VEC_T64P1_CMPINT0 			IVEC_TO_INUM(INT_LVL_T64P1_CMPINT0 	)
#define INT_VEC_T64P1_CMPINT1 			IVEC_TO_INUM(INT_LVL_T64P1_CMPINT1 	)
#define INT_VEC_T64P1_CMPINT2 			IVEC_TO_INUM(INT_LVL_T64P1_CMPINT2 	)
#define INT_VEC_T64P1_CMPINT3 			IVEC_TO_INUM(INT_LVL_T64P1_CMPINT3 	)
#define INT_VEC_T64P1_CMPINT4 			IVEC_TO_INUM(INT_LVL_T64P1_CMPINT4 	)
#define INT_VEC_T64P1_CMPINT5 			IVEC_TO_INUM(INT_LVL_T64P1_CMPINT5 	)
#define INT_VEC_T64P1_CMPINT6 			IVEC_TO_INUM(INT_LVL_T64P1_CMPINT6 	)
#define INT_VEC_T64P1_CMPINT7 			IVEC_TO_INUM(INT_LVL_T64P1_CMPINT7 	)
#define	INT_VEC_ARMCLKSTOPREQ 			IVEC_TO_INUM(INT_LVL_ARMCLKSTOPREQ 	)
#define INT_VEC_UPP_ALLINT				IVEC_TO_INUM(INT_LVL_UPP_ALLINT		)
#define INT_VEC_VPIF_ALLINT				IVEC_TO_INUM(INT_LVL_VPIF_ALLINT	)
#define INT_VEC_EDMA31_CC0_INT0			IVEC_TO_INUM(INT_LVL_EDMA31_CC0_INT0)
#define INT_VEC_EDMA31_CC0_ERRINT			IVEC_TO_INUM(INT_LVL_EDMA31_CC0_ERRINT	)
#define INT_VEC_EDMA31_TC0_ERRINT			IVEC_TO_INUM(INT_LVL_EDMA31_TC0_ERRINT	)
#define INT_VEC_T64P3_ALL					IVEC_TO_INUM(INT_LVL_T64P3_ALL		)
#define INT_VEC_MCBSP0_RINT				IVEC_TO_INUM(INT_LVL_MCBSP0_RINT	)
#define INT_VEC_MCBSP0_XINT				IVEC_TO_INUM(INT_LVL_MCBSP0_XINT	)
#define INT_VEC_MCBSP1_RINT				IVEC_TO_INUM(INT_LVL_MCBSP1_RINT	)
#define INT_VEC_MCBSP1_XINT				IVEC_TO_INUM(INT_LVL_MCBSP1_XINT	)

#define C6748_INTNUMLEVELS		101
#define BIT_ALLMSK 				( 0x0ffffffff )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  PLL0 Controller                                                         *
 *      Generates DSP, ARM clocks                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define PLL0_BASE   	0x01C11000   							/*SYSTEM PLL BASE ADDRESS*/

#define PLL0_PID      	 (PLL0_BASE + 0x00)		/*PID*/
#define PLL0_FUSERR   	 (PLL0_BASE + 0xE0)		/*x*FuseFarm Error Reg*/
#define PLL0_RSTYPE	     (PLL0_BASE + 0xE4)		/*Reset Type status Reg*/
#define PLL0_PLLCTL      (PLL0_BASE + 0x100) 	/*PLL Control Register*/
#define PLL0_OCSEL       (PLL0_BASE + 0x104)	/*OBSCLK Select Register*/
#define PLL0_SECCTL      (PLL0_BASE + 0x108)	/*PLL Secondary Control Register*/
#define PLL0_PLLM        (PLL0_BASE + 0x110)    /*PLL Multiplier*/	
#define PLL0_PREDIV      (PLL0_BASE + 0x114)    /*Pre divider*/	
#define PLL0_PLLDIV1     (PLL0_BASE + 0x118)    /*Diveder-1*/	
#define PLL0_PLLDIV2     (PLL0_BASE + 0x11C)    /*Diveder-2*/	
#define PLL0_PLLDIV3     (PLL0_BASE + 0x120)    /*Diveder-3*/	
#define PLL0_OSCDIV1     (PLL0_BASE + 0x124)    /*Oscilator Divider*/	
#define PLL0_POSTDIV     (PLL0_BASE + 0x128)    /*Post Divider*/	
#define PLL0_BPDIV       (PLL0_BASE + 0x12C)	/*Bypass Divider*/
#define PLL0_WAKEUP      (PLL0_BASE + 0x130)	/*Wakeup Reg*/
#define PLL0_PLLCMD      (PLL0_BASE + 0x138)	/*Command Reg*/
#define PLL0_PLLSTAT     (PLL0_BASE + 0x13C)	/*Status Reg*/
#define PLL0_ALNCTL      (PLL0_BASE + 0x140)	/*Clock Align Control Reg*/
#define PLL0_DCHANGE     (PLL0_BASE + 0x144)	/*PLLDIV Ratio Chnage status*/
#define PLL0_CKEN        (PLL0_BASE + 0x148)	/*Clock Enable Reg*/
#define PLL0_CKSTAT      (PLL0_BASE + 0x14C)	/*Clock Status Reg*/
#define PLL0_SYSTAT      (PLL0_BASE + 0x150)	/*Sysclk status reg*/
#define PLL0_PLLDIV4     (PLL0_BASE + 0x160)	/*Divider 4*/
#define PLL0_PLLDIV5     (PLL0_BASE + 0x164)	/*Divider 5*/
#define PLL0_PLLDIV6     (PLL0_BASE + 0x168)	/*Divider 6*/
#define PLL0_PLLDIV7     (PLL0_BASE + 0x16C)	/*Divider 7*/
#define PLL0_PLLDIV8     (PLL0_BASE + 0x170)	/*Divider 8*/
#define PLL0_PLLDIV9     (PLL0_BASE + 0x174)	/*Divider 9*/
#define PLL0_PLLDIV10    (PLL0_BASE + 0x178)	/*Divider 10*/
#define PLL0_PLLDIV11    (PLL0_BASE + 0x17C)	/*Divider 11*/
#define PLL0_PLLDIV12    (PLL0_BASE + 0x180)	/*Divider 12*/
#define PLL0_PLLDIV13    (PLL0_BASE + 0x184)	/*Divider 13*/
#define PLL0_PLLDIV14    (PLL0_BASE + 0x188)	/*Divider 14*/
#define PLL0_PLLDIV15    (PLL0_BASE + 0x18C)	/*Divider 15*/
#define PLL0_PLLDIV16    (PLL0_BASE + 0x190)	/*Divider 16*/
#define PLLEN_MUX_SWITCH  4 
#define PLL_LOCK_TIME_CNT 2400
/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Timer Controller                                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define TIMER0_BASE         0x01C20000
#define TIMER0_EMUMGT      ( TIMER0_BASE + 0x04 )
#define TIMER0_GPINTGPEN   ( TIMER0_BASE + 0x08 )
#define TIMER0_GPDATGPDIR  ( TIMER0_BASE + 0x0C )
#define TIMER0_TIM12       ( TIMER0_BASE + 0x10 )
#define TIMER0_TIM34       ( TIMER0_BASE + 0x14 )
#define TIMER0_PRD12       ( TIMER0_BASE + 0x18 )
#define TIMER0_PRD34       ( TIMER0_BASE + 0x1C )
#define TIMER0_TCR         ( TIMER0_BASE + 0x20 )
#define TIMER0_TGCR        ( TIMER0_BASE + 0x24 )
#define TIMER0_INTCTLSTAT  ( TIMER0_BASE + 0x44 )

#define TIMER1_BASE         0x01C21000
#define TIMER1_EMUMGT      ( TIMER1_BASE + 0x04 )
#define TIMER1_GPINTGPEN   ( TIMER1_BASE + 0x08 )
#define TIMER1_GPDATGPDIR  ( TIMER1_BASE + 0x0C )
#define TIMER1_TIM12       ( TIMER1_BASE + 0x10 )
#define TIMER1_TIM34       ( TIMER1_BASE + 0x14 )
#define TIMER1_PRD12       ( TIMER1_BASE + 0x18 )
#define TIMER1_PRD34       ( TIMER1_BASE + 0x1C )
#define TIMER1_TCR         ( TIMER1_BASE + 0x20 )
#define TIMER1_TGCR        ( TIMER1_BASE + 0x24 )
#define TIMER1_INTCTLSTAT  ( TIMER1_BASE + 0x44 )

#define TIMER2_BASE         0x01F0C000
#define TIMER2_EMUMGT      ( TIMER2_BASE + 0x04 )
#define TIMER2_GPINTGPEN   ( TIMER2_BASE + 0x08 )
#define TIMER2_GPDATGPDIR  ( TIMER2_BASE + 0x0C )
#define TIMER2_TIM12       ( TIMER2_BASE + 0x10 )
#define TIMER2_TIM34       ( TIMER2_BASE + 0x14 )
#define TIMER2_PRD12       ( TIMER2_BASE + 0x18 )
#define TIMER2_PRD34       ( TIMER2_BASE + 0x1C )
#define TIMER2_TCR         ( TIMER2_BASE + 0x20 )
#define TIMER2_TGCR        ( TIMER2_BASE + 0x24 )
#define TIMER2_REL12       ( TIMER2_BASE + 0x34 )
#define TIMER2_INTCTLSTAT  ( TIMER2_BASE + 0x44 )
#define TIMER2_CMP0		   ( TIMER2_BASE + 0x60 )
#define TIMER2_CMP1		   ( TIMER2_BASE + 0x64 )
#define TIMER2_CMP2		   ( TIMER2_BASE + 0x68 )
#define TIMER2_CMP3		   ( TIMER2_BASE + 0x6C )
#define TIMER2_CMP4		   ( TIMER2_BASE + 0x70 )
#define TIMER2_CMP5		   ( TIMER2_BASE + 0x74 )
#define TIMER2_CMP6		   ( TIMER2_BASE + 0x78 )
#define TIMER2_CMP7		   ( TIMER2_BASE + 0x7C )









#define TIMER3_BASE         0x01F0D000
#define TIMER3_EMUMGT      ( TIMER3_BASE + 0x04 )
#define TIMER3_GPINTGPEN   ( TIMER3_BASE + 0x08 )
#define TIMER3_GPDATGPDIR  ( TIMER3_BASE + 0x0C )
#define TIMER3_TIM12       ( TIMER3_BASE + 0x10 )
#define TIMER3_TIM34       ( TIMER3_BASE + 0x14 )
#define TIMER3_PRD12       ( TIMER3_BASE + 0x18 )
#define TIMER3_PRD34       ( TIMER3_BASE + 0x1C )
#define TIMER3_TCR         ( TIMER3_BASE + 0x20 )
#define TIMER3_TGCR        ( TIMER3_BASE + 0x24 )
#define TIMER3_INTCTLSTAT  ( TIMER3_BASE + 0x44 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  UART Controller                                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define UART0_BASE          0x01C42000
#define UART0_RBR          ( UART0_BASE + 0x00 )
#define UART0_THR          ( UART0_BASE + 0x00 )
#define UART0_IER          ( UART0_BASE + 0x04 )
#define UART0_IIR          ( UART0_BASE + 0x08 )
#define UART0_FCR          ( UART0_BASE + 0x08 )
#define UART0_LCR          ( UART0_BASE + 0x0C )
#define UART0_MCR          ( UART0_BASE + 0x10 )
#define UART0_LSR          ( UART0_BASE + 0x14 )
#define UART0_DLL          ( UART0_BASE + 0x20 )
#define UART0_DLH          ( UART0_BASE + 0x24 )
#define UART0_PID1         ( UART0_BASE + 0x28 )
#define UART0_PID2         ( UART0_BASE + 0x2C )
#define UART0_PWREMU_MGMT  ( UART0_BASE + 0x30 )

#define UART1_BASE          0x01D0C000
#define UART1_RBR          ( UART1_BASE + 0x00 )
#define UART1_THR          ( UART1_BASE + 0x00 )
#define UART1_IER          ( UART1_BASE + 0x04 )
#define UART1_IIR          ( UART1_BASE + 0x08 )
#define UART1_FCR          ( UART1_BASE + 0x08 )
#define UART1_LCR          ( UART1_BASE + 0x0C )
#define UART1_MCR          ( UART1_BASE + 0x10 )
#define UART1_LSR          ( UART1_BASE + 0x14 )
#define UART1_DLL          ( UART1_BASE + 0x20 )
#define UART1_DLH          ( UART1_BASE + 0x24 )
#define UART1_PID1         ( UART1_BASE + 0x28 )
#define UART1_PID2         ( UART1_BASE + 0x2C )
#define UART1_PWREMU_MGMT  ( UART1_BASE + 0x30 )

#define UART2_BASE          0x01D0D000
#define UART2_RBR          ( UART2_BASE + 0x00 )
#define UART2_THR          ( UART2_BASE + 0x00 )
#define UART2_IER          ( UART2_BASE + 0x04 )
#define UART2_IIR          ( UART2_BASE + 0x08 )
#define UART2_FCR          ( UART2_BASE + 0x08 )
#define UART2_LCR          ( UART2_BASE + 0x0C )
#define UART2_MCR          ( UART2_BASE + 0x10 )
#define UART2_LSR          ( UART2_BASE + 0x14 )
#define UART2_DLL          ( UART2_BASE + 0x20 )
#define UART2_DLH          ( UART2_BASE + 0x24 )
#define UART2_PID1         ( UART2_BASE + 0x28 )
#define UART2_PID2         ( UART2_BASE + 0x2C )
#define UART2_PWREMU_MGMT  ( UART2_BASE + 0x30 )

#define UART_RBR                ( 0x00 )
#define UART_THR                ( 0x00 )
#define UART_IER                ( 0x04 )
#define UART_IIR                ( 0x08 )
#define UART_FCR                ( 0x08 )
#define UART_LCR                ( 0x0C )
#define UART_MCR                ( 0x10 )
#define UART_LSR                ( 0x14 )
#define UART_DLL                ( 0x20 )
#define UART_DLH                ( 0x24 )
#define UART_PID1               ( 0x28 )
#define UART_PID2               ( 0x2C )
#define UART_PWREMU_MGMT        ( 0x30 )
#define UART_REG_ADDR_INTERVAL  ( 4 )

#define LOCAL_RAM_BASE             (0XFFFF0000)
#define LOCAL_RAM_SIZE             (SZ_8K)

#define INCTLR_REG_BASE            (0XFFFEE000)
#define INCTLR_REG_SIZE            (SZ_8K)

#define LOCAL_ROM_BASE             (0XFFFD0000)
#define LOCAL_ROM_SIZE             (SZ_64K)

#define EMIFB_REG_BASE             (0XB0000000)
#define EMIFB_REG_SIZE             (SZ_32K)

#define SHARE_SDRAM_BASE           (0X80000000)
#define SHARE_SDRAM_SIZE           (SZ_128K)

#define INTERNAL_PERIPHERALS_BASE  (0X01B00000)
#define INTERNAL_PERIPHERALS_SIZE  (0x500000)


/* hardware access methods */
#define C6748_REG_READ(x,result) \
        ((result) = *(volatile unsigned int *)(x))

#define C6748_REG_WRITE(x,data) \
        (*((volatile unsigned int *)(x)) = (data))

//-----------------------------------------------------------------------------
// bit manipulation macros and bitval lookup table declarations.
//-----------------------------------------------------------------------------
#define SETBIT(dest,mask)     (dest |= mask)
#define CLRBIT(dest,mask)     (dest &= ~mask)
#define TGLBIT(dest,mask)     (dest ^= mask)
#define CHKBIT(dest,mask)     (dest & mask)


//-----------------------------------------------------------------------------
// bitmask defines for EMUMGT.
//-----------------------------------------------------------------------------
#define SOFT                  (0x00000002)   // bit 1
//#define FREE                  (0x00000001)   // bit 0

//-----------------------------------------------------------------------------
// Return Error Defines
//-----------------------------------------------------------------------------
#define ERR_NO_ERROR             (0)
#define ERR_FAIL                 (1)
#define ERR_INIT_FAIL            (2)
#define ERR_NO_UI_BOARD          (3)
#define ERR_INVALID_PARAMETER    (4)
#define ERR_TIMEOUT              (5)
#define ERR_UART_RX_FIFO_EMPTY   (6)
#define ERR_SPI_BUS_ERROR        (7)
#define ERR_ENET_LINK_INACTIVE   (8)
#define ERR_ENET_PKT_TOO_LARGE   (9)
#define ERR_ENET_Q_EMPTY         (10)
#define ERR_ENET_RX_ERROR        (11)
#define ERR_FLASH_VERIFY         (12)
#define ERR_MMCSD_TIMEOUT        (13)
#define ERR_NAND_BAD_BLOCK       (14)
#define ERR_UIDB_NUM_DEVICES     (15)    //for UI databus muxing control 
#define ERR_UIDB_INCOMPAT_DEV    (16)
#define ERR_UIDB_INVALID_DEVICE  (17)
//-----------------------------------------------------------------------------
// Utility Print Defines
//-----------------------------------------------------------------------------
#define PRINT_NONE                  (0)
#define PRINT_DURING_VERIFY         (1)
#define PRINT_HEADER                (0)
#define PRINT_CONTINUE              (1)

//-----------------------------------------------------------------------------
// power and sleep config registers
//-----------------------------------------------------------------------------
#define PSC0_REG_BASE         (0x01C10000)
#define PSC1_REG_BASE         (0x01E27000)

//-----------------------------------------------------------------------------
// system config registers
//-----------------------------------------------------------------------------
#define SYSCONFIG_REG_BASE    (0x01C14000)

//-----------------------------------------------------------------------------
// PLL registers
//-----------------------------------------------------------------------------
#define PLL0_REG_BASE         (0x01C11000)
#define PLL1_REG_BASE         (0x01E1A000)

//-----------------------------------------------------------------------------
// DDR registers
//-----------------------------------------------------------------------------
#define DDR_REG_BASE          (0xB0000000)
#define DDR_MEM_BASE          (0xC0000000)
#define DDR_MEM_SIZE          (0x08000000)	// 128MB

//-----------------------------------------------------------------------------
// EMIFA registers
//-----------------------------------------------------------------------------
#define EMIFA_REG_BASE        (0x68000000)

//-----------------------------------------------------------------------------
// GPIO registers
//-----------------------------------------------------------------------------
#define GPIO_REG_BASE         (0x01E26000)
#define GPIO_BANK_OFFSET      (0x28)

#define GPIO_REV              (GPIO_REG_BASE)
//#define GPIO_BINTEN           (GPIO_REG_BASE + 0x08)

#define GPIO_BANK01_BASE      (GPIO_REG_BASE + 0x10)
#define GPIO_BANK23_BASE      (GPIO_BANK01_BASE + GPIO_BANK_OFFSET)
#define GPIO_BANK45_BASE      (GPIO_BANK23_BASE + GPIO_BANK_OFFSET)
#define GPIO_BANK67_BASE      (GPIO_BANK45_BASE + GPIO_BANK_OFFSET)
#define GPIO_BANK8_BASE       (GPIO_BANK67_BASE + GPIO_BANK_OFFSET)

#define GPIO_BUFF_OE_BANK        (2)
#define GPIO_BUFF_OE_PIN         (6)
#define PINMUX_GPIO_BUFF_OE_REG  (6)
#define PINMUX_GPIO_BUFF_OE_MASK (0x000000F0)
#define PINMUX_GPIO_BUFF_OE_VAL  (0x00000080)

//-----------------------------------------------------------------------------
// Timer registers
//-----------------------------------------------------------------------------
#define TIMER0_REG_BASE       (0x01C20000)
#define TIMER1_REG_BASE       (0x01C21000)

//-----------------------------------------------------------------------------
// UART registers
//-----------------------------------------------------------------------------
#define UART0_REG_BASE        (0x01C42000)
#define UART1_REG_BASE        (0x01D0C000)
#define UART2_REG_BASE        (0x01D0D000)

//-----------------------------------------------------------------------------
// SPI registers
//-----------------------------------------------------------------------------
#define SPI0_REG_BASE         (0x01C41000)
#define SPI1_REG_BASE         (0x01F0E000)

//-----------------------------------------------------------------------------
// I2C registers
//-----------------------------------------------------------------------------
#define I2C0_REG_BASE         (0x01C22000)
#define I2C1_REG_BASE         (0x01E28000)

//-----------------------------------------------------------------------------
// EMAC registers
//-----------------------------------------------------------------------------
#define EMAC_RAM_BASE         (0x01E20000)
#define EMAC_CTRL_REG_BASE    (0x01E22000)
#define EMAC_REG_BASE         (0x01E23000)
#define MDIO_REG_BASE         (0x01E24000)

//-----------------------------------------------------------------------------
// MMCSD registers
//-----------------------------------------------------------------------------
#define MMCSD0_REG_BASE       (0x01C40000)
#define MMCSD1_REG_BASE       (0x01E1B000)

//-----------------------------------------------------------------------------
// MCASP registers
//-----------------------------------------------------------------------------
#define MCASP_REG_BASE        (0x01D00000)

//-----------------------------------------------------------------------------
// USB registers
//-----------------------------------------------------------------------------
#define USB_OTG_REG_BASE      (0x01E00000)
#define USB_HOST_REG_BASE     (0x01E25000)

//-----------------------------------------------------------------------------
// VPIF registers
//-----------------------------------------------------------------------------
#define VPIF_REG_BASE            (0x01E17000)
#define VPIF_CAP_CH0_REG_BASE    (0x01E17040)
#define VPIF_CAP_CH1_REG_BASE    (0x01E17080)
#define VPIF_DISP_CH2_REG_BASE   (0x01E170C0)
#define VPIF_DISP_CH3_REG_BASE   (0x01E17140)

//-----------------------------------------------------------------------------
// LCDC registers
//-----------------------------------------------------------------------------
#define LCDC_REG_BASE         (0x01E13000)

//-----------------------------------------------------------------------------
// uPP registers
//-----------------------------------------------------------------------------
#define UPP_REG_BASE          (0x01E16000)

//-----------------------------------------------------------------------------
// RTC registers
//-----------------------------------------------------------------------------
#define RTC_REG_BASE          (0x01C23000)




// define the one and only system config module.
#define SYSCONFIG          ((sysconfig_regs_t *)SYSCONFIG_REG_BASE)

// unlock/lock kick registers defines.
#define KICK0R_UNLOCK      (0x83E70B13)
#define KICK1R_UNLOCK      (0x95A4F1E0)
#define KICK0R_LOCK        (0x00000000)
#define KICK1R_LOCK        (0x00000000)

// bitmask defines for cfgchip[0].
#define PLL0_MASTER_LOCK   (0x00000010)   // bit 4

// bitmask defines for cfgchip[3].
#define CLK2XSRC           (0x00000080)   // bit 7
#define PLL1_MASTER_LOCK   (0x00000020)   // bit 5
#define DIV4P5ENA          (0x00000004)   // bit 2
#define EMA_CLKSRC         (0x00000002)   // bit 1

// defines for hostcfg.
#define BOOTRDY            (0x00000001)   // bit 0

// defines for pinmux0.
#define MASK_EMB_WE        (0xF0000000) // bits 31-28
#define MASK_EMB_RAS       (0x0F000000) // bits 27-24




// define the power and sleep config modules.
#define PSC0            ((psc_regs_t *)PSC0_REG_BASE)
#define PSC1            ((psc_regs_t *)PSC1_REG_BASE)

// domain defines.
#define DOMAIN0         (0x00000001)
#define DOMAIN1         (0x00000002)

// defines for ptcmd.
#define GO_0            (0x00000001)
#define GO_1            (0x00000002)

// defines for ptstat.
#define GOSTAT_0        (0x00000001)
#define GOSTAT_1        (0x00000002)

// psc0 lpsc defines.
#define LPSC_TPCC          (0)
#define LPSC_TPTC0         (1)
#define LPSC_TPTC1         (2)
#define LPSC_EMIFA         (3)
#define LPSC_SPI0          (4)
#define LPSC_MMCSD0        (5)
#define LPSC_AINTC         (6)
#define LPSC_ARM_RAMROM    (7)
// 8 not used.
#define LPSC_UART0         (9)
#define LPSC_SCR0          (10)
#define LPSC_SCR1          (11)
#define LPSC_SCR2          (12)
#define LPSC_DMAX          (13)
#define LPSC_ARM           (14)
#define LPSC_DSP           (15)

// psc1 lpsc defines.
// 0 not used.
#define LPSC_USB0                (1)
#define LPSC_USB1                (2)
#define LPSC_GPIO                (3)
#define LPSC_HPI                 (4)
#define LPSC_EMAC                (5)
#define LPSC_EMIF3A              (6)
#define LPSC_DDR2                (6)
#define LPSC_MCASP0              (7)
#define LPSC_SATA                (8)
#define LPSC_VPIF                (9)
#define LPSC_SPI1                (10)
#define LPSC_I2C1                (11)
#define LPSC_UART1               (12)
#define LPSC_UART2               (13)
#define LPSC_MCBSP0              (14)
#define LPSC_MCBSP1              (15)
#define LPSC_LCDC                (16)
#define LPSC_PWM                 (17)
#define LPSC_MMCSD1              (18)
#define LPSC_RPI                 (19)
#define LPSC_ECAP                (20)
#define LPSC_TPTC2               (21)
// 22-23 not used.
#define LPSC_SCR8                (24)
#define LPSC_SCR7                (25)
#define LPSC_SCR12               (26)
// 27-30 not used.
#define LPSC_SHRAM               (31)

// psc module status register defines.
#define MASK_STATE               (0x0000003F)

// psc module control register defines.
#define FORCE                    (0x80000000)   // bit 31.
#define EMUIHBIE                 (0x00000400)   // bit 10.
#define EMURSTIE                 (0x00000200)   // bit 9.
#define LRST                     (0x00000100)   // bit 8.
#define NEXT                     (0x00000007)   // bits 0-2.

// psc module next states.
#define PSC_ENABLE               (0x00000003)
#define PSC_DISABLE              (0x00000002)
#define PSC_SYNCRESET            (0x00000001)
#define PSC_SWRSTDISABLE         (0x00000000)



#define PLL0         ((pll_regs_t*)PLL0_REG_BASE)
#define PLL1         ((pll_regs_t*)PLL1_REG_BASE)

// bitmask defines for PLLCTL.
#define EXTCLKSRC       (0x00000200)   // bit 9
#define CLKMODE         (0x00000100)   // bit 8
#define PLLENSRC        (0x00000020)   // bit 5
#define PLLDIS          (0x00000010)   // bit 4 
#define PLLRST          (0x00000008)   // bit 3
#define PLLPWRDN        (0x00000002)   // bit 1
#define PLLEN           (0x00000001)   // bit 0
#define CLKMODE_SHIFT   (8)

// bitmask defines for PLLCMD and PLLSTAT.
#define GOSET        (0x00000001)
#define GOSTAT       (0x00000001)

// defines for divisors.
#define DIV_ENABLE         (0x00008000)
#define MULTIPLIER         (24)
#define POSTDIV_RATIO      (1)
#define PLLDIV2_RATIO      (2)
#define PLLDIV3_RATIO      (12)
#define PLLDIV4_RATIO      (4)
#define PLLDIV5_RATIO      (5)
#define PLLDIV6_RATIO      (1)
#define PLLDIV7_RATIO      (6)
#define PLL_LOCK_CYCLES          (2400)
#define PLL_STABILIZATION_TIME   (2000)
#define PLL_RESET_TIME_CNT       (200)

// system clock frequency defines.
#define AUXCLOCK_HZ        (24)
#define SYSCLOCK1_HZ       (300000000)
#define SYSCLOCK2_HZ       (SYSCLOCK1_HZ / PLLDIV2_RATIO)
#define SYSCLOCK3_HZ       (SYSCLOCK1_HZ / PLLDIV3_RATIO)
#define SYSCLOCK4_HZ       (SYSCLOCK1_HZ / PLLDIV4_RATIO)
#define SYSCLOCK5_HZ       (SYSCLOCK1_HZ / PLLDIV5_RATIO)
#define SYSCLOCK6_HZ       (SYSCLOCK1_HZ / PLLDIV6_RATIO)
#define SYSCLOCK7_HZ       (SYSCLOCK1_HZ / PLLDIV7_RATIO)

// bitmask defines for OCSEL (OBSCLK pin).
#define OBSCLK_CLKIN       (0x14)
#define OBSCLK_SYSCLK1     (0x17)
#define OBSCLK_SYSCLK2     (0x18)
#define OBSCLK_SYSCLK3     (0x19)
#define OBSCLK_SYSCLK4     (0x1A)
#define OBSCLK_SYSCLK5     (0x1B)
#define OBSCLK_SYSCLK6     (0x1C)
#define OBSCLK_SYSCLK7     (0x1D)


//-----------------------------------------------------------------------------
// Register Structure & Defines
//-----------------------------------------------------------------------------
typedef struct
{
   volatile Uint32 REVID;         // 0x0000
   volatile Uint32 RSVD0[56];     // 0x0004
   volatile Uint32 RSTYPE;        // 0x00E4
   volatile Uint32 RSVD1[6];      // 0x00E8
   volatile Uint32 PLLCTL;        // 0x0100
   volatile Uint32 OCSEL;         // 0x0104
   volatile Uint32 RSVD2[2];      // 0x0108
   volatile Uint32 PLLM;          // 0x0110
   volatile Uint32 PREDIV;        // 0x0114
   volatile Uint32 PLLDIV1;       // 0x0118
   volatile Uint32 PLLDIV2;       // 0x011C
   volatile Uint32 PLLDIV3;       // 0x0120
   volatile Uint32 OSCDIV;        // 0x0124
   volatile Uint32 POSTDIV;       // 0x0128
   volatile Uint32 RSVD3[3];      // 0x012C
   volatile Uint32 PLLCMD;        // 0x0138
   volatile Uint32 PLLSTAT;       // 0x013C
   volatile Uint32 ALNCTL;        // 0x0140
   volatile Uint32 DCHANGE;       // 0x0144
   volatile Uint32 CKEN;          // 0x0148
   volatile Uint32 CKSTAT;        // 0x014C
   volatile Uint32 SYSTAT;        // 0x0150
   volatile Uint32 RSVD4[3];      // 0x0154
   volatile Uint32 PLLDIV4;       // 0x0160
   volatile Uint32 PLLDIV5;       // 0x0164
   volatile Uint32 PLLDIV6;       // 0x0168
   volatile Uint32 PLLDIV7;       // 0x016C
} pll_regs_t;
//-----------------------------------------------------------------------------
// Register Structure & Defines
//-----------------------------------------------------------------------------
typedef struct
{
  volatile Uint32 REVID;          // 0x0000
  volatile Uint32 RSVD0[5];       // 0x0004
  volatile Uint32 INTEVAL;        // 0x0018
  volatile Uint32 RSVD1[9];       // 0x001C
  volatile Uint32 MERRPR0;        // 0x0040
  volatile Uint32 RSVD2[3];       // 0x0044
  volatile Uint32 MERRCR0;        // 0x0050
  volatile Uint32 RSVD3[3];       // 0x0054
  volatile Uint32 PERRPR;         // 0x0060
  volatile Uint32 RSVD4;          // 0x0064
  volatile Uint32 PERRCR;         // 0x0068
  volatile Uint32 RSVD5[45];      // 0x006C
  volatile Uint32 PTCMD;          // 0x0120
  volatile Uint32 RSVD6;          // 0x0124
  volatile Uint32 PTSTAT;         // 0x0128
  volatile Uint32 RSVD7[53];      // 0x012C
  volatile Uint32 PDSTAT0;        // 0x0200
  volatile Uint32 PDSTAT1;        // 0x0204
  volatile Uint32 RSVD8[62];      // 0x0208
  volatile Uint32 PDCTL0;         // 0x0300
  volatile Uint32 PDCTL1;         // 0x0304
  volatile Uint32 RSVD9[62];      // 0x0308
  volatile Uint32 PDCFG0;         // 0x0400
  volatile Uint32 PDCFG1;         // 0x0404
  volatile Uint32 RSVD10[254];    // 0x0408
  volatile Uint32 MDSTAT[32];     // 0x0800
  volatile Uint32 RSVD11[96];     // 0x0880
  volatile Uint32 MDCTL[32];      // 0x0A00
} psc_regs_t;

typedef struct
{
   volatile Uint32 REVID;            // 0x0000
   volatile Uint32 RSVD0;            // 0x0004
   volatile Uint32 DIEIDR[4];        // 0x0008
   volatile Uint32 RSVD1[2];         // 0x0018
   volatile Uint32 BOOTCFG;          // 0x0020
   volatile Uint32 RSVD2[5];         // 0x0024
   volatile Uint32 KICKR[2];         // 0x0038
   volatile Uint32 HOST0CFG;         // 0x0040
   volatile Uint32 HOST1CFG;         // 0x0044
   volatile Uint32 RSVD3[38];        // 0x0048
   volatile Uint32 IRAWSTAT;         // 0x00E0
   volatile Uint32 IENSTAT;          // 0x00E4
   volatile Uint32 IENSET;           // 0x00E8
   volatile Uint32 IENCLR;           // 0x00EC
   volatile Uint32 EOI;              // 0x00F0
   volatile Uint32 FLTADDRR;         // 0x00F4
   volatile Uint32 FLTSTAT;          // 0x00F8
   volatile Uint32 RSVD4[5];         // 0x00FC
   volatile Uint32 MSTPRI[3];        // 0x0110
   volatile Uint32 RSVD5;            // 0x011C
   volatile Uint32 PINMUX[20];       // 0x0120
   volatile Uint32 SUSPSRC;          // 0x0170
   volatile Uint32 CHIPSIG;          // 0x0174
   volatile Uint32 CHIPSIG_CLR;      // 0x0178
   volatile Uint32 CFGCHIP[5];       // 0x017C
} sysconfig_regs_t;


typedef struct
{
  volatile UINT32 REVID;          // 0x0000
  volatile UINT32 SDRSTAT;        // 0x0004
  volatile UINT32 SDCR;           // 0x0008
  volatile UINT32 SDRCR;          // 0x000C
  volatile UINT32 SDTIMR1;        // 0x0010
  volatile UINT32 SDTIMR2;        // 0x0014
  volatile UINT32 RSVD1;          // 0x0018
  volatile UINT32 SDCR2;          // 0x001C
  volatile UINT32 PBBPR;          // 0x0020
  volatile UINT32 RSVD2;          // 0x0024
  volatile UINT32 VBUSMCFG1;      // 0x0028
  volatile UINT32 VBUSMCFG2;      // 0x002C
  volatile UINT32 RSVD3[36];      // 0x0030
  volatile UINT32 IRR;            // 0x00C0
  volatile UINT32 IMR;            // 0x00C4
  volatile UINT32 IMSR;           // 0x00C8
  volatile UINT32 IMCR;           // 0x00CC
  volatile UINT32 RSVD4[4];       // 0x00D0
  volatile UINT32 DDRPHYREV;      // 0x00E0
  volatile UINT32 DDRPHYCTL1;     // 0x00E4
  volatile UINT32 DDRPHYCTL2;     // 0x00E8
} ddr_regs_t;

#define DDR          ((ddr_regs_t*)DDR_REG_BASE)

#define VTPIO_CTL    (*(UINT32 *)(0x1E2C0000))

//* Register Overlay Structure
#define CSL_CACHE_0_REGS                    (0x01840000)
typedef struct  {
    volatile UINT32 L2CFG;
    volatile UINT8 RSVD0[28];
    volatile UINT32 L1PCFG;
    volatile UINT32 L1PCC;
    volatile UINT8 RSVD1[24];
    volatile UINT32 L1DCFG;
    volatile UINT32 L1DCC;
    volatile UINT8 RSVD2[16312];
    volatile UINT32 L2WBAR;
    volatile UINT32 L2WWC;
    volatile UINT8 RSVD3[8];
    volatile UINT32 L2WIBAR;
    volatile UINT32 L2WIWC;
    volatile UINT32 L2IBAR;
    volatile UINT32 L2IWC;
    volatile UINT32 L1PIBAR;
    volatile UINT32 L1PIWC;
    volatile UINT8 RSVD4[8];
    volatile UINT32 L1DWIBAR;
    volatile UINT32 L1DWIWC;
    volatile UINT8 RSVD5[8];
    volatile UINT32 L1DWBAR;
    volatile UINT32 L1DWWC;
    volatile UINT32 L1DIBAR;
    volatile UINT32 L1DIWC;
    volatile UINT8 RSVD6[4016];
    volatile UINT32 L2WB;
    volatile UINT32 L2WBINV;
    volatile UINT32 L2INV;
    volatile UINT8 RSVD7[28];
    volatile UINT32 L1PINV;
    volatile UINT8 RSVD8[20];
    volatile UINT32 L1DWB;
    volatile UINT32 L1DWBINV;
    volatile UINT32 L1DINV;
    volatile UINT8 RSVD9[12212];
    volatile UINT32 MAR[256];
} CSL_CacheRegs;
#endif
/**************************************************************************\
* Overlay structure typedef definition
\**************************************************************************/
typedef volatile CSL_CacheRegs         *CSL_CacheRegsOvly;

extern const Uint32 bitval_u32[32];
//-----------------------------------------------------------------------------
// bitmask defines for EMUMGT.
//-----------------------------------------------------------------------------
#define SOFT                  (0x00000002)   // bit 1
#define FREE                  (0x00000001)   // bit 0

#define FALSE                  0
#define TRUE                   1

#ifdef __cplusplus
}
#endif

//#endif


