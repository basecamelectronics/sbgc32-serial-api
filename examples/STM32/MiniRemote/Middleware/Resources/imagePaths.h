/** ____________________________________________________________________
 *
 *	@file		imagePaths.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_IMAGE_PATHS_H_
#define		_IMAGE_PATHS_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"romfs_files.h"

#define		SHORTCUT_PATHS_ORIGIN	IPR_GYRO_CALIB


typedef enum
{
	IPR_ARROW_RETURN_UP				= 0,
	IPR_ARROW_RETURN_LEFT,

	IPR_ARROW_UP,
	IPR_ARROW_DOWN,

	IPR_ADJ_VARS_SYNC,
	IPR_ADJ_VARS_EDIT,
	IPR_ADJ_VARS_ADD,
	IPR_ADJ_VARS_REMOVE,

	IPR_GYRO_CALIB,
	IPR_ACC_CALIB,
	IPR_MOTORS_SWITCH,
	IPR_AUTO_PID,
	IPR_RESET,
	IPR_SCRIPT_1,
	IPR_SCRIPT_2,
	IPR_SCRIPT_3,
	IPR_SCRIPT_4,
	IPR_SCRIPT_5

}	ImagePathsReference_t;


extern const char *imagePathsReferenceArray [];


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _IMAGE_PATHS_H_ */
