/** ____________________________________________________________________
 *
 *	@file		eeprom.c
 *
 *	@brief 		EEPROM source file
 *	____________________________________________________________________
 *
 *	@attention	<center><h3>
 *	Copyright © 2022 BaseCam Electronics™.</h3></center>
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

#include "eeprom.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	EEPROM_I2C_Reg_Buff
 * 	@{
 */
/**	@brief	Writes data to any device connected to I2C line
 *
 *	@note	I2C_RegBuff_t.dataLen must be always filled and exact.
 *			Be careful and always be aware of which register you are working with.
 *			Also pay special attention to the address of the device and
 *			the data bus on which it is located.
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*I2C_RegBuff - structure with prepared I2C data
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteRegBuffI2C (GeneralSBGC_t *generalSBGC, const I2C_RegBuff_t *I2C_RegBuff, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_I2C_WRITE_REG_BUF);
	WriteByte(&cmd, I2C_RegBuff->deviceAddr);
	WriteByte(&cmd, I2C_RegBuff->regAddr);
	WriteBuff(&cmd, &I2C_RegBuff->data, I2C_RegBuff->dataLen, PM_DEFAULT_8BIT);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Requests reading from any device
			connected to an I2C line
 *
 *	@note	Must be set:\n
 *			I2C_RegBuff_t.deviceAddr \n
 *			I2C_RegBuff_t.regAddr \n
 *			I2C_RegBuff_t.dataLen
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*I2C_RegBuff - structure with prepared service I2C data
 *			and also storing the received data
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadRegBuffI2C (GeneralSBGC_t *generalSBGC, I2C_RegBuff_t *I2C_RegBuff)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_I2C_READ_REG_BUF);
	WriteByte(&cmd, I2C_RegBuff->deviceAddr);
	WriteByte(&cmd, I2C_RegBuff->regAddr);
	WriteByte(&cmd, I2C_RegBuff->dataLen);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_I2C_READ_REG_BUF), "I2C Buffer:") == TX_RX_OK)
		ReadBuff(&cmd, I2C_RegBuff->data, I2C_RegBuff->dataLen, PM_DEFAULT_8BIT);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	EEPROM_Data
 * 	@{
 */
/**	@brief	Writes a block of data to EEPROM to a specified address
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	addr - address for writing. Should be aligned to 64
 *	@param	*data - writable payload array
 *	@param	size - size of data
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteEEPROM (GeneralSBGC_t *generalSBGC, ui32 addr, const i8 *data, ui16 size, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_EEPROM_WRITE);
	WriteLong(&cmd, addr);
	WriteBuff(&cmd, data, size, PM_DEFAULT_8BIT);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Request a reading of block of data from EEPROM
 *			at the specified address and size
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	addr - address of a portion of data, 64-byte aligned
 *	@param	*data - prepared payload space
 *	@param	size - size of readable data
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadEEPROM (GeneralSBGC_t *generalSBGC, ui32 addr, i8 *data, ui16 size)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_EEPROM_READ);
	WriteLong(&cmd, addr);
	WriteWord(&cmd, size);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_EEPROM_READ), "Data from EEPROM:") == TX_RX_OK)
		ReadBuff(&cmd, data, size, PM_DEFAULT_8BIT);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	EEPROM_External_Data
 * 	@{
 */
/**	@brief	Stores any user data to the dedicated area in the EEPROM
 *
 *	@note	size of data[] must be == 128 bytes
 *			(@ref EEPROM_USER_DATA_LEN)\n
 *			Clear the data[] before passing it to a function
 *			or load all 128 bytes
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*data - writable payload array
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteExternalData (GeneralSBGC_t *generalSBGC, const i8 *data, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_EXTERNAL_DATA);
	WriteBuff(&cmd, data, EEPROM_USER_DATA_LEN, PM_DEFAULT_8BIT);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Request user data, stored in the EEPROM
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*data - 128 bytes prepared payload space
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadExternalData (GeneralSBGC_t *generalSBGC, i8 *data)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_EXTERNAL_DATA);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_EXTERNAL_DATA), "Data from External EEPROM:") == TX_RX_OK)
		ReadBuff(&cmd, data, EEPROM_USER_DATA_LEN, PM_DEFAULT_8BIT);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	EEPROM_File
 * 	@{
 */
/**	@brief	Writes the file to the internal filesystem
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*writeReadFile - structure with written file
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteFile (GeneralSBGC_t *generalSBGC, const WriteReadFile_t *writeReadFile, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_FILE);
	WriteWord(&cmd, writeReadFile->fileID);
	WriteWord(&cmd, writeReadFile->fileSize);
	WriteWord(&cmd, writeReadFile->pageOffset);
	WriteBuff(&cmd, &writeReadFile->data, writeReadFile->fileSize, PM_DEFAULT_8BIT);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Read the file from internal filesystem
 *
 *	@note	Must be set:\n
 *			WriteReadFile_t.fileID \n
 *			WriteReadFile_t.pageOffset \n
 *			WriteReadFile_t.maxSize
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*writeReadFile - structure for reading file
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadFile (GeneralSBGC_t *generalSBGC, WriteReadFile_t *writeReadFile)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_FILE);
	WriteWord(&cmd, writeReadFile->fileID);
	WriteWord(&cmd, writeReadFile->pageOffset);
	WriteWord(&cmd, writeReadFile->maxSize);
	WriteEmptyBuff(&cmd, 14);  // reserved[14]

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_FILE), "File from EEPROM:") == TX_RX_OK)
	{
		writeReadFile->fileSize = ReadWord(&cmd);
		writeReadFile->pageOffset = ReadWord(&cmd);
		ReadBuff(&cmd, &writeReadFile->data, writeReadFile->fileSize, PM_DEFAULT_8BIT);
		writeReadFile->errCode = ReadByte(&cmd);
	}

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	EEPROM_Clear
 * 	@{
 */
/**	@brief	Delete all files from internal filesystem
 *
 *	@note	Returns CMD_CONFIRM with parameter ERR_CODE.
 *			Require about a 5 seconds to get confirmation
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ClearFileSystem (GeneralSBGC_t *generalSBGC, ConfirmationState_t *confirmationState)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_FS_CLEAR_ALL);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, CMD_FS_CLEAR_ALL);
	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
