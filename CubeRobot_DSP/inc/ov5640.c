//-----------------------------------------------------------------------------
// \file    OV5640 .c
// \brief   implementation of a camera driver for the C6748 EVM.
//
//-----------------------------------------------------------------------------
#include "stdio.h"
#include "types.h"
#include "rk6748.h"
#include "rk6748_timer.h"
#include "rk6748_i2c.h"
#include "ov5640cfg.h"
#include "ov5640af.h"

// OV5640 Registers
#define OV5640_CHIPIDH          0X300A  	// OV5640: High Byte of Chip ID
#define OV5640_CHIPIDL          0X300B  	// OV5640: Low Byte of Chip ID
#define OV5640_ID               0X5640  	// OV5640: Chip ID
 
//-----------------------------------------------------------------------------
// Private Defines and Macros
//-----------------------------------------------------------------------------

// i2c defines.
#define I2C_PORT_OV5640      (I2C0)
#define I2C_ADDR_OV5640      (0x78>>1)

#define I2C_ADDR_BUSSW        (0x0073)
// i2c bus switch defines.
#define I2C_BUSSW_CH0EN       (0x01)
#define I2C_BUSSW_CH1EN       (0x02)


void OV5640_Flash_Ctrl(UINT8 sw);
UINT8 OV5640_WR_Reg(UINT16 reg,UINT8 data);

UINT32 OV5640_readRegister(UINT16 in_reg_addr, UINT8 *dest_buffer)
{
	UINT32 rtn;
	UINT8 i2c_data[2];
	
	i2c_data[0] = (UINT8)((in_reg_addr & 0xFF00) >> 8);
	i2c_data[1] = (UINT8)(in_reg_addr & 0x00FF);

   // write the register address that we want to read.
   rtn = I2C_write(I2C0, I2C_ADDR_OV5640, i2c_data, 2, SKIP_STOP_BIT_AFTER_WRITE);
   if (rtn != ERR_NO_ERROR)
      return (rtn);

   // clock out the register data.
   rtn = I2C_read(I2C0, I2C_ADDR_OV5640, i2c_data, 1, SKIP_BUSY_BIT_CHECK);
   if (rtn != ERR_NO_ERROR)
      return (rtn);

   *dest_buffer = i2c_data[0];
   
   return (rtn);
}

// Read OV5640 Registers
UINT8 OV5640_RD_Reg(UINT16 reg)
{
	UINT32 rtn;
	UINT8  i2c_data[2];
	
	i2c_data[0] = (UINT8)((reg & 0xFF00) >> 8);
	i2c_data[1] = (UINT8)(reg & 0x00FF);

   // write the register address that we want to read.
   rtn = I2C_write(I2C_PORT_OV5640, I2C_ADDR_OV5640, i2c_data, 2, SKIP_STOP_BIT_AFTER_WRITE);
   if (rtn != ERR_NO_ERROR)
      return (rtn);

   // clock out the register data.
   I2C_read(I2C_PORT_OV5640, I2C_ADDR_OV5640, i2c_data, 1, SKIP_BUSY_BIT_CHECK);
   
   return (i2c_data[0]);
}

// Write OV5640 Registers 
// Return: 0 for success and 1 for failure
UINT8 OV5640_WR_Reg(UINT16 reg,UINT8 data)
{
	 UINT32 rtn;
	 UINT8	i2c_data[3];
	 
	 i2c_data[0] = (UINT8)((reg & 0xFF00) >> 8);
	 i2c_data[1] = (UINT8)(reg & 0x00FF);
	 i2c_data[2] = data;
	
	// write the register that we want to read.
	rtn = I2C_write(I2C_PORT_OV5640, I2C_ADDR_OV5640, i2c_data, 3, SET_STOP_BIT_AFTER_WRITE);
	
	return (rtn);
}

UINT16 OV5640_Init(void)
{
	UINT16 i=0;
	UINT16 reg;
	
   	RK6748_pinmuxConfig(13, 0xF0F00000, 0x80800000); // Pin reuse
   	GPIO_setDir(6,8,0);  // RST
   	GPIO_setDir(6,10,0); // POWER
   
   	GPIO_setOutput(6,8,0);
   	MsDelay(50);
   	GPIO_setDir(6,10,0);    //POWER ON
   	MsDelay(50);
   	GPIO_setOutput(6,8,1);	
   	MsDelay(50);
 
   	I2C_init(I2C0, I2C_CLK_100K); // Init SCCB IO
   	MsDelay(100);	

	reg=OV5640_RD_Reg(OV5640_CHIPIDH);	// Read ID high 8 bits
	reg<<=8;
	reg|=OV5640_RD_Reg(OV5640_CHIPIDL);	// Read ID low 8 bits
	
	printf("ID:0x%04X\r\n",reg);
	
	if(reg!=OV5640_ID)
	{
		printf("ID:0x%04X\r\n",reg);
		return 1;
	} 

	//reg write test
	/*
	reg=OV5640_RD_Reg(0x3c01);
	printf("ID:0x%02X\r\n",reg);
	OV5640_WR_Reg(0x3c01,0X34);	//system clock from pad, bit[1]
	reg=OV5640_RD_Reg(0x3c01);
	printf("ID:0x%02X\r\n",reg);
	*/
	
	OV5640_WR_Reg(0x3103,0X11);	//system clock from pad, bit[1]
	OV5640_WR_Reg(0X3008,0X82);	// soft reset
	MsDelay(10);
 	// Init OV5640 
	for(i=0;i<sizeof(ov5640_init_reg_tbl)/4;i++)
	{
	   	OV5640_WR_Reg(ov5640_init_reg_tbl[i][0],ov5640_init_reg_tbl[i][1]);
 	}    
	// Check whether the flash is normal
	OV5640_Flash_Ctrl(1);//on
	MsDelay(500);
	OV5640_Flash_Ctrl(0);//off
  	return 0x00; 	//ok
	
}
 
// Set OV5640 to JPEG mode
void OV5640_JPEG_Mode(void) 
{
	UINT16 i=0; 
	for(i=0;i<(sizeof(OV5640_jpeg_reg_tbl)/4);i++)
	{
		OV5640_WR_Reg(OV5640_jpeg_reg_tbl[i][0],OV5640_jpeg_reg_tbl[i][1]);  
	}  
}

// Set OV5640 to RGB565 mode
void OV5640_RGB565_Mode(void) 
{
	UINT16 i=0;
	for(i=0;i<(sizeof(ov5640_rgb565_reg_tbl)/4);i++)
	{
		OV5640_WR_Reg(ov5640_rgb565_reg_tbl[i][0],ov5640_rgb565_reg_tbl[i][1]); 
	} 
} 

// EV Exposure compensation list
const static UINT8 OV5640_EXPOSURE_TBL[7][6]=
{
    0x10,0x08,0x10,0x08,0x20,0x10,//-3  
    0x20,0x18,0x41,0x20,0x18,0x10,//-
    0x30,0x28,0x61,0x30,0x28,0x10,//-1 
    0x38,0x30,0x61,0x38,0x30,0x10,//0  
    0x40,0x38,0x71,0x40,0x38,0x10,//+1 
    0x50,0x48,0x90,0x50,0x48,0x20,//+2   
    0x60,0x58,0xa0,0x60,0x58,0x20,//+3    
};

// EV Exposure compensation
//exposure:0~6
void OV5640_Exposure(UINT8 exposure)
{
    OV5640_WR_Reg(0x3212,0x03);	//start group 3
    OV5640_WR_Reg(0x3a0f,OV5640_EXPOSURE_TBL[exposure][0]); 
	OV5640_WR_Reg(0x3a10,OV5640_EXPOSURE_TBL[exposure][1]); 
    OV5640_WR_Reg(0x3a1b,OV5640_EXPOSURE_TBL[exposure][2]); 
	OV5640_WR_Reg(0x3a1e,OV5640_EXPOSURE_TBL[exposure][3]); 
    OV5640_WR_Reg(0x3a11,OV5640_EXPOSURE_TBL[exposure][4]); 
    OV5640_WR_Reg(0x3a1f,OV5640_EXPOSURE_TBL[exposure][5]); 
    OV5640_WR_Reg(0x3212,0x13); //end group 3
	OV5640_WR_Reg(0x3212,0xa3); //launch group 3
}

// Light mode parameter table, supporting 5 modes
const static UINT8 OV5640_LIGHTMODE_TBL[5][7]=
{ 
	0x04,0X00,0X04,0X00,0X04,0X00,0X00,//Auto 
	0x06,0X1C,0X04,0X00,0X04,0XF3,0X01,//Sunny 
	0x05,0X48,0X04,0X00,0X07,0XCF,0X01,//Office, 
	0x06,0X48,0X04,0X00,0X04,0XD3,0X01,//Cloudy 
	0x04,0X10,0X04,0X00,0X08,0X40,0X01,//Home 
}; 

// White balance settings
// 0-auto 1-sunny 2-office 3-cloudy 4-home
void OV5640_Light_Mode(UINT8 mode)
{
	UINT8 i;
	OV5640_WR_Reg(0x3212,0x03);	//start group 3
	for(i=0;i<7;i++)OV5640_WR_Reg(0x3400+i,OV5640_LIGHTMODE_TBL[mode][i]); // Set saturation
	OV5640_WR_Reg(0x3212,0x13); //end group 3
	OV5640_WR_Reg(0x3212,0xa3); //launch group 3	
}

// Color saturation setting parameter table, supporting 7 levels
const static UINT8 OV5640_SATURATION_TBL[7][6]=
{ 
	0X0C,0x30,0X3D,0X3E,0X3D,0X01,//-3 
	0X10,0x3D,0X4D,0X4E,0X4D,0X01,//-2	
	0X15,0x52,0X66,0X68,0X66,0X02,//-1	
	0X1A,0x66,0X80,0X82,0X80,0X02,//+0	
	0X1F,0x7A,0X9A,0X9C,0X9A,0X02,//+1	
	0X24,0x8F,0XB3,0XB6,0XB3,0X03,//+2
 	0X2B,0xAB,0XD6,0XDA,0XD6,0X04,//+3
}; 

// Chroma setting
// 0~6
void OV5640_Color_Saturation(UINT8 sat)
{ 
	UINT8 i;
	OV5640_WR_Reg(0x3212,0x03);	//start group 3
	OV5640_WR_Reg(0x5381,0x1c);
	OV5640_WR_Reg(0x5382,0x5a);
	OV5640_WR_Reg(0x5383,0x06);
	for(i=0;i<6;i++)OV5640_WR_Reg(0x5384+i,OV5640_SATURATION_TBL[sat][i]); // Set saturation
	OV5640_WR_Reg(0x538b, 0x98);
	OV5640_WR_Reg(0x538a, 0x01);
	OV5640_WR_Reg(0x3212, 0x13); //end group 3
	OV5640_WR_Reg(0x3212, 0xa3); //launch group 3	
}

// Brightness setting
// 0~8
void OV5640_Brightness(UINT8 bright)
{
	UINT8 brtval;
	if(bright<4)brtval=4-bright;
	else brtval=bright-4;
	OV5640_WR_Reg(0x3212,0x03);	//start group 3
	OV5640_WR_Reg(0x5587,brtval<<4);
	if(bright<4)OV5640_WR_Reg(0x5588,0x09);
	else OV5640_WR_Reg(0x5588,0x01);
	OV5640_WR_Reg(0x3212,0x13); //end group 3
	OV5640_WR_Reg(0x3212,0xa3); //launch group 3
}

// Contrast setting
// 0~6
void OV5640_Contrast(UINT8 contrast)
{
	UINT8 reg0val=0X00;//contrast=3,Ĭ�϶Աȶ�
	UINT8 reg1val=0X20;
  	switch(contrast)
	{
		case 0://-3
			reg1val=reg0val=0X14;	 	 
			break;	
		case 1://-2
			reg1val=reg0val=0X18; 	 
			break;	
		case 2://-1
			reg1val=reg0val=0X1C;	 
			break;	
		case 4://1
			reg0val=0X10;	 	 
			reg1val=0X24;	 	 
			break;	
		case 5://2
			reg0val=0X18;	 	 
			reg1val=0X28;	 	 
			break;	
		case 6://3
			reg0val=0X1C;	 	 
			reg1val=0X2C;	 	 
			break;	
	} 
	OV5640_WR_Reg(0x3212,0x03); //start group 3
	OV5640_WR_Reg(0x5585,reg0val);
	OV5640_WR_Reg(0x5586,reg1val); 
	OV5640_WR_Reg(0x3212,0x13); //end group 3
	OV5640_WR_Reg(0x3212,0xa3); //launch group 3
}

// Sharpness setting
// 0~33: 0-off 33-auto others-values
void OV5640_Sharpness(UINT8 sharp)
{
	if(sharp<33)
	{
		OV5640_WR_Reg(0x5308,0x65);
		OV5640_WR_Reg(0x5302,sharp);
	}else // auto
	{
		OV5640_WR_Reg(0x5308,0x25);
		OV5640_WR_Reg(0x5300,0x08);
		OV5640_WR_Reg(0x5301,0x30);
		OV5640_WR_Reg(0x5302,0x10);
		OV5640_WR_Reg(0x5303,0x00);
		OV5640_WR_Reg(0x5309,0x08);
		OV5640_WR_Reg(0x530a,0x30);
		OV5640_WR_Reg(0x530b,0x04);
		OV5640_WR_Reg(0x530c,0x06);
	}
	
}

// Special effects setting parameter table, supporting 7 special effects
const static UINT8 OV5640_EFFECTS_TBL[7][3]=
{ 
	0X06,0x40,0X10,
	0X1E,0xA0,0X40,
	0X1E,0x80,0XC0,
	0X1E,0x80,0X80,
	0X1E,0x40,0XA0, 
	0X40,0x40,0X10,
	0X1E,0x60,0X60,
}; 

// Special effect settings 
void OV5640_Special_Effects(UINT8 eft)
{ 
	OV5640_WR_Reg(0x3212,0x03); //start group 3
	OV5640_WR_Reg(0x5580,OV5640_EFFECTS_TBL[eft][0]);
	OV5640_WR_Reg(0x5583,OV5640_EFFECTS_TBL[eft][1]);// sat U
	OV5640_WR_Reg(0x5584,OV5640_EFFECTS_TBL[eft][2]);// sat V
	OV5640_WR_Reg(0x5003,0x08);
	OV5640_WR_Reg(0x3212,0x13); //end group 3
	OV5640_WR_Reg(0x3212,0xa3); //launch group 3
}

// Test sequence
//mode: 0-off  1-lines 2-blocks
void OV5640_Test_Pattern(UINT8 mode)
{
	if(mode==0)OV5640_WR_Reg(0X503D,0X00);
	else if(mode==1)OV5640_WR_Reg(0X503D,0X80);
	else if(mode==2)OV5640_WR_Reg(0X503D,0X82);
} 

// Strobe Control
//mode: 0-off 1-on
void OV5640_Flash_Ctrl(UINT8 sw)
{
	OV5640_WR_Reg(0x3016,0X02);
	OV5640_WR_Reg(0x301C,0X02);
	if(sw)OV5640_WR_Reg(0X3019,0X02);
	else OV5640_WR_Reg(0X3019,0X00);
}

// Set image output size
// Return: 0 for success and others for failure
UINT8 OV5640_OutSize_Set(UINT16 offx,UINT16 offy,UINT16 width,UINT16 height)
{ 
    OV5640_WR_Reg(0X3212,0X03);  	 // Start group 3
    OV5640_WR_Reg(0x3808,width>>8);
    OV5640_WR_Reg(0x3809,width&0xff);
    OV5640_WR_Reg(0x380a,height>>8);
    OV5640_WR_Reg(0x380b,height&0xff);
    OV5640_WR_Reg(0x3810,offx>>8);	 // Set X offset for high Byte
    OV5640_WR_Reg(0x3811,offx&0xff); // Set X offset for high Byte
	
    OV5640_WR_Reg(0x3812,offy>>8);	 // Set Y offset for high Byte
    OV5640_WR_Reg(0x3813,offy&0xff); // Set Y offset for low Byte
	
    OV5640_WR_Reg(0X3212,0X13); // End group 3
    OV5640_WR_Reg(0X3212,0Xa3);	// Enable group 3 settings
	return 0; 
}

// Setting the image window size (ISP size). NOT necessary
// Return: 0 for success and others for failure
UINT8 OV5640_ImageWin_Set(UINT16 offx,UINT16 offy,UINT16 width,UINT16 height)
{
	UINT16 xst,yst,xend,yend;
	xst=offx;
	yst=offy;
	xend=offx+width-1;
	yend=offy+height-1;  
    OV5640_WR_Reg(0X3212,0X03);		// Start group 3
	OV5640_WR_Reg(0X3800,xst>>8);	
	OV5640_WR_Reg(0X3801,xst&0XFF);	
	OV5640_WR_Reg(0X3802,yst>>8);	
	OV5640_WR_Reg(0X3803,yst&0XFF);	
	OV5640_WR_Reg(0X3804,xend>>8);	
	OV5640_WR_Reg(0X3805,xend&0XFF);
	OV5640_WR_Reg(0X3806,yend>>8);	
	OV5640_WR_Reg(0X3807,yend&0XFF);
    OV5640_WR_Reg(0X3212,0X13);		// End group 3
    OV5640_WR_Reg(0X3212,0Xa3);		// Enable group 3 settings
	return 0;
}  

// Initialize auto focus
// Return: 0 for success and others for failure
UINT8 OV5640_Focus_Init(void)
{ 
	UINT16 i; 
	UINT16 addr=0x8000;
	UINT8 state=0x8F;
	OV5640_WR_Reg(0x3000, 0x20);			// reset MCU	 
	for(i=0;i<sizeof(OV5640_AF_Config);i++) // Send configuration array
	{
		OV5640_WR_Reg(addr,OV5640_AF_Config[i]);
		addr++;
	}  
	OV5640_WR_Reg(0x3022,0x00);
	OV5640_WR_Reg(0x3023,0x00);
	OV5640_WR_Reg(0x3024,0x00);
	OV5640_WR_Reg(0x3025,0x00);
	OV5640_WR_Reg(0x3026,0x00);
	OV5640_WR_Reg(0x3027,0x00);
	OV5640_WR_Reg(0x3028,0x00);
	OV5640_WR_Reg(0x3029,0x7f);
	OV5640_WR_Reg(0x3000,0x00); 
	i=0;
	do
	{
		state=OV5640_RD_Reg(0x3029);	
		MsDelay(5);
		i++;
		if(i>1000)return 1;
	}while(state!=0x70); 
	return 0;    
}  

//ִ Perform an autofocus
// Return: 0 for success and others for failure
UINT8 OV5640_Focus_Single(void)
{
	UINT8 temp; 
	UINT16 retry=0; 
	OV5640_WR_Reg(0x3022,0x03);		// Trigger auto focus once
	while(1)
	{
		retry++;
		temp=OV5640_RD_Reg(0x3029);	// Check the focus completion status
		if(temp==0x10)break;		// focus completed
		MsDelay(5);
		if(retry>1000)return 1;
	}
	return 0;	 		
}

// Continuous auto focus, when out of focus, will automatically continue to focus
// Return: 0 for success and others for failure
UINT8 OV5640_Focus_Constant(void)
{
	UINT8 temp=0;   
	UINT16 retry=0; 
	OV5640_WR_Reg(0x3023,0x01);
	OV5640_WR_Reg(0x3022,0x08); // Send IDLE command
	do 
	{
		temp=OV5640_RD_Reg(0x3023); 
		retry++;
		if(retry>1000)return 2;
		MsDelay(5);
	} while(temp!=0x00);   
	OV5640_WR_Reg(0x3023,0x01);
	OV5640_WR_Reg(0x3022,0x04); // Send focusing command
	retry=0;
	do 
	{
		temp=OV5640_RD_Reg(0x3023); 
		retry++;
		if(retry>1000)return 2;
		MsDelay(5);
	}while(temp!=0x00); // 0 for completed, 1 for focusing
	return 0;
} 
