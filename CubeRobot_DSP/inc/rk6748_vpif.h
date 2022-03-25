//-----------------------------------------------------------------------------
// \file    evmc6748_vpif.h
// \brief   C6748 vpif registers, bit definitions, and
//          function prototypes.
//
//-----------------------------------------------------------------------------

#ifndef RK6748_VPIF_H
#define RK6748_VPIF_H

//-----------------------------------------------------------------------------
// Register Structure & Defines
//-----------------------------------------------------------------------------
typedef struct
{
   volatile UINT32 PID;           // 0x0000
   volatile UINT32 CH0CTRL;       // 0x0004
   volatile UINT32 CH1CTRL;       // 0x0008
   volatile UINT32 CH2CTRL;       // 0x000C
   volatile UINT32 CH3CTRL;       // 0x0010
   volatile UINT32 RSVD0[3];      // 0x0014
   volatile UINT32 INTEN;         // 0x0020
   volatile UINT32 INTENSET;      // 0x0024
   volatile UINT32 INTENCLR;      // 0x0028
   volatile UINT32 INTSTAT;       // 0x002C
   volatile UINT32 INTSTATCLR;    // 0x0030
   volatile UINT32 EMUCTRL;       // 0x0034
   volatile UINT32 REQSIZE;       // 0x0038
} vpif_regs_t;

#define VPIF            ((vpif_regs_t *)VPIF_REG_BASE)

// bitmask defines for CHnCTRL (all).
#define CLKEDGE               (0x80000000)   // bit 31
#define FIELDFRAME            (0x00001000)   // bit 12
#define VANC                  (0x00000200)   // bit 9
#define HANC                  (0x00000100)   // bit 8
#define INTFRAME_TOP_ONLY     (0x00000000)   // bit 6-7
#define INTFRAME_BOTTOM_ONLY  (0x00000040)   // bit 6-7
#define INTFRAME_TOP_BOTTOM   (0x00000080)   // bit 6-7
#define YCMUX                 (0x00000008)   // bit 3
#define CHANEN                (0x00000001)   // bit 0

// bitmask defines for CHnCTRL (0-1).
#define DATAWIDTH_8BPP        (0x00000000)   // bit 28-29
#define DATAWIDTH_10BPP       (0x10000000)   // bit 28-29
#define DATAWIDTH_12BPP       (0x20000000)   // bit 28-29
#define FIDINV                (0x00008000)   // bit 15
#define VVINV                 (0x00004000)   // bit 14
#define HVINV                 (0x00002000)   // bit 13
#define VVINV                 (0x00004000)   // bit 14
#define CH01_INTRPROG         (0x00000400)   // bit 10
#define CAPMODE               (0x00000004)   // bit 2
#define INTLINE_SHIFT         (16)

// bitmask defines for CHnCTRL (2-3).
#define CLIPANC               (0x00004000)   // bit 14
#define CLIPVID               (0x00002000)   // bit 13
#define CH23_INTRPROG         (0x00000800)   // bit 11
#define PIXEL_DATA            (0x00000400)   // bit 10
#define CLKEN                 (0x00000002)   // bit 1

// bitmask defines for INT*.
#define INT_FRAME_CH0         (0x00000001)   // bit 0
#define INT_FRAME_CH1         (0x00000002)   // bit 1
#define INT_FRAME_CH2         (0x00000004)   // bit 2
#define INT_FRAME_CH3         (0x00000008)   // bit 3

typedef struct
{
   volatile UINT32 TLUMA;         // 0x0000
   volatile UINT32 BLUMA;         // 0x0004
   volatile UINT32 TCHROMA;       // 0x0008
   volatile UINT32 BCHROMA;       // 0x000C
   volatile UINT32 THANC;         // 0x0010
   volatile UINT32 BHANC;         // 0x0014
   volatile UINT32 TVANC;         // 0x0018
   volatile UINT32 BVANC;         // 0x001C
   volatile UINT32 SUBPIC_CFG;    // 0x0020
   volatile UINT32 IMGOFFSET;     // 0x0024
   volatile UINT32 HANCOFFSET;    // 0x0028
   volatile UINT32 HCFG;          // 0x002C
   volatile UINT32 VCFG0;         // 0x0030
   volatile UINT32 VCFG1;         // 0x0034
   volatile UINT32 VCFG2;         // 0x0038
   volatile UINT32 VSIZE;         // 0x003C
} vpif_cap_regs_t;

#define VPIF_CAP_CH0    ((vpif_cap_regs_t *)VPIF_CAP_CH0_REG_BASE)
#define VPIF_CAP_CH1    ((vpif_cap_regs_t *)VPIF_CAP_CH1_REG_BASE)

// bitmask defines for HCFG.
#define EAV2SAV_SHIFT   (16)

typedef struct
{
   volatile UINT32 TLUMA;         // 0x0000
   volatile UINT32 BLUMA;         // 0x0004
   volatile UINT32 TCHROMA;       // 0x0008
   volatile UINT32 BCHROMA;       // 0x000C
   volatile UINT32 THANC;         // 0x0010
   volatile UINT32 BHANC;         // 0x0014
   volatile UINT32 TVANC;         // 0x0018
   volatile UINT32 BVANC;         // 0x001C
   volatile UINT32 SUBPIC_CFG;    // 0x0020
   volatile UINT32 IMGOFFSET;     // 0x0024
   volatile UINT32 HANCOFFSET;    // 0x0028
   volatile UINT32 HCFG;          // 0x002C
   volatile UINT32 VCFG0;         // 0x0030
   volatile UINT32 VCFG1;         // 0x0034
   volatile UINT32 VCFG2;         // 0x0038
   volatile UINT32 VSIZE;         // 0x003C
   volatile UINT32 THANCPOS;      // 0x0040
   volatile UINT32 THANCSIZE;     // 0x0044
   volatile UINT32 BHANCPOS;      // 0x0048
   volatile UINT32 BHANCSIZE;     // 0x004C
   volatile UINT32 TVANCPOS;      // 0x0050
   volatile UINT32 TVANCSIZE;     // 0x0054
   volatile UINT32 BVANCPOS;      // 0x0058
   volatile UINT32 BVANCSIZE;     // 0x005C
} vpif_disp_regs_t;

#define VPIF_DISP_CH2   ((vpif_disp_regs_t *)VPIF_DISP_CH2_REG_BASE)
#define VPIF_DISP_CH3   ((vpif_disp_regs_t *)VPIF_DISP_CH3_REG_BASE)

//-----------------------------------------------------------------------------
// Public Defines and Macros
//-----------------------------------------------------------------------------

//#define ADDR_VIDEO_DATA_BASE        (0xc1000000)
#define ADDR_VIDEO_DATA_BASE        (0xc1f00020)


//-----------------------------------------------------------------------------
// Public Typedefs
//-----------------------------------------------------------------------------
typedef enum
{
   VIDEO_CONN_COMPOSITE = 0,
   VIDEO_CONN_SVIDEO,
   VIDEO_CONN_CAMERA
} video_connector_e;

//-----------------------------------------------------------------------------
// Public Function Prototypes
//-----------------------------------------------------------------------------
UINT32 VPIF_initReceive(video_connector_e in_conn);
UINT32 VPIF_initTransmit(video_connector_e in_conn);

#endif

