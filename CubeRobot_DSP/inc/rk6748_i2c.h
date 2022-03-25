//-----------------------------------------------------------------------------
// \file    evmc6748_i2c.h
// \brief   C6748 i2c registers, bit definitions, and
//          function prototypes.
//
//-----------------------------------------------------------------------------

#ifndef RK6748_I2C_H
#define RK6748_I2C_H

//-----------------------------------------------------------------------------
// Register Structure & Defines
//-----------------------------------------------------------------------------
typedef struct
{
   volatile UINT32 ICOAR;      // 0x0000
   volatile UINT32 ICIMR;      // 0x0004
   volatile UINT32 ICSTR;      // 0x0008
   volatile UINT32 ICCLKL;     // 0x000C
   volatile UINT32 ICCLKH;     // 0x0010
   volatile UINT32 ICCNT;      // 0x0014
   volatile UINT32 ICDRR;      // 0x0018
   volatile UINT32 ICSAR;      // 0x001C
   volatile UINT32 ICDXR;      // 0x0020
   volatile UINT32 ICMDR;      // 0x0024
   volatile UINT32 ICIVR;      // 0x0028
   volatile UINT32 ICEMDR;     // 0x002C
   volatile UINT32 ICPSC;      // 0x0030
   volatile UINT32 REVID1;     // 0x0034
   volatile UINT32 REVID2;     // 0x0038
   volatile UINT32 RSVD0[3];   // 0x003C
   volatile UINT32 ICPFUNC;    // 0x0048
   volatile UINT32 ICPDIR;     // 0x004C
   volatile UINT32 ICPDIN;     // 0x0050
   volatile UINT32 ICPDOUT;    // 0x0054
   volatile UINT32 ICPDSET;    // 0x0058
   volatile UINT32 ICPDCLR;    // 0x005C
} i2c_regs_t;

#define I2C0         ((i2c_regs_t *)I2C0_REG_BASE)
#define I2C1         ((i2c_regs_t *)I2C1_REG_BASE)

// defines for ICSTR.
#define BB           (0x00001000)   // bit 12
#define ICXRDY       (0x00000010)   // bit 4
#define ICRRDY       (0x00000008)   // bit 3

// defines for ICMDR.
#define NACKMOD      (0x00008000)   // bit 15
#define ICMDR_FREE   (0x00004000)   // bit 14
#define STT          (0x00002000)   // bit 13
#define STP          (0x00000800)   // bit 11
#define MST          (0x00000400)   // bit 10
#define TRX          (0x00000200)   // bit 9
#define XA           (0x00000100)   // bit 8
#define RM           (0x00000080)   // bit 7
#define DLB          (0x00000040)   // bit 6
#define IRS          (0x00000020)   // bit 5
#define ICMDR_STB    (0x00000010)   // bit 4
#define FDF          (0x00000008)   // bit 3
#define MASK_BC      (0x00000007)   // bit 0-2

// defines to pass whether we should set stop bit after a write
// and check busy bit before a read.
#define CHECK_BUSY_BEFORE_READ      (1)
#define SKIP_BUSY_BIT_CHECK         (0)
#define SET_STOP_BIT_AFTER_WRITE    (1)
#define SKIP_STOP_BIT_AFTER_WRITE   (0)

// i2c addresses for C6748 EVM.
#define I2C_ADDR_AIC3106      (0x0018)
#define I2C_ADDR_GPIO_UI      (0x0020)
#define I2C_ADDR_GPIO_EX      (0x0021)
#define I2C_ADDR_PMIC         (0x0048)
#define I2C_ADDR_SVIDEODEC    (0x005C)
#define I2C_ADDR_CVIDEODEC    (0x005D)
#define I2C_ADDR_CDCE913      (0x0065)
#define I2C_ADDR_CVIDEOENC    (0x002A)

//-----------------------------------------------------------------------------
// Public Typedefs
//-----------------------------------------------------------------------------
typedef enum
{
   I2C_CLK_100K = 0,
   I2C_CLK_400K
} i2c_clk_e;

//-----------------------------------------------------------------------------
// Public Function Prototypes
//-----------------------------------------------------------------------------

UINT32 I2C_init(i2c_regs_t *i2c, i2c_clk_e in_clock_rate);
UINT32 I2C_read(i2c_regs_t *i2c, UINT16 in_addr, UINT8 *dest_buffer, UINT16 in_length, UINT8 chk_busy);
UINT32 I2C_write(i2c_regs_t *i2c, UINT16 in_addr, UINT8 *src_buffer, UINT16 in_length, UINT8 set_stop);

#endif

