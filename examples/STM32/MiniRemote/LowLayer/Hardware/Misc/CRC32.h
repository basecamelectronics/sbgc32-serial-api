/** ____________________________________________________________________
 *
 *	@file		CRC32.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_CRC32_H_
#define		_CRC32_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"hardware.h"


class CRC_HardwareHandler
{
	private :

		CRC_HandleTypeDef	hcrc;
		CRC_TypeDef			*instance;

	public :

		CRC_HardwareHandler(CRC_TypeDef *instance)
							{
								this->instance = instance;
							}

		void				Init (void);
		ui32				CalculateCRC32 (ui32 *buff, ui16 size);

};


extern CRC_HardwareHandler CRC32_Module;


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _CRC32_H_ */
