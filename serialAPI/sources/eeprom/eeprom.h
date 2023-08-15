/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.1
 *
 * 	@file		eeprom.h
 *
 *	@brief 		EEPROM header file
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
/** ____________________________________________________________________
 *
 * 	@defgroup	EEPROM SBGC32 EEPROM
 *	@ingroup	Sources
 *		@brief	SBGC32 EEPROM Title Module
 *  ____________________________________________________________________
 *
 * 	@defgroup	EEPROM_I2C_Reg_Buff EEPROM I2C Register Operations
 * 	@ingroup	EEPROM
 * 		@brief	EEPROM I2C Register Operations Module
 *
 *				Covered Commands:
 *
 *				### CMD_I2C_WRITE_REG_BUF
 *				### CMD_I2C_READ_REG_BUF
 *
 * 	@defgroup	EEPROM_Data EEPROM Data Operations
 * 	@ingroup	EEPROM
 * 		@brief	EEPROM Data Operations Module
 *
 *				Covered Commands:
 *
 *				### CMD_EEPROM_WRITE
 *				### CMD_EEPROM_READ
 *
 * 	@defgroup	EEPROM_External_Data EEPROM External Data Operations
 * 	@ingroup	EEPROM
 * 		@brief	EEPROM External Data Operations Module
 *
 *				Covered Commands:
 *
 *				### CMD_WRITE_EXTERNAL_DATA
 *				### CMD_READ_EXTERNAL_DATA
 *
 * 	@defgroup	EEPROM_File EEPROM File Operations
 * 	@ingroup	EEPROM
 * 		@brief	EEPROM File Operations Module
 *
 *				Covered Commands:
 *
 *				### CMD_WRITE_FILE
 *				### CMD_READ_FILE
 *
 * 	@defgroup	EEPROM_Clear EEPROM Clear File System
 * 	@ingroup	EEPROM
 * 		@brief	EEPROM Clear File System Module
 *
 *				Covered Commands:
 *
 *				### CMD_FS_CLEAR_ALL
 *	____________________________________________________________________
 */

#ifndef     _EEPROM_H_
#define     _EEPROM_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_EEPROM_MODULE)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										   Constants
 */
/**	@addtogroup	EEPROM_External_Data
 * 	@{
 */
/**	Size of data for writing and reading operations
 	with external EEPROM */
#define 	EEPROM_USER_DATA_LEN	128
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 						   EEPROM I2C Register flags
 */
/**	@addtogroup	EEPROM_I2C_Reg_Buff
 * 	@{
 */
/**	@note	I2C_RegBuff_t.deviceAddr
 */
typedef enum
{
	DA_I2C_EXTERNAL_PORT			= 0,
	DA_I2C_INTERNAL_PORT			= 1

}	DeviceAddr_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								   EEPROM File flags
 */
/**	@addtogroup	EEPROM_File
 * 	@{
 */
/**	@note	WriteReadFile_t.fileID
 */
typedef enum
{
	FID_FILE_TYPE_SCRIPT 			= 1,
	FID_FILE_TYPE_IMU_CALIB 		= 3,
	FID_FILE_TYPE_COGGING_CORRECTION
									= 4,
	FID_FILE_TYPE_ADJ_VAR_LUT 		= 5,
	FID_FILE_TYPE_PROFILE_SET 		= 6,
	FID_FILE_TYPE_PARAMS 			= 7,
	FID_FILE_TYPE_TUNE 				= 8,
	FID_FILE_TYPE_CANDRV 			= 10

}	FileID_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 					   EEPROM I2C Register structure
 */
/**	@addtogroup	EEPROM_I2C_Reg_Buff
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		I2C_RegBuff parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_I2C_WRITE_REG_BUF
 *			CMD_I2C_READ_REG_BUF
 *
 *			TX/RX ? bytes
 *
 *	@ref	SBGC32_WriteRegBuffI2C function\n
 *	@ref	SBGC32_ReadRegBuffI2C function
 */
typedef struct __PACKED__
{
	ui8		deviceAddr,								/*!<  I2C device address															*/
			regAddr,								/*!<  Register address (only 1-byte addressing is supported)						*/
			dataLen;								/*!<  Length of data to write/read													*/

	i8 		data [240];								/*!<  Data length depends on the dataLen parameter in the request					*/

}			I2C_RegBuff_t;
/**	@}
 */


/**	@addtogroup	EEPROM_File
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		WriteReadFile parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_WRITE_FILE
 *			CMD_READ_FILE
 *
 *			TX/RX ? bytes
 *
 *	@ref	SBGC32_WriteFile function\n
 *	@ref	SBGC32_ReadFile function
 */
typedef struct __PACKED__
{
	ui16	fileID,									/*!<  See @ref FileID_t enumeration													*/
			fileSize,								/*!<  Full size of a file															*/
			pageOffset,								/*!<  Offset from the beginning, in pages. 1 page = 64 bytes						*/
			maxSize;

	ui8		data [240];								/*!<  Payload data																	*/
	/* In case of errors */
	ui8		errCode;								/*!<  See @ref ErrorCode_t enumeration												*/

}			WriteReadFile_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
/**	@addtogroup	EEPROM_I2C_Reg_Buff
 * 	@{
 */
TxRxStatus_t SBGC32_WriteRegBuffI2C (GeneralSBGC_t *generalSBGC, const I2C_RegBuff_t *I2C_RegBuff);
TxRxStatus_t SBGC32_ReadRegBuffI2C (GeneralSBGC_t *generalSBGC, I2C_RegBuff_t *I2C_RegBuff);
/**	@}
 */


/**	@addtogroup	EEPROM_Data
 * 	@{
 */
TxRxStatus_t SBGC32_WriteEEPROM (GeneralSBGC_t *generalSBGC, ui32 addr, const i8 *data, ui16 size);
TxRxStatus_t SBGC32_ReadEEPROM (GeneralSBGC_t *generalSBGC, ui32 addr, i8 *data, ui16 size);
/**	@}
 */


/**	@addtogroup	EEPROM_External_Data
 * 	@{
 */
TxRxStatus_t SBGC32_WriteExternalData (GeneralSBGC_t *generalSBGC, const i8 *data);
TxRxStatus_t SBGC32_ReadExternalData (GeneralSBGC_t *generalSBGC, i8 *data);
/**	@}
 */


/**	@addtogroup	EEPROM_File
 * 	@{
 */
TxRxStatus_t SBGC32_WriteFile (GeneralSBGC_t *generalSBGC, const WriteReadFile_t *writeReadFile);
TxRxStatus_t SBGC32_ReadFile (GeneralSBGC_t *generalSBGC, WriteReadFile_t *writeReadFile);
/**	@}
 */


/**	@addtogroup	EEPROM_Clear
 * 	@{
 */
TxRxStatus_t SBGC32_ClearFileSystem (GeneralSBGC_t *generalSBGC);
/**	@}
 */

#endif		/* SBGC_EEPROM_MODULE */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif      /* _EEPROM_H_ */
