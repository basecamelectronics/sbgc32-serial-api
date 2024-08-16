/** ____________________________________________________________________
 *
 *	@file		parameters.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_PARAMETERS_H_
#define		_PARAMETERS_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"EEPROM.h"
#include	"internalFlash.h"
#include	"CRC32.h"

#include	"gimbal.h"
#include	"system.h"


typedef enum
{
	LS_OK							= 0,

	LS_GET_SETTINGS,
	LS_WRITE_SETTINGS,
	LS_READ_SETTINGS,
	LS_SET_SETTINGS,

	LS_WRITE_ERROR,
	LS_READ_ERROR

}	LoaderState_t;


typedef struct __attribute__((aligned(4)))
{
	/* Header */
	ui32				PS_FirmwareVersion;			// Always at the start of header

	ui32				miniRemoteParametersSize;
	ui32				gimbalParametersSize;
	ui32				headerCRC32;

	/* Parameters */
	MiniRemotePresets_t	PS_MiniRemoteSettings;		// Constantly start of parameters
	GimbalPresets_t		PS_GimbalSettings;

	/* CRC32 */
	ui32				parameterCRC32;

}	PreserveSettings_t;


class Loader : public InternalFlashHandle
{
	private :

		LoaderState_t		currentState;

		ui32				parametersSector;
		ui32				parametersAddress;

		PreserveSettings_t	PreserveSettings;

		ui32				settingsHeaderSize,
							settingsHeaderWordNum,
							settingsParametersSize,
							settingsParametersWordNum;


	public :

		Loader(				ui32 parametersSector,
							ui32 parametersAddress)
							{
								this->parametersSector = parametersSector;
								this->parametersAddress = parametersAddress;

								settingsHeaderSize = (ui32)&PreserveSettings.headerCRC32 - (ui32)&PreserveSettings.PS_FirmwareVersion +
											sizeof(PreserveSettings.headerCRC32);
								settingsHeaderWordNum = settingsHeaderSize / 4;

								settingsParametersSize = sizeof(PreserveSettings.PS_MiniRemoteSettings) +
										sizeof(PreserveSettings.PS_GimbalSettings);
								settingsParametersWordNum = settingsParametersSize / 4;
							}

		void				GetSettings (void);
		void				SetSettings (void);
		void				UpdateSettings (ui32 *parametersBuff);

		void				WriteSettings (void);
		void				ReadSettings (void);

		void				Save (void);
		sbgcBoolean_t		Boot (void);

		sbgcBoolean_t		SaveRemoteParameter (void *p);
		sbgcBoolean_t		SaveGimbalParameter (void *p);
		void				RecoverAdjVars (void);
		void				ClearAll (void);

		LoaderState_t		GetCurrentState (void) { return currentState; }

};

extern Loader SettingsLoader;


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _PARAMETERS_H_ */
