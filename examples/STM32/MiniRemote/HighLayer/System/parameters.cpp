/** ____________________________________________________________________
 *
 *	@file		parameters.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "parameters.h"


Loader SettingsLoader(	FLASH_LOADER_SECTOR,
	 					FLASH_LOADER_ADDRESS);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void Loader::GetSettings (void)
{
	/* Header filling */
	PreserveSettings.PS_FirmwareVersion = MiniRemote.GetFirmwareVersion();
	PreserveSettings.miniRemoteParametersSize = sizeof(MiniRemotePresets_t);
	PreserveSettings.gimbalParametersSize = sizeof(GimbalPresets_t);

	/* MiniRemote settings */
	memcpy(&PreserveSettings.PS_MiniRemoteSettings, &MiniRemote.Presets, PreserveSettings.miniRemoteParametersSize);

	/* Gimbal settings */
	memcpy(&PreserveSettings.PS_GimbalSettings, &Gimbal.Presets, PreserveSettings.gimbalParametersSize);

	/* CRC32 Calculation */
	PreserveSettings.headerCRC32 = CRC32_Module.CalculateCRC32((ui32*)&PreserveSettings, (settingsHeaderWordNum - 1));
	PreserveSettings.parameterCRC32 = CRC32_Module.CalculateCRC32((ui32*)&PreserveSettings.PS_MiniRemoteSettings, settingsParametersWordNum);
}


void Loader::SetSettings (void)
{
	/* MiniRemote settings */
	memcpy(&MiniRemote.Presets, &PreserveSettings.PS_MiniRemoteSettings, sizeof(MiniRemotePresets_t));
	MiniRemote.SetFirmwareVersion(PreserveSettings.PS_FirmwareVersion);

	/* Gimbal settings */
	memcpy(&Gimbal.Presets, &PreserveSettings.PS_GimbalSettings, sizeof(GimbalPresets_t));
}


void Loader::WriteSettings (void)
{
	osSystemLock();

	#if (LOADER_USE_EXTERNAL_EEPROM)

		ui32 wholeSettingsSize = settingsHeaderSize + settingsParametersSize + sizeof(PreserveSettings.parameterCRC32);

		ui8 *preserveSettingsPointer = (ui8*)&PreserveSettings;
		ui16 regAddr = 0;

		while (1)
		{
			if (wholeSettingsSize > EEPROM_BLOCK_DATA_SIZE)
			{
				EEPROM.WriteData(regAddr, preserveSettingsPointer, EEPROM_BLOCK_DATA_SIZE);
				wholeSettingsSize -= EEPROM_BLOCK_DATA_SIZE;
				preserveSettingsPointer += EEPROM_BLOCK_DATA_SIZE;
				regAddr += EEPROM_BLOCK_DATA_SIZE;

				/* Use Simple system delay cause we are in the lock */
				for (ui32 i = 0; i < SystemCoreClock / 1000; i++)
					__NOP();
			}

			else
			{
				EEPROM.WriteData(regAddr, preserveSettingsPointer, wholeSettingsSize);
				break;
			}
		}

	#else
		/* Flash unlocking */
		Unlock();

		/* Sector erasing */
		EraseSector(parametersSector, 1);

		__IO ui32 pAddress = parametersAddress;
		__IO ui32 *pData = (__IO ui32*)&PreserveSettings;
		ui32 wholeSettingsSize = settingsHeaderSize + settingsParametersSize + sizeof(PreserveSettings.parameterCRC32);

		while (wholeSettingsSize)
		{
			SaveWord(pAddress, *(pData));
			pAddress += 4;
			pData++;
			wholeSettingsSize -= 4;
		}

		/* Flash locking */
		Lock();

	#endif

	osSystemUnlock();
}


void Loader::ReadSettings (void)
{
	osSystemLock();

	ui32	parametersSizeTemp,
			parameterWordNumTemp;

	ui32 *buff = (ui32*)osMalloc(settingsHeaderSize);


	#if (LOADER_USE_EXTERNAL_EEPROM)
		EEPROM.ReadData(0, (ui8*)buff, settingsHeaderWordNum * 4);

	#else

		for (ui32 i = 0; i < settingsHeaderWordNum; i++)
			buff[i] = ReadWord(parametersAddress + (i * 4));

	#endif

	/* Header parse */
	PreserveSettings.PS_FirmwareVersion = buff[0];
	PreserveSettings.miniRemoteParametersSize = buff[settingsHeaderWordNum - 3];
	PreserveSettings.gimbalParametersSize = buff[settingsHeaderWordNum - 2];
	PreserveSettings.headerCRC32 = buff[settingsHeaderWordNum - 1];

	parametersSizeTemp = PreserveSettings.miniRemoteParametersSize + PreserveSettings.gimbalParametersSize;
	parameterWordNumTemp = parametersSizeTemp / 4;

	/* CRC32 checking */
	if ((PreserveSettings.headerCRC32 != CRC32_Module.CalculateCRC32(buff, settingsHeaderWordNum - 1)) ||
		(PreserveSettings.headerCRC32 == 0) || (PreserveSettings.headerCRC32 == 0xFFFFFFFF))
		currentState = LS_READ_ERROR;

	else
	{
		osFree(buff);
		osDelay(1);

		buff = (ui32*)osMalloc(parametersSizeTemp + sizeof(PreserveSettings.parameterCRC32));

		#if (LOADER_USE_EXTERNAL_EEPROM)
			EEPROM.ReadData(settingsHeaderWordNum * 4, (ui8*)buff, (parameterWordNumTemp + 1) * 4);

		#else

			for (ui32 i = 0; i < parameterWordNumTemp + 1; i++)  // + parameters CRC32
				buff[i] = ReadWord(parametersAddress + settingsHeaderSize + (i * 4));

		#endif

		PreserveSettings.parameterCRC32 = buff[parameterWordNumTemp];

		if (PreserveSettings.parameterCRC32 != CRC32_Module.CalculateCRC32(buff, parameterWordNumTemp))
			currentState = LS_READ_ERROR;

		else
		{
			if ((PreserveSettings.PS_FirmwareVersion) / 1000 != (MINI_REMOTE_FIRMWARE_VERSION / 1000))
			/* If saved firmware version doesn't match with software version (build version is ignored) */
			{
				PreserveSettings.PS_FirmwareVersion = MINI_REMOTE_FIRMWARE_VERSION;

				/* and if the PreserveSettings are need to change itself structure greatly,
				   we should to call settings re-parse special functions here */
			}

			/* Coping MiniRemote settings */
			memcpy(&PreserveSettings.PS_MiniRemoteSettings, buff,
				   PreserveSettings.miniRemoteParametersSize);

			/* Coping Gimbal settings */
			memcpy(&PreserveSettings.PS_GimbalSettings, &buff[(PreserveSettings.miniRemoteParametersSize / 4)],
				   PreserveSettings.gimbalParametersSize);

			currentState = LS_OK;
		}

		osFree(buff);
	}

	osSystemUnlock();
}


void Loader::Save (void)
{
	GetSettings();
	WriteSettings();
}


sbgcBoolean_t Loader::Boot (void)
{
	ReadSettings();
	SetSettings();

	if (currentState == LS_OK)
		return sbgcTRUE;

	else
		return sbgcFALSE;
}


sbgcBoolean_t Loader::SaveRemoteParameter (void *p)
{
	#if (LOADER_USE_EXTERNAL_EEPROM)

		osSystemLock();

		ui32 shift = (ui32)p - (ui32)&MiniRemote.Presets;
		ui8 dataW [4], dataR [4];
		ui32 ptr = ((ui32)&MiniRemote.Presets) + shift;

		memcpy(dataW, (ui32*)ptr, sizeof(ui32));

		EEPROM.WriteData(settingsHeaderSize + shift, dataW, sizeof(ui32));

		for (ui32 i = 0; i < SystemCoreClock / 5000; i++)
			__NOP();

		EEPROM.ReadData(settingsHeaderSize + shift, dataR, sizeof(ui32));

		for (ui8 i = 0; i < sizeof(ui32); i++)
			if (dataW[i] != dataR[i])
			{
				osSystemUnlock();
				return sbgcFALSE;
			}

		/* Data have written OK. Save new parameter to local settings structure */
		memcpy((void*)(((ui32)&PreserveSettings.PS_MiniRemoteSettings) + shift), dataR, sizeof(ui32));

		PreserveSettings.parameterCRC32 = CRC32_Module.CalculateCRC32((ui32*)&PreserveSettings.PS_MiniRemoteSettings, settingsParametersWordNum);

		memcpy(dataW, &PreserveSettings.parameterCRC32, sizeof(ui32));

		EEPROM.WriteData(settingsHeaderSize + settingsParametersSize, dataW, sizeof(ui32));

		for (ui32 i = 0; i < SystemCoreClock / 5000; i++)
			__NOP();

		EEPROM.ReadData(settingsHeaderSize + settingsParametersSize, dataR, sizeof(ui32));

		for (ui8 i = 0; i < sizeof(ui32); i++)
			if (dataW[i] != dataR[i])
			{
				osSystemUnlock();
				return sbgcFALSE;
			}

		osSystemUnlock();

		return sbgcTRUE;

	#else

		unused_(p);
		return sbgcFALSE;

	#endif
}


sbgcBoolean_t Loader::SaveGimbalParameter (void *p)
{
	#if (LOADER_USE_EXTERNAL_EEPROM)

		osSystemLock();

		ui32 shift = (ui32)p - (ui32)&Gimbal.Presets;
		ui8 dataW [4], dataR [4];
		ui32 ptr = ((ui32)&Gimbal.Presets) + shift;

		memcpy(dataW, (ui32*)ptr, sizeof(ui32));

		EEPROM.WriteData(settingsHeaderSize + sizeof(MiniRemotePresets_t) + shift, dataW, sizeof(ui32));

		for (ui32 i = 0; i < SystemCoreClock / 5000; i++)
			__NOP();

		EEPROM.ReadData(settingsHeaderSize + sizeof(MiniRemotePresets_t) + shift, dataR, sizeof(ui32));

		for (ui8 i = 0; i < sizeof(ui32); i++)
			if (dataW[i] != dataR[i])
			{
				osSystemUnlock();
				return sbgcFALSE;
			}

		/* Data have written OK. Save new parameter to local settings structure */
		memcpy((void*)(((ui32)&PreserveSettings.PS_GimbalSettings) + shift), dataR, sizeof(ui32));

		PreserveSettings.parameterCRC32 = CRC32_Module.CalculateCRC32((ui32*)&PreserveSettings.PS_MiniRemoteSettings, settingsParametersWordNum);

		memcpy(dataW, &PreserveSettings.parameterCRC32, sizeof(ui32));

		EEPROM.WriteData(settingsHeaderSize + settingsParametersSize, dataW, sizeof(ui32));

		for (ui32 i = 0; i < SystemCoreClock / 5000; i++)
			__NOP();

		EEPROM.ReadData(settingsHeaderSize + settingsParametersSize, dataR, sizeof(ui32));

		for (ui8 i = 0; i < sizeof(ui32); i++)
			if (dataW[i] != dataR[i])
			{
				osSystemUnlock();
				return sbgcFALSE;
			}

		osSystemUnlock();

		return sbgcTRUE;

	#else

		unused_(p);
		return sbgcFALSE;

	#endif
}


void Loader::RecoverAdjVars (void)
{
	osSystemLock();

	ui32 shift = (ui32)&Gimbal.Presets.AdjVarGeneral - (ui32)&Gimbal.Presets;

	EEPROM.ReadData(settingsHeaderSize + sizeof(MiniRemotePresets_t) + shift, (ui8*)Gimbal.Presets.AdjVarGeneral,
					sizeof(sbgcAdjVarGeneral_t) * SBGC_ADJ_VARS_MAX_QUANTITY);

	osSystemUnlock();
}


void Loader::ClearAll (void)
{
	EEPROM.ClearAll();
}
