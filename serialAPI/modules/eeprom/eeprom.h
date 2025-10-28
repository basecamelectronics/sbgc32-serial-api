/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		eeprom.h
 *
 *	@brief		EEPROM header file
 *	____________________________________________________________________
 *
 *	@attention	<h3><center>
 *				Copyright © 2025 BaseCam Electronics™.<br>
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
/**	____________________________________________________________________
 *
 *	@defgroup	EEPROM SBGC32 EEPROM
 *	@ingroup	Modules
 *		@brief	SBGC32 EEPROM Title Module
 *	____________________________________________________________________
 *
 *	@defgroup	EEPROM_I2C_Reg_Buff EEPROM I2C Register Operations
 *	@ingroup	EEPROM
 *		@brief	EEPROM I2C Register Operations Module
 *
 *				Covered Commands:
 *
 *				### CMD_I2C_WRITE_REG_BUF
 *				### CMD_I2C_READ_REG_BUF
 *
 *	@defgroup	EEPROM_Data EEPROM Data Operations
 *	@ingroup	EEPROM
 *		@brief	EEPROM Data Operations Module
 *
 *				Covered Commands:
 *
 *				### CMD_EEPROM_WRITE
 *				### CMD_EEPROM_READ
 *
 *	@defgroup	EEPROM_External_Data EEPROM External Data Operations
 *	@ingroup	EEPROM
 *		@brief	EEPROM External Data Operations Module
 *
 *				Covered Commands:
 *
 *				### CMD_WRITE_EXTERNAL_DATA
 *				### CMD_READ_EXTERNAL_DATA
 *
 *	@defgroup	EEPROM_File EEPROM File Operations
 *	@ingroup	EEPROM
 *		@brief	EEPROM File Operations Module
 *
 *				Covered Commands:
 *
 *				### CMD_WRITE_FILE
 *				### CMD_READ_FILE
 *
 *	@defgroup	EEPROM_Clear EEPROM Clear File System
 *	@ingroup	EEPROM
 *		@brief	EEPROM Clear File System Module
 *
 *				Covered Commands:
 *
 *				### CMD_FS_CLEAR_ALL
 *	____________________________________________________________________
 */

#ifndef		MODULES_EEPROM_H_
#define		MODULES_EEPROM_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_EEPROM_MODULE)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										   Constants
 */
/**	@addtogroup	EEPROM_I2C_Reg_Buff
 *	@{
 */
/**	Size of data for writing and reading operations with
	I2C devices by @ref SBGC32_WriteRegBuffI2C
	and @ref SBGC32_ReadRegBuffI2C functions */
#define		SBGC_EEPROM_MAX_BUFF_DATA_LEN	240U
/**	@}
 */


/**	@addtogroup	EEPROM_Data
 *	@{
 */
/** See @ref SBGC32_WriteEEPROM and
	@ref SBGC32_ReadEEPROM functions */
#define		SBGC_EEPROM_ALIGN_DATA_LEN		64U

/** Maximal address of SBGC32's EEPROM IC */
#define		SBGC_EEPROM_MAX_REQ_ADDR		32767U
/**	@}
 */


/**	@addtogroup	EEPROM_External_Data
 *	@{
 */
/**	Size of data for writing and reading operations with
	external EEPROM by @ref SBGC32_WriteExternalData
	and @ref SBGC32_ReadExternalData functions */
#define		SBGC_EEPROM_USER_DATA_LEN		128U
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						   EEPROM I2C Register flags
 */
/**	@addtogroup	EEPROM_I2C_Reg_Buff
 *	@{
 */
/**	@note	sbgcI2C_RegBuff_t.deviceAddr
 */
typedef enum
{
	DA_I2C_EXTERNAL_PORT			= 0,
	DA_I2C_INTERNAL_PORT			= 1

}	sbgcDeviceAddr_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   EEPROM File flags
 */
/**	@addtogroup	EEPROM_File
 *	@{
 */
/**	@note	sbgcWriteReadFile_t.fileID
 */
typedef enum
{
	FID_FILE_TYPE_SCRIPT			= 1,
	FID_FILE_TYPE_IMU_CALIB			= 3,
	FID_FILE_TYPE_COGGING_CORRECTION
									= 4,
	FID_FILE_TYPE_ADJ_VAR_LUT		= 5,
	FID_FILE_TYPE_PROFILE_SET		= 6,
	FID_FILE_TYPE_PARAMS			= 7,
	FID_FILE_TYPE_TUNE				= 8,
	FID_FILE_TYPE_CANDRV			= 10

}	sbgcFileID_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					   EEPROM I2C Register structure
 */
/**	@addtogroup	EEPROM_I2C_Reg_Buff
 *	@{
 */
/**	@brief	Structure type for work with
 *			I2C_RegBuff parameters
 *
 *	@ref	SBGC32_WriteRegBuffI2C function\n
 *	@ref	SBGC32_ReadRegBuffI2C function
 */
typedef struct PACKED__
{
	ui8		deviceAddr,								/*!<  I2C device address															*/
			regAddr,								/*!<  Register address (only 1-byte addressing is supported)						*/
			dataLen;								/*!<  Length of data to write/read													*/

	i8		data [SBGC_MAX_PAYLOAD_SIZE];			/*!<  Data length depends on the dataLen parameter in the request					*/

}	sbgcI2C_RegBuff_t;
/**	@}
 */


/**	@addtogroup	EEPROM_File
 *	@{
 */
/**	@brief	Structure type for work with
 *			WriteReadFile parameters
 *
 *	@ref	SBGC32_WriteFile function\n
 *	@ref	SBGC32_ReadFile function
 */
typedef struct PACKED__
{
	ui16	fileID,									/*!<  See @ref sbgcFileID_t enumeration												*/
			fileSize,								/*!<  Full size of a file															*/
			pageOffset,								/*!<  Offset from the beginning, in pages. 1 page = 64 bytes						*/
			maxSize;

	ui8		data [SBGC_EEPROM_MAX_BUFF_DATA_LEN];	/*!<  Payload data																	*/
	/* In case of errors */
	ui8		errCode;								/*!<  See @ref sbgcErrorCode_t enumeration											*/

}	sbgcWriteReadFile_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
/**	@cond
 */
/**	@addtogroup	EEPROM_I2C_Reg_Buff
 *	@{
 */
sbgcCommandStatus_t SBGC32_WriteRegBuffI2C (sbgcGeneral_t *gSBGC, const sbgcI2C_RegBuff_t *I2C_RegBuff, sbgcConfirm_t *confirm
											SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadRegBuffI2C (sbgcGeneral_t *gSBGC, sbgcI2C_RegBuff_t *I2C_RegBuff SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	EEPROM_Data
 *	@{
 */
sbgcCommandStatus_t SBGC32_WriteEEPROM (sbgcGeneral_t *gSBGC, ui32 addr, const i8 *data, ui16 size, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadEEPROM (sbgcGeneral_t *gSBGC, ui32 addr, i8 *data, ui16 size SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	EEPROM_External_Data
 *	@{
 */
sbgcCommandStatus_t SBGC32_WriteExternalData (sbgcGeneral_t *gSBGC, const i8 *data, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadExternalData (sbgcGeneral_t *gSBGC, i8 *data SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	EEPROM_File
 *	@{
 */
sbgcCommandStatus_t SBGC32_WriteFile (sbgcGeneral_t *gSBGC, const sbgcWriteReadFile_t *writeReadFile, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadFile (sbgcGeneral_t *gSBGC, sbgcWriteReadFile_t *writeReadFile SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	EEPROM_Clear
 *	@{
 */
sbgcCommandStatus_t SBGC32_ClearFileSystem (sbgcGeneral_t *gSBGC SBGC_ADVANCED_PARAMS__);
/**	@}
 */
/**	@endcond
 */

#endif /* SBGC_EEPROM_MODULE */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* MODULES_EEPROM_H_ */
