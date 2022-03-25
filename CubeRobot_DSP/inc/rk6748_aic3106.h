//-----------------------------------------------------------------------------
// \file    evmc6748_aic3106.h
// \brief   C6748 aic3106 definitions and function prototypes.
//
//-----------------------------------------------------------------------------

#ifndef RK6748_AIC3106_H
#define RK6748_AIC3106_H

//-----------------------------------------------------------------------------
// Public Defines and Macros
//-----------------------------------------------------------------------------

// aic3106 register defines.
#define AIC3106_REG_PAGESELECT                  (0)
#define AIC3106_REG_RESET                       (1)
#define AIC3106_REG_CODEC_SAMPLE_SELECT         (2)


//-----------------------------------------------------------------------------
// Public Function Prototypes
//-----------------------------------------------------------------------------
UINT32 AIC3106_init(void);
UINT32 AIC3106_readRegister(UINT8 in_reg_addr, UINT8 *dest_buffer);
UINT32 AIC3106_writeRegister(UINT8 in_reg_addr, UINT8 in_data);

#endif
