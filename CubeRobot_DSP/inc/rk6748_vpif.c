//-----------------------------------------------------------------------------
// \file    evmc6748_vpif.c
// \brief   implementation of a vpif driver for the C6748 EVM.
//
//-----------------------------------------------------------------------------
#include "types.h"
#include "rk6748.h"
#include "rk6748_vpif.h"

#define IMAGE_SIZE_X       (640)
#define IMAGE_SIZE_Y       (480)


//-----------------------------------------------------------------------------
// Private Defines and Macros
//-----------------------------------------------------------------------------
// pinmux defines.
#define PINMUX_VPIF_TX_REG_0        (16)
#define PINMUX_VPIF_TX_MASK_0       (0xFFFFFF00)
#define PINMUX_VPIF_TX_VAL_0        (0x11111100)
#define PINMUX_VPIF_TX_REG_1        (17)
#define PINMUX_VPIF_TX_MASK_1       (0xFFFFFFFF)
#define PINMUX_VPIF_TX_VAL_1        (0x11111111)
#define PINMUX_VPIF_TX_REG_2        (18)
#define PINMUX_VPIF_TX_MASK_2       (0x000000FF)
#define PINMUX_VPIF_TX_VAL_2        (0x00000011)
#define PINMUX_VPIF_TX_REG_3        (19)
#define PINMUX_VPIF_TX_MASK_3       (0x00FFFF00)
#define PINMUX_VPIF_TX_VAL_3        (0x00111100)
#define PINMUX_VPIF_RX_REG_0        (14)
#define PINMUX_VPIF_RX_MASK_0       (0xFFFFFFFF)
#define PINMUX_VPIF_RX_VAL_0        (0x11111111)
#define PINMUX_VPIF_RX_REG_1        (15)
#define PINMUX_VPIF_RX_MASK_1       (0xFFFFFFFF)
#define PINMUX_VPIF_RX_VAL_1        (0x11111111)
#define PINMUX_VPIF_RX_REG_2        (16)
#define PINMUX_VPIF_RX_MASK_2       (0x000000FF)
#define PINMUX_VPIF_RX_VAL_2        (0x00000011)

// data address defines.
#define LUMA_TOP_DATA_ADDR          (ADDR_VIDEO_DATA_BASE)
#define LUMA_TOP_DATA_SIZE          (720*240)
#define LUMA_BOTTOM_DATA_ADDR       (LUMA_TOP_DATA_ADDR + LUMA_TOP_DATA_SIZE)
#define LUMA_BOTTOM_DATA_SIZE       (720*240)
#define CHROMA_TOP_DATA_ADDR        (LUMA_BOTTOM_DATA_ADDR + LUMA_BOTTOM_DATA_SIZE)
#define CHROMA_TOP_DATA_SIZE        (720*240)
#define CHROMA_BOTTOM_DATA_ADDR     (CHROMA_TOP_DATA_ADDR + CHROMA_TOP_DATA_SIZE)
#define CHROMA_BOTTOM_DATA_SIZE     (720*240)

//-----------------------------------------------------------------------------
// Static Variable Declarations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------------------
static void configReceivePinMux(void);
static void configReceiveVpifRegs(vpif_cap_regs_t *vpif_cap_ch);
static void configTransmitPinMux(void);
static void configTransmitVpifRegs(vpif_disp_regs_t *vpif_disp_ch);

//-----------------------------------------------------------------------------
// Public Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// \brief   configures the vpif for receive.
//
// \param   video_connector_e in_conn - which connector to use for receive.
//
// \return  UINT32
//    ERR_NO_ERROR - everything is ok...vpif ready to use.
//    ERR_INIT_FAIL - something happened during initialization.
//-----------------------------------------------------------------------------
UINT32 VPIF_initReceive(video_connector_e in_conn)
{
   // disable the channel 0 & 1 and their interrupts.
   SETBIT(VPIF->INTENCLR, INT_FRAME_CH0 | INT_FRAME_CH1);
   CLRBIT(VPIF->INTEN, INT_FRAME_CH0 | INT_FRAME_CH1);
   VPIF->CH0CTRL = 0;
   VPIF->CH1CTRL = 0;

   // enable the psc and config pinmux for vpif.
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_VPIF, PSC_ENABLE);
   configReceivePinMux();

   // config dma request size and emulation control.
   VPIF->REQSIZE = 0x20;
   VPIF->EMUCTRL = 0x01;
   
   switch (in_conn)
   {
      case VIDEO_CONN_COMPOSITE:
         // config channel 0 control and capture registers.
         VPIF->CH0CTRL = INTFRAME_BOTTOM_ONLY | YCMUX;
         configReceiveVpifRegs(VPIF_CAP_CH0);

         // config interrupts.
         SETBIT(VPIF->INTEN, INT_FRAME_CH0);
         SETBIT(VPIF->INTENCLR, INT_FRAME_CH0);

         // enable channel 0.
         SETBIT(VPIF->CH0CTRL, CHANEN);
         break;

      case VIDEO_CONN_SVIDEO:
         // config channel 1 control and capture registers.
         VPIF->CH1CTRL = INTFRAME_BOTTOM_ONLY | YCMUX;
         configReceiveVpifRegs(VPIF_CAP_CH1);

         // config interrupts.
         SETBIT(VPIF->INTEN, INT_FRAME_CH1);
         SETBIT(VPIF->INTENCLR, INT_FRAME_CH1);

         // enable channel 1.
         SETBIT(VPIF->CH1CTRL, CHANEN);
         break;

      case VIDEO_CONN_CAMERA:
         // config channel 0 & 1 control and capture registers.
         VPIF->CH0CTRL = DATAWIDTH_8BPP | (120 << INTLINE_SHIFT) | FIELDFRAME | CH01_INTRPROG | INTFRAME_TOP_ONLY | CAPMODE;
         VPIF->CH1CTRL = FIELDFRAME | CH01_INTRPROG | INTFRAME_TOP_ONLY | CAPMODE;
         
         // config the data address registers (progressive).
         VPIF_CAP_CH0->TLUMA = ADDR_VIDEO_DATA_BASE;
         VPIF_CAP_CH0->IMGOFFSET = IMAGE_SIZE_X*2;//752*2;480*2

         // config interrupts.
         SETBIT(VPIF->INTEN, INT_FRAME_CH0 | INT_FRAME_CH1);
         SETBIT(VPIF->INTENCLR, INT_FRAME_CH0 | INT_FRAME_CH1);

         // enable channels 0 & 1.
         SETBIT(VPIF->CH0CTRL, CHANEN);
         SETBIT(VPIF->CH1CTRL, CHANEN);
         break;

      default:
         return (ERR_INVALID_PARAMETER);
   }

   return (ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
// \brief   configures the vpif for transmit.
//
// \param   video_connector_e in_conn - which connector to use for transmit.
//
// \return  UINT32
//    ERR_NO_ERROR - everything is ok...vpif ready to use.
//    ERR_INIT_FAIL - something happened during initialization.
//-----------------------------------------------------------------------------
UINT32 VPIF_initTransmit(video_connector_e in_conn)
{
   // disable the channel 2 & 3 and their interrupts.
   SETBIT(VPIF->INTENCLR, INT_FRAME_CH2 | INT_FRAME_CH3);
   CLRBIT(VPIF->INTEN, INT_FRAME_CH2 | INT_FRAME_CH3);
   VPIF->CH2CTRL = 0;
   VPIF->CH3CTRL = 0;
   
   // enable the psc and config pinmux for vpif.
   RK6748_lpscTransition(PSC1, DOMAIN0, LPSC_VPIF, PSC_ENABLE);
   configTransmitPinMux();

   // config dma request size, emulation control, and channel control regs.
   VPIF->REQSIZE = 0x20;
   VPIF->EMUCTRL = 0x01;

   switch (in_conn)
   {
      // composite and s-video use channel 2.
      case VIDEO_CONN_COMPOSITE:
      case VIDEO_CONN_SVIDEO:
         // config channel 2 control and display registers.
         VPIF->CH2CTRL = PIXEL_DATA | INTFRAME_BOTTOM_ONLY | YCMUX | CLKEN;
         configTransmitVpifRegs(VPIF_DISP_CH2);

         // config interrupts.
         SETBIT(VPIF->INTEN, INT_FRAME_CH2);
         SETBIT(VPIF->INTENSET, INT_FRAME_CH2);
         SETBIT(VPIF->INTENCLR, INT_FRAME_CH2);

         // enable channel 2 (sync to channel 0/1 if enabled).
         VPIF->INTENCLR = INT_FRAME_CH0 | INT_FRAME_CH1;
         if (CHKBIT(VPIF->INTEN, (INT_FRAME_CH0 | INT_FRAME_CH1)))
         {
            while (!CHKBIT(VPIF->INTSTAT, (INT_FRAME_CH0 | INT_FRAME_CH1))) {}
            VPIF->INTENCLR = INT_FRAME_CH0 | INT_FRAME_CH1;
         }
         SETBIT(VPIF->CH2CTRL, CHANEN);
         break;

      default:
         return (ERR_INVALID_PARAMETER);

   }

   return (ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
// Private Function Definitions
//-----------------------------------------------------------------------------

void configReceivePinMux(void)
{
   RK6748_pinmuxConfig(PINMUX_VPIF_RX_REG_0, PINMUX_VPIF_RX_MASK_0, PINMUX_VPIF_RX_VAL_0);
   RK6748_pinmuxConfig(PINMUX_VPIF_RX_REG_1, PINMUX_VPIF_RX_MASK_1, PINMUX_VPIF_RX_VAL_1);
   RK6748_pinmuxConfig(PINMUX_VPIF_RX_REG_2, PINMUX_VPIF_RX_MASK_2, PINMUX_VPIF_RX_VAL_2);
}

void configTransmitPinMux(void)
{
   RK6748_pinmuxConfig(PINMUX_VPIF_TX_REG_0, PINMUX_VPIF_TX_MASK_0, PINMUX_VPIF_TX_VAL_0);
   RK6748_pinmuxConfig(PINMUX_VPIF_TX_REG_1, PINMUX_VPIF_TX_MASK_1, PINMUX_VPIF_TX_VAL_1);
   RK6748_pinmuxConfig(PINMUX_VPIF_TX_REG_2, PINMUX_VPIF_TX_MASK_2, PINMUX_VPIF_TX_VAL_2);
   RK6748_pinmuxConfig(PINMUX_VPIF_TX_REG_3, PINMUX_VPIF_TX_MASK_3, PINMUX_VPIF_TX_VAL_3);
}

void configReceiveVpifRegs(vpif_cap_regs_t *vpif_cap_ch)
{
   // config the data address registers (interlaced).
   vpif_cap_ch->TLUMA = LUMA_TOP_DATA_ADDR;
   vpif_cap_ch->BLUMA = LUMA_BOTTOM_DATA_ADDR;
   vpif_cap_ch->TCHROMA = CHROMA_TOP_DATA_ADDR;
   vpif_cap_ch->BCHROMA = CHROMA_BOTTOM_DATA_ADDR;

   // config horizontal and vertical data size regs for BT.656.
   vpif_cap_ch->HCFG = (268 << 16) | 1440;
   vpif_cap_ch->VCFG0 = (4 << 16) | 20;
   vpif_cap_ch->VCFG1 = (264 << 16) | 266;
   vpif_cap_ch->VCFG2 = (283 << 16) | 1;
   vpif_cap_ch->VSIZE = 525;
   vpif_cap_ch->IMGOFFSET = 720;
}

void configTransmitVpifRegs(vpif_disp_regs_t *vpif_disp_ch)
{
   // config the data address registers (interlaced).
   vpif_disp_ch->TLUMA = LUMA_TOP_DATA_ADDR;
   vpif_disp_ch->BLUMA = LUMA_BOTTOM_DATA_ADDR;
   vpif_disp_ch->TCHROMA = CHROMA_TOP_DATA_ADDR;
   vpif_disp_ch->BCHROMA = CHROMA_BOTTOM_DATA_ADDR;
   
   // config horizontal and vertical data size regs for BT.656.
   vpif_disp_ch->HCFG = (268 << 16) | 1440;
   vpif_disp_ch->VCFG0 = (4 << 16) | 20;
   vpif_disp_ch->VCFG1 = (264 << 16) | 266;
   vpif_disp_ch->VCFG2 = (283 << 16) | 1;
   vpif_disp_ch->VSIZE = 525;
   vpif_disp_ch->IMGOFFSET = 720;
}
