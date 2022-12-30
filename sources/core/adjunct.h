/** ____________________________________________________________________
 *
 * 	@file		adjunct.h
 *
 *	@brief 		Header help-code file
 *
 *				<center><a href="https://www.basecamelectronics.com">
 *				www.basecamelectronics.com</a>
 *	____________________________________________________________________
 *
 *	@attention	<center><h3>
 *	Copyright © 2023 BaseCam Electronics™.</h3></center>
 *	<center>All rights reserved.</center>
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
#ifndef		SHORT_TYPE_NAMES
#define		SHORT_TYPE_NAMES
	#if defined	__x86_64__
		#define	_long__
		#define	_L32__
	#else
		#define	_long__				long
	#endif

	typedef	unsigned char			ui8;
	typedef	unsigned short			ui16;
	typedef _long__ unsigned int	ui32;

	typedef	signed char				i8;
	typedef	short signed int		i16;
	typedef	_long__ signed int		i32;
#endif


#define		SET_OFF					(0)
#define		SET_ON					(-1)

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


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									  		  Macros
 */
#define		unused_(x)				((void)(x))
#define 	nameof_(var)			#var
#define		countof_(arr)			(sizeof((arr)) / sizeof(*(arr)))
#define		offsetof_(pEnd, pStart)	(((ui8*)(pEnd)) - ((ui8*)(pStart)))
#define		constrain_(val, min, max)\
									((val) < (min) ? (min) : (val) > (max) ? (max) : (val))

#define		TEXT_SIZE_(text)		text, (strlen(text))
#define 	DATA_BLOCK_(arr)		{ sizeof((arr)), countof_((arr)) }
#define 	VAR_BLOCK_(var)			{ sizeof((var)), 1 }

#define		__PACKED__				__attribute__((packed))


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									   Adjunct Enums
 */
typedef enum
{
	FALSE__ 						= 0,
	TRUE__ 							= 1

}	Boolean_t;


typedef enum
{
	_DUMMY_ 						= 0,			// It's not a type

    _UNSIGNED_CHAR_,
    _SIGNED_CHAR_,

    _UNSIGNED_SHORT_,
    _SIGNED_SHORT_,

    _UNSIGNED_INT_,
    _SIGNED_INT_,

    _FLOAT_

}   VarType_t;


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _ADJUNCT_H_ */
