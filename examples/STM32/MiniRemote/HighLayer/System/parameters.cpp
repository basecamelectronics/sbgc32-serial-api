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

	osSystemUnlock();
}


void Loader::ReadSettings (void)
{
	ui32	parametersSizeTemp,
			parameterWordNumTemp;

	ui32 *buff = (ui32*)osMalloc(settingsHeaderSize);

	for (ui32 i = 0; i < settingsHeaderWordNum; i++)
		buff[i] = ReadWord(parametersAddress + (i * 4));

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

		for (ui32 i = 0; i < parameterWordNumTemp + 1; i++)  // + parameters CRC32
			buff[i] = ReadWord(parametersAddress + settingsHeaderSize + (i * 4));

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
}


void Loader::Save (void)
{
	GetSettings();
	WriteSettings();
}


Boolean_t Loader::Boot (void)
{
	ReadSettings();
	SetSettings();

	if (currentState == LS_OK)
		return TRUE__;

	else
		return FALSE__;
}

