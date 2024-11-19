/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.1
 *
 *	@file		adjunct.h
 *
 *	@brief		Header help-code file
 *	____________________________________________________________________
 *
 *	@attention	<h3><center>
 *				Copyright © 2024 BaseCam Electronics™.<br>
 *				All rights reserved.
 *				</center></h3>
 *
 *				<center><a href="https://www.basecamelectronics.com">
 *				www.basecamelectronics.com</a></center>
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *	http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 *	implied. See the License for the specific language governing
 *	permissions and limitations under the License.
 *	____________________________________________________________________
 */

#ifndef		SERIAL_API_ADJUNCT_H_
#define		SERIAL_API_ADJUNCT_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"string.h"
#include	"stdint.h"
#include	"stdio.h"
#include	"stdlib.h"
#include	"math.h"
#include	"stdarg.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Types and Constants
 */
#if	(defined (__x86_64__) ||defined (__aarch64__) || defined (_M_ARM64))
	#define	_long__
	#define	L32__
#else
	#define	_long__					long
#endif

typedef		unsigned char			ui8;
typedef		unsigned short			ui16;
typedef		_long__ unsigned int	ui32;
typedef		long long unsigned int	ui64;

typedef		signed char				i8;
typedef		short signed int		i16;
typedef		_long__ signed int		i32;
typedef		long long signed int	i64;

#ifndef sbgcOFF
	#define	sbgcOFF					(0)
#endif

#ifndef sbgcON
	#define	sbgcON					(-1)
#endif

#define		BIT_0_SET				0x1U
#define		BIT_1_SET				0x2U
#define		BIT_2_SET				0x4U
#define		BIT_3_SET				0x8U
#define		BIT_4_SET				0x10U
#define		BIT_5_SET				0x20U
#define		BIT_6_SET				0x40U
#define		BIT_7_SET				0x80U
#define		BIT_8_SET				0x100U
#define		BIT_9_SET				0x200U
#define		BIT_10_SET				0x400U
#define		BIT_11_SET				0x800U
#define		BIT_12_SET				0x1000U
#define		BIT_13_SET				0x2000U
#define		BIT_14_SET				0x4000U
#define		BIT_15_SET				0x8000U
#define		BIT_16_SET				0x10000U
#define		BIT_17_SET				0x20000U
#define		BIT_18_SET				0x40000U
#define		BIT_19_SET				0x80000U
#define		BIT_20_SET				0x100000U
#define		BIT_21_SET				0x200000U
#define		BIT_22_SET				0x400000U
#define		BIT_23_SET				0x800000U
#define		BIT_24_SET				0x1000000U
#define		BIT_25_SET				0x2000000U
#define		BIT_26_SET				0x4000000U
#define		BIT_27_SET				0x8000000U
#define		BIT_28_SET				0x10000000U
#define		BIT_29_SET				0x20000000U
#define		BIT_30_SET				0x40000000U
#define		BIT_31_SET				0x80000000U

#define		BUFF_SIZE_(buff)		buff, (sizeof(buff))
#define		TEXT_LENGTH_(text)		text, (strlen(text))
#define		DATA_BLOCK_(arr)		{ sizeof((arr)), countof_((arr)) }
#define		VAR_BLOCK_(var)			{ sizeof((var)), 1 }

#define		PACKED__				__attribute__((packed))
#define		WEAK__					__attribute__((weak))
#define		NORETURN__				__attribute__((noreturn))


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									 Adjunct Objects
 */
/**	@brief	Primitive boolean
 */
typedef enum
{
	sbgcFALSE						= 0,
	sbgcTRUE						= 1

}	sbgcBoolean_t;


/**	@brief	Variable types
 */
typedef enum
{
    sbgcUCHAR						= 1,
    sbgcCHAR						= 2,

    sbgcUSHORT						= 3,
    sbgcSHORT						= 4,

    sbgcUINT						= 5,
    sbgcINT							= 6,

    sbgcFLOAT						= 7,

	/* Var modes */
	sbgcFLAG						= BIT_6_SET,	// This variable is flag. Uses only for reference info
	sbgcDUMMY						= BIT_7_SET,	// This variable is empty or reserved. Uses only for reference info

	sbgcRCHAR						= (sbgcUCHAR | sbgcDUMMY)

}   sbgcVarType_t;

#define		CLEAN_TYPE_MASK			7				// Excluding all under sbgcFLOAT (0b00000111)


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						 Static Functions and Macros
 */
#define		unused_(x)				((void)(x))
#define		nameof_(var)			(#var)
#define		countof_(arr)			(sizeof(arr) / sizeof(*(arr)))
#define		offsetof_(pEnd, pStart)	(((ui8*)(pEnd)) - ((ui8*)(pStart)))
#define		clearbuff_(p)			(memset(p, 0, sizeof(*(p))))
#define		constrain_(val, min, max)\
									((val) < (min) ? (min) : (val) > (max) ? (max) : (val))
#define		rawconstrain_(val, min, max, raw)\
									(((val) <= (min)) || ((val) >= (max)) ? (raw) : (val))
#define		deadbandcross_(val, valOrg, db)\
									((abs((val) - (valOrg)) > (db)) ? 1U : 0U)
#define		toboolean_(val)			((val) && 1U)
#define		lambdafunc_(body)		([](void) { body; } )
#define		calcFreeSpaceFIFO(t, h, max)\
									(((h) >= (t)) ? ((max) - ((h) - (t))) : ((t) - (h)))


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* SERIAL_API_ADJUNCT_H_ */
