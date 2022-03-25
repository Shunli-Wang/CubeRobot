;
; File: intvecs.asm
;
; Brief: Contains interrupt vector table and fetch packets
;
; Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
; ALL RIGHTS RESERVED

;**********************************************************
;				Global Symbols
;**********************************************************
	.global _intcVectorTable
	.global _c_int00
	.global _c674x_nmi_isr
	.global _c674x_rsvd_int2_isr
	.global _c674x_rsvd_int3_isr
	.global _c674x_mask_int4_isr
	.global _c674x_mask_int5_isr
	.global _c674x_mask_int6_isr
	.global _c674x_mask_int7_isr
	.global _c674x_mask_int8_isr
	.global _c674x_mask_int9_isr
	.global _c674x_mask_int10_isr
	.global _c674x_mask_int11_isr
	.global _c674x_mask_int12_isr
	.global _c674x_mask_int13_isr
	.global _c674x_mask_int14_isr
	.global _c674x_mask_int15_isr

;**********************************************************
;				Interrupt Fetch Packet
;**********************************************************
VEC_ENTRY .macro addr
	STW B0,*--B15
	MVKL addr,B0
	MVKH addr,B0
	B B0
	LDW *B15++,B0
	NOP 2
	NOP
	NOP
	.endm

;**********************************************************
;				Interrupt Vector Table
;**********************************************************
	.align 1024
_intcVectorTable:
	VEC_ENTRY _c_int00
	VEC_ENTRY _c674x_nmi_isr
	VEC_ENTRY _c674x_rsvd_int2_isr
	VEC_ENTRY _c674x_rsvd_int3_isr
	VEC_ENTRY _c674x_mask_int4_isr
	VEC_ENTRY _c674x_mask_int5_isr
	VEC_ENTRY _c674x_mask_int6_isr
	VEC_ENTRY _c674x_mask_int7_isr
	VEC_ENTRY _c674x_mask_int8_isr
	VEC_ENTRY _c674x_mask_int9_isr
	VEC_ENTRY _c674x_mask_int10_isr
	VEC_ENTRY _c674x_mask_int11_isr
	VEC_ENTRY _c674x_mask_int12_isr
	VEC_ENTRY _c674x_mask_int13_isr
	VEC_ENTRY _c674x_mask_int14_isr
	VEC_ENTRY _c674x_mask_int15_isr
