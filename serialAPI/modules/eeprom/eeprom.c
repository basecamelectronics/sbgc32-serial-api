/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		eeprom.c
 *
 *	@brief		EEPROM source file
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

#include "../../sbgc32.h"


#if (SBGC_EEPROM_MODULE)

/* Borrowed Functions  -------------------------------------------------
 */
extern sbgcCommandStatus_t SBGC32_SendEmptyCommand (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t cmdID
													/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	EEPROM_I2C_Reg_Buff
 *	@{
 */
/**	@brief	Writes data to any device connected to I2C line
 *
 *	####	TX —> CMD_I2C_WRITE_REG_BUF :	2 + sbgcI2C_RegBuff_t.dataLen bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	sbgcI2C_RegBuff_t.dataLen must be always filled and exact.
 *			Also it should not exceed SBGC_EEPROM_MAX_BUFF_DATA_LEN
 *			(240). Be careful and always be aware of which
 *			register you are working with. Also pay special
 *			attention to the address of the device and
 *			the data bus on which it is located.
 *			Whole struct must be filled
 *
 *	@attention	sbgcI2C_RegBuff_t.dataLen should not exceed
 *				SBGC_EEPROM_MAX_BUFF_DATA_LEN (240)
 *
 *	@code

			#define SBGC_I2C_DEVICE_ADDR 0x69
			#define SBGC_I2C_REG_ADDR 64

			sbgcI2C_RegBuff_t I2C_RegBuff;
			i8 dataArr [] = { "Hello, world!" };

			I2C_RegBuff.deviceAddr = SBGC_I2C_DEVICE_ADDR;
			I2C_RegBuff.regAddr = SBGC_I2C_REG_ADDR;
			I2C_RegBuff.dataLen = sizeof(dataArr);
			memcpy(I2C_RegBuff.data, dataArr, sizeof(dataArr));

			SBGC32_WriteRegBuffI2C(&SBGC32_Device, &I2C_RegBuff, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*I2C_RegBuff - structure with prepared I2C data
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_WriteRegBuffI2C (sbgcGeneral_t *gSBGC, const sbgcI2C_RegBuff_t *I2C_RegBuff, sbgcConfirm_t *confirm
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertParam(I2C_RegBuff->dataLen, 1, SBGC_EEPROM_MAX_BUFF_DATA_LEN)

	gSBGC->_api->startWrite(gSBGC, CMD_I2C_WRITE_REG_BUF SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, I2C_RegBuff->deviceAddr);
	gSBGC->_api->writeByte(gSBGC, I2C_RegBuff->regAddr);
	gSBGC->_api->writeBuff(gSBGC, &I2C_RegBuff->data, I2C_RegBuff->dataLen);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_I2C_WRITE_REG_BUF SBGC_ADVANCED_ARGS__);

	gSBGC->_api->bound(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Requests reading from any device
 *			connected to an I2C line
 *
 *	####	TX —> CMD_I2C_READ_REG_BUF :	3 bytes
 *	####	RX <— CMD_I2C_READ_REG_BUF :	sbgcI2C_RegBuff_t.dataLen bytes
 *
 *	@pre	Must be set:\n
 *			sbgcI2C_RegBuff_t.deviceAddr \n
 *			sbgcI2C_RegBuff_t.regAddr \n
 *			sbgcI2C_RegBuff_t.dataLen
 *
 *	@code

			#define SBGC_I2C_DEVICE_ADDR 0x69
			#define SBGC_I2C_REG_ADDR 64
			#define SBGC_I2C_DATA_LENGHT 15

			sbgcI2C_RegBuff_t I2C_RegBuff;

			I2C_RegBuff.deviceAddr = SBGC_I2C_DEVICE_ADDR;
			I2C_RegBuff.regAddr = SBGC_I2C_REG_ADDR;
			I2C_RegBuff.dataLen = SBGC_I2C_DATA_LENGHT;

			SBGC32_ReadRegBuffI2C(&SBGC32_Device, &I2C_RegBuff);

			#if (SBGC_NEED_DEBUG)
				DebugSBGC32_PrintBuffer(&SBGC32_Device, (char*)I2C_RegBuff.data, I2C_RegBuff.dataLen);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*I2C_RegBuff - structure with prepared service
 *			I2C data and also storing the received data
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_ReadRegBuffI2C (sbgcGeneral_t *gSBGC, sbgcI2C_RegBuff_t *I2C_RegBuff
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_I2C_READ_REG_BUF SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, I2C_RegBuff->deviceAddr);
	gSBGC->_api->writeByte(gSBGC, I2C_RegBuff->regAddr);
	gSBGC->_api->writeByte(gSBGC, I2C_RegBuff->dataLen);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_I2C_READ_REG_BUF SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, I2C_RegBuff->data, SBGC_MAX_PAYLOAD_SIZE);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->bound(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	EEPROM_Data
 *	@{
 */
/**	@brief	Writes a block of data to EEPROM to a specified address
 *
 *	####	TX —> CMD_EEPROM_WRITE :		4 + size bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	Data should be aligned to 64-byte page
 *
 *	@attention	Incorrect use of this function can
 *				damage the controller settings
 *
 *	@code

			i8 dataWrite [SBGC_EEPROM_ALIGN_DATA_LEN] = { 0 };
			ui32 addr = (SBGC_EEPROM_MAX_REQ_ADDR + 1) - 64;

			memcpy(dataWrite, TEXT_LENGTH_("Hello, world!"));

			// Write data to the last EEPROM page
			SBGC32_WriteEEPROM(&SBGC32_Device, addr, dataWrite, SBGC_EEPROM_ALIGN_DATA_LEN, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	addr - 0 --> 32767. Address for writing.
 *			Should be aligned to 64
 *	@param	*data - writable payload array
 *	@param	size - size of data
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_WriteEEPROM (sbgcGeneral_t *gSBGC, ui32 addr, const i8 *data, ui16 size, sbgcConfirm_t *confirm
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertParam(addr, 0, SBGC_EEPROM_MAX_REQ_ADDR)
	sbgcAssertParam(size, SBGC_EEPROM_ALIGN_DATA_LEN, SBGC_MAX_SER_BUFF_SIZE - SBGC_EEPROM_ALIGN_DATA_LEN)

	gSBGC->_api->startWrite(gSBGC, CMD_EEPROM_WRITE SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeLong(gSBGC, addr);
	gSBGC->_api->writeBuff(gSBGC, data, size);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_EEPROM_WRITE SBGC_ADVANCED_ARGS__);

	gSBGC->_api->bound(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_ReadEEPROM function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostReadEEPROM (sbgcGeneral_t *gSBGC)
{
	ui8 bytesSkip = sizeof(ui32);

	if (serialAPI_CurCmd_->_destinationSize < (serialAPI_CurCmd_->_payloadSize - bytesSkip))
		SerialAPI_FatalErrorHandler();

	gSBGC->_api->skipBytes(gSBGC, bytesSkip);  // skip address
	gSBGC->_api->readBuff(gSBGC, serialAPI_CurCmdDest_, serialAPI_CurCmd_->_payloadSize - bytesSkip);
}

/**	@brief	Requests a reading of block of data from EEPROM
 *			at the specified address and size
 *
 *	####	TX —> CMD_EEPROM_READ :	6 bytes
 *	####	RX <— CMD_EEPROM_READ :	4 + size bytes
 *
 *	@code

			i8 dataRead [SBGC_EEPROM_ALIGN_DATA_LEN];
			ui32 addr = (SBGC_EEPROM_MAX_REQ_ADDR + 1) - 64;

			// Read from the last EEPROM page
			SBGC32_ReadEEPROM(&SBGC32_Device, addr, dataRead, SBGC_EEPROM_ALIGN_DATA_LEN);

			#if (SBGC_NEED_DEBUG)
				DebugSBGC32_PrintBuffer(&SBGC32_Device, (char*)dataRead, SBGC_EEPROM_ALIGN_DATA_LEN);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	addr - address of a portion of data, 64-byte aligned
 *	@param	*data - prepared payload space
 *	@param	size - size of read data
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_ReadEEPROM (sbgcGeneral_t *gSBGC, ui32 addr, i8 *data, ui16 size
									   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertParam(addr, 0, SBGC_EEPROM_MAX_REQ_ADDR)
	sbgcAssertParam(size, SBGC_EEPROM_ALIGN_DATA_LEN, SBGC_MAX_SER_BUFF_SIZE - SBGC_EEPROM_ALIGN_DATA_LEN)

	gSBGC->_api->startWrite(gSBGC, CMD_EEPROM_READ SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeLong(gSBGC, addr);
	gSBGC->_api->writeWord(gSBGC, size);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_EEPROM_READ SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostReadEEPROM, data, size);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->bound(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	EEPROM_External_Data
 *	@{
 */
/**	@brief	Stores any user data to the dedicated area in the EEPROM
 *
 *	####	TX —> CMD_WRITE_EXTERNAL_DATA :	128 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@note	size of data[] must be == SBGC_EEPROM_USER_DATA_LEN
 *			bytes (128)
 *
 *	@code

 			i8 dataWrite [SBGC_EEPROM_USER_DATA_LEN] = { 0 };

			memcpy(dataWrite, TEXT_LENGTH_("Hello, world!"));

			SBGC32_WriteExternalData(&SBGC32_Device, dataWrite, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*data - writable payload array
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_WriteExternalData (sbgcGeneral_t *gSBGC, const i8 *data, sbgcConfirm_t *confirm
											  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_WRITE_EXTERNAL_DATA SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, data, SBGC_EEPROM_USER_DATA_LEN);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_WRITE_EXTERNAL_DATA SBGC_ADVANCED_ARGS__);

	gSBGC->_api->bound(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Requests user data, stored in the EEPROM
 *
 *	####	TX —> CMD_READ_EXTERNAL_DATA	with no payload
 *	####	RX <— CMD_READ_EXTERNAL_DATA :	128 bytes
 *
 *	@note	size of data[] must be == SBGC_EEPROM_USER_DATA_LEN
 *			bytes (128)
 *
 *	@code

 			i8 dataRead [SBGC_EEPROM_USER_DATA_LEN];

			SBGC32_ReadExternalData(&SBGC32_Device, dataRead);

			#if (SBGC_NEED_DEBUG)
				DebugSBGC32_PrintBuffer(&SBGC32_Device, (char*)dataRead, SBGC_EEPROM_USER_DATA_LEN);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*data - 128 bytes prepared payload space
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_ReadExternalData (sbgcGeneral_t *gSBGC, i8 *data
											 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_READ_EXTERNAL_DATA SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_READ_EXTERNAL_DATA SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, data, SBGC_EEPROM_USER_DATA_LEN);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->bound(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	EEPROM_File
 *	@{
 */
/**	@brief	Writes the file to the internal filesystem
 *
 *	####	TX —> CMD_WRITE_FILE :	128 bytes
 *	####	RX <— CMD_CONFIRM :		1-6 bytes
 *
 *	@pre	Must be set:\n
 *			WriteReadFile_t.fileID \n
 *			WriteReadFile_t.fileSize \n
 *			WriteReadFile_t.pageOffset \n
 *			WriteReadFile_t.data
 *
 *	@code

			#define SBGC_EEPROM_FILE_SIZE 128
			#define SBGC_EEPROM_FILE_PAGE_OFFSET 30

			sbgcWriteReadFile_t WriteReadFile;
			ui8 dataArr [SBGC_EEPROM_MAX_BUFF_DATA_LEN];

			WriteReadFile.fileID = FID_FILE_TYPE_SCRIPT;
			WriteReadFile.fileSize = SBGC_EEPROM_FILE_SIZE;
			WriteReadFile.pageOffset = SBGC_EEPROM_FILE_PAGE_OFFSET;
			memcpy(WriteReadFile.data, dataArr, SBGC_EEPROM_MAX_BUFF_DATA_LEN);

			SBGC32_WriteFile(&SBGC32_Device, &WriteReadFile, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*writeReadFile - structure with written file
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_WriteFile (sbgcGeneral_t *gSBGC, const sbgcWriteReadFile_t *writeReadFile, sbgcConfirm_t *confirm
									  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_WRITE_FILE SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeWord(gSBGC, writeReadFile->fileID);
	gSBGC->_api->writeWord(gSBGC, writeReadFile->fileSize);
	gSBGC->_api->writeWord(gSBGC, writeReadFile->pageOffset);
	gSBGC->_api->writeBuff(gSBGC, &writeReadFile->data, writeReadFile->fileSize);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_WRITE_FILE SBGC_ADVANCED_ARGS__);

	gSBGC->_api->bound(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_ReadFile function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostReadFile (sbgcGeneral_t *gSBGC)
{
	sbgcWriteReadFile_t *writeReadFile = (sbgcWriteReadFile_t*)serialAPI_CurCmdDest_;

	writeReadFile->fileSize = gSBGC->_api->readWord(gSBGC);
	writeReadFile->pageOffset = gSBGC->_api->readWord(gSBGC);
	gSBGC->_api->readBuff(gSBGC, writeReadFile->data, writeReadFile->fileSize);
	writeReadFile->errCode = gSBGC->_api->readByte(gSBGC);
}

/**	@brief	Reads the file from internal filesystem
 *
 *	####	TX —> CMD_READ_FILE :	20 bytes
 *	####	RX <— CMD_READ_FILE :	5 + sbgcWriteReadFile_t.fileSize bytes
 *
 *	@pre	Must be set:\n
 *			sbgcWriteReadFile_t.fileID \n
 *			sbgcWriteReadFile_t.pageOffset \n
 *			sbgcWriteReadFile_t.maxSize
 *
 *	@code

			#define SBGC_EEPROM_FILE_PAGE_OFFSET 30
			#define SBGC_EEPROM_FILE_MAX_SIZE 128

			sbgcWriteReadFile_t WriteReadFile;

			WriteReadFile.fileID = FID_FILE_TYPE_SCRIPT;
			WriteReadFile.pageOffset = SBGC_EEPROM_FILE_PAGE_OFFSET;
			WriteReadFile.maxSize = SBGC_EEPROM_FILE_MAX_SIZE;

			SBGC32_ReadFile(&SBGC32_Device, &WriteReadFile);

			#if (SBGC_NEED_DEBUG)
				DebugSBGC32_PrintBuffer(&SBGC32_Device, (char*)WriteReadFile.data, SBGC_EEPROM_FILE_MAX_SIZE);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*writeReadFile - structure for reading file
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_ReadFile (sbgcGeneral_t *gSBGC, sbgcWriteReadFile_t *writeReadFile
									 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_READ_FILE SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeWord(gSBGC, writeReadFile->fileID);
	gSBGC->_api->writeWord(gSBGC, writeReadFile->pageOffset);
	gSBGC->_api->writeWord(gSBGC, writeReadFile->maxSize);
	gSBGC->_api->writeEmptyBuff(gSBGC, 14);  // reserved[14]
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_READ_FILE SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostReadFile, writeReadFile, sizeof(sbgcWriteReadFile_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->bound(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	EEPROM_Clear
 *	@{
 */
/**	@brief	Deletes all files from internal filesystem
 *
 *	####	TX —> CMD_FS_CLEAR_ALL	with no payload
 *
 *	@post	Returns CMD_CONFIRM with parameter ERR_CODE.
 *			Require about 5 seconds to get confirmation.
 *			Call the @ref SBGC32_CheckConfirmation function
 *			passing it the CMD_FS_CLEAR_ALL argument
 *
 *	@attention	<h3>This function will erase
 *				all settings in the EEPROM!</h3>
 *
 *	@code

			// Attention! This function will erase all settings in the EEPROM!
			SBGC32_ClearFileSystem(&SBGC32_Device);

			#if (SBGC_NEED_CONFIRM_CMD)

				// ...
				// After approximately 5 seconds
				SBGC32_CheckConfirmation(&SBGC32_Device, SBGC_NO_CONFIRM, CMD_FS_CLEAR_ALL);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_ClearFileSystem (sbgcGeneral_t *gSBGC
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	return SBGC32_SendEmptyCommand(gSBGC, CMD_FS_CLEAR_ALL SBGC_ADVANCED_ARGS__);
}
/**	@}
 */

#endif /* SBGC_EEPROM_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
