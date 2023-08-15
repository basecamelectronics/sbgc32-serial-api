/** ____________________________________________________________________
 *
 *	SBGC32 Serial API Library v1.1
 *
 *	@file		adjunct.h
 *
 *	@brief		Header help-code file
 *	____________________________________________________________________
 *
 *	@attention	<h3><center>
 *				Copyright © 2023 BaseCam Electronics™.<br>
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

#ifndef		_ADJUNCT_H_
#define		_ADJUNCT_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include    "string.h"
#include    "stdio.h"
#include    "stdlib.h"
#include	"math.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						 		 Types and Constants
 */
#if (defined(__x86_64__) || defined(__aarch64__) || defined(_M_ARM64))
	#define	_long__
	#define	_L32__
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

#ifndef SET_OFF
	#define	SET_OFF					(0)
#endif

#ifndef SET_ON
	#define	SET_ON					(-1)
#endif

#define		BIT_0_SET				(1U << 0)
#define		BIT_1_SET				(1U << 1)
#define		BIT_2_SET				(1U << 2)
#define		BIT_3_SET				(1U << 3)
#define		BIT_4_SET				(1U << 4)
#define		BIT_5_SET				(1U << 5)
#define		BIT_6_SET				(1U << 6)
#define		BIT_7_SET				(1U << 7)
#define		BIT_8_SET				(1U << 8)
#define		BIT_9_SET				(1U << 9)
#define		BIT_10_SET				(1U << 10)
#define		BIT_11_SET				(1U << 11)
#define		BIT_12_SET				(1U << 12)
#define		BIT_13_SET				(1U << 13)
#define		BIT_14_SET				(1U << 14)
#define		BIT_15_SET				(1U << 15)
#define		BIT_16_SET				(1U << 16)
#define		BIT_17_SET				(1U << 17)
#define		BIT_18_SET				(1U << 18)
#define		BIT_19_SET				(1U << 19)
#define		BIT_20_SET				(1U << 20)
#define		BIT_21_SET				(1U << 21)
#define		BIT_22_SET				(1U << 22)
#define		BIT_23_SET				(1U << 23)
#define		BIT_24_SET				(1U << 24)
#define		BIT_25_SET				(1U << 25)
#define		BIT_26_SET				(1U << 26)
#define		BIT_27_SET				(1U << 27)
#define		BIT_28_SET				(1U << 28)
#define		BIT_29_SET				(1U << 29)
#define		BIT_30_SET				(1U << 30)
#define		BIT_31_SET				(1U << 31)

#define		PI__					3.14159265

#define		TEXT_SIZE_(text)		text, (strlen(text))
#define 	DATA_BLOCK_(arr)		{ sizeof((arr)), countof_((arr)) }
#define 	VAR_BLOCK_(var)			{ sizeof((var)), 1 }

#define		__PACKED__				__attribute__((packed))
#define		__WEAK__				__attribute__((weak))


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									 Adjunct Objects
 */
/**	@brief	Primitive boolean
 */
typedef enum
{
	FALSE__ 						= 0U,
	TRUE__ 							= 1U

}	Boolean_t;


/**	@brief	Variable types
 */
typedef enum
{
    _UNSIGNED_CHAR_					= 1,
    _SIGNED_CHAR_					= 2,

    _UNSIGNED_SHORT_				= 3,
    _SIGNED_SHORT_					= 4,

    _UNSIGNED_INT_					= 5,
    _SIGNED_INT_					= 6,

    _FLOAT_							= 7,

	/* Var modes */
	_FLAG_							= BIT_6_SET,	// This variable is flag. Uses only for reference info
	_DUMMY_							= BIT_7_SET,	// This variable is empty or reserved. Uses only for reference info

	_RESERVED_CHAR_					= (_UNSIGNED_CHAR_ | _DUMMY_)

}   VarType_t;

#define		CLEAN_TYPE_MASK			7				// Excluding all types under _FLOAT_ (0b00000111)


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						 Static Functions and Macros
 */
#define		unused_(x)				((void)(x))
#define 	nameof_(var)			(#var)
#define		countof_(arr)			(sizeof(arr) / sizeof(*(arr)))
#define		offsetof_(pEnd, pStart)	(((ui8*)(pEnd)) - ((ui8*)(pStart)))
#define		constrain_(val, min, max)\
									((val) < (min) ? (min) : (val) > (max) ? (max) : (val))
#define		rawconstrain_(val, min, max, raw)\
									(((val) <= (min)) || ((val) >= (max)) ? (raw) : (val))
#define		deadbandcross_(val, valOrg, db)\
									((abs((val) - (valOrg)) > (db)) ? 1U : 0U)
#define		toboolean_(val)			((val) && 1U)


static inline ui8 ConvertTypeToByteNum (VarType_t varType)
{
	ui8 res = 0;

	switch (varType & CLEAN_TYPE_MASK)
	{
		case _UNSIGNED_CHAR_ :
		case _SIGNED_CHAR_ :
		case _RESERVED_CHAR_ :
			res = 1;
			break;

		case _UNSIGNED_SHORT_ :
		case _SIGNED_SHORT_ :
			res = 2;
			break;

		case _UNSIGNED_INT_ :
		case _SIGNED_INT_ :
		case _FLOAT_ :
			res = 4;
			break;

		default :
			break;
	}

	return res;
}


static inline ui16 ConvertValueBiniry16_FlagToDecade (ui16 flag)
{
	for (ui8 i = 0; i < 16; i++)
	{
		if (flag == 1)
			return i;

		flag >>= 1;
	}

	return 0;
}


static inline double ConvertRadiansToDegrees (double radian)
{
	return radian * 180.0 / PI__;
}


static inline double ConvertDegreesToRadians (double degree)
{
	return degree * PI__ / 180;
}


static inline i32 SignedCeil (float value)
{
	return (value > 0) ? (ceil(value)) : -(ceil(abs(value)));
}


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _ADJUNCT_H_ */
