//----------------------------------------------------------------------------
// \file    types.h
// \brief   .
//
//----------------------------------------------------------------------------

#ifndef TYPES_H
#define TYPES_H


#ifndef UINT64
		typedef unsigned  long long UINT64;
#endif
	
#ifndef SINT64
		typedef signed	  long long SINT64;
#endif
	
#ifndef FLOAT32
		typedef float				FLOAT32;
#endif
	
#ifndef UINT32
		typedef unsigned  int		UINT32;
#endif
	
#ifndef SINT32
		typedef int 				SINT32;
#endif
	
#ifndef UINT16
		typedef unsigned  short 	UINT16;
#endif
	
#ifndef SINT16
		typedef short int			SINT16;
#endif
	
#ifndef UINT8
		typedef unsigned  char		UINT8 ;
#endif
	
#ifndef SINT8
		typedef signed	char		SINT8;
#endif
	
#ifndef VUINT32
		typedef volatile UINT32 	VUINT32;
#endif
	
#ifndef VUINT16
		typedef volatile UINT16 	VUINT16;
#endif
	
	
#ifndef VUINT8
		typedef volatile UINT8		VUINT8;
#endif
	
#ifndef false
    #define false             (UINT8)0
#endif
#ifndef true
    #define true              (UINT8)1
#endif
	
	
#ifndef NULL
    #define NULL	        0
#endif
	
#ifndef BOOL
    #define BOOL             UINT32
#endif

#endif
