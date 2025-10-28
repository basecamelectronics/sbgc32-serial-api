/** ____________________________________________________________________
 *
 *	@file		mixes.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "mixes.h"


static const MixersInitReference_t MixersInitReferenceArray [] =
	/*
	||		 	   INPUT -->	    	 ||  --> MIXER -->  ||	   		--> OUTPUT			||
	 */
	{ {	PRPH_ABSOLUTE_ENCODER_EEPROM,		MIX_CHANNEL_0,		CSF_PARAMETER_CHANGE
	},{	PRPH_DIGITAL_JOYSTICK_CHANNEL_X,	MIX_CHANNEL_1,		CSF_NAVIGATION_Y
	},{	PRPH_DIGITAL_JOYSTICK_CHANNEL_Y,	MIX_CHANNEL_2,		CSF_NAVIGATION_X
	},{	PRPH_LEFT_INCREMENTAL_ENCODER,		MIX_CHANNEL_3,		SF_NO
	},{	PRPH_RIGHT_INCREMENTAL_ENCODER,		MIX_CHANNEL_4,		VSF_AXIS_CONTROL_SENS
	},{	PRPH_ANALOG_JOYSTICK_CHANNEL_X,		MIX_CHANNEL_5,		CSF_NAVIGATION_Y
	},{	PRPH_ANALOG_JOYSTICK_CHANNEL_Y,		MIX_CHANNEL_6,		CSF_NAVIGATION_X
	},{	PRPH_POTENTIOMETER,					MIX_CHANNEL_7,		VSF_AXIS_TRIMMING
	},{	PRPH_ENCODER1_BUTTON,				MIX_CHANNEL_8,		VSF_SC_MENU_ADJ_VARS
	},{	PRPH_ENCODER2_BUTTON,				MIX_CHANNEL_9,		CSF_NAVIGATION_EXIT
	},{	PRPH_BUTTON1,						MIX_CHANNEL_10,		VSF_NAVIGATION_CONTROL_TOGGLE
	},{	PRPH_BUTTON2,						MIX_CHANNEL_11,		CSF_NAVIGATION_ENTER
	},{	PRPH_TOGGLE_SWITCH1,				MIX_CHANNEL_12,		SF_NO
	},{	PRPH_TOGGLE_SWITCH2,				MIX_CHANNEL_13,		VSF_CONTROL_PROFILE_TOGGLE
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_14,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_15,		SF_NO

	}};


static const MixersCoefficientsInitReference_t MixersCoefficientsInitReferenceArray [] =
	/*
	||		MIXER		||	     MIN	  ||	  MAX	  ||		OFFSET		||	  MULTUPLIER  	||		 INVERSION		||		AVERAGE		||
	 */
	{ {	MIX_CHANNEL_0,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_1,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_INVERTED,	MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_2,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_3,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_4,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_5,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_6,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_7,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_8,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_9,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_10,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_11,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_12,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_13,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_14,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_15,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE

	}};


void ParseMixesInitReference (SystemFunction_t *systemFunction, ui8 mixChannelsNumber, MixChannel_t *mixChannel)
{
	/* Mixers init */
	for (ui8 i = 0; i < mixChannelsNumber; i++)
	{
		mixChannel[i].number = MixersInitReferenceArray[i].mix;

		/* Inputs */
		if (MixersInitReferenceArray[i].in != PRPH_NO_INPUT)
		{
			mixChannel[i].source = inputClassesArray[(ui8)MixersInitReferenceArray[i].in];
			mixChannel[i].referenceInputID = inputClassesArray[(ui8)MixersInitReferenceArray[i].in]->GetID();
		}

		else
		{
			mixChannel[i].source = MIX_HAVENO_INPUT;
			mixChannel[i].referenceInputID = PRPH_NO_INPUT;
		}

		/* Outputs */
		for (ui8 k = 0; k < SYSTEM_FUNCTIONS_TOTAL_NUMBER; k++)
		{
			systemFunction[k].ID = (SystemFunctionID_t)k;
			systemFunction[k].value = 0;
		}

		if (MixersInitReferenceArray[i].out != SF_NO)
		{
			mixChannel[i].target = &systemFunction[(ui8)MixersInitReferenceArray[i].out];
			mixChannel[i].referenceOutputID = systemFunction[(ui8)MixersInitReferenceArray[i].out].ID;
		}

		else
		{
			mixChannel[i].target = MIX_HAVENO_OUTPUT;
			mixChannel[i].referenceOutputID = SF_NO;
		}

		mixChannel[i].value = 0;
		mixChannel[i].min = MixersCoefficientsInitReferenceArray[i].min;
		mixChannel[i].max = MixersCoefficientsInitReferenceArray[i].max;

		/* Common */
		mixChannel[MixersInitReferenceArray[i].mix].state = MIX_CHANNEL_ON;

		if (MixersInitReferenceArray[i].in != PRPH_NO_INPUT)
			mixChannel[MixersInitReferenceArray[i].mix].source->SetState(IN_NEED_INIT);

		mixChannel[MixersCoefficientsInitReferenceArray[i].mix].offset = MixersCoefficientsInitReferenceArray[i].offset;
		mixChannel[MixersCoefficientsInitReferenceArray[i].mix].multiplier = MixersCoefficientsInitReferenceArray[i].multiplier;
		mixChannel[MixersCoefficientsInitReferenceArray[i].mix].inversion = MixersCoefficientsInitReferenceArray[i].inversion;
		mixChannel[MixersCoefficientsInitReferenceArray[i].mix].average = MixersCoefficientsInitReferenceArray[i].average;
	}
}


void AttachMixesFunctionsByReferenceSources (SystemFunction_t *systemFunction, ui8 mixChannelsNumber, MixChannel_t *mixChannel)
{
	for (ui8 i = 0; i < mixChannelsNumber; i++)
	{
		mixChannel[i].source = MIX_HAVENO_INPUT;
		mixChannel[i].target = MIX_HAVENO_OUTPUT;

		for (ui8 j = 0; j < mixChannelsNumber; j++)
		{
			if (mixChannel[i].referenceInputID == PRPH_NO_INPUT)
				break;

			if (MixersInitReferenceArray[j].in != PRPH_NO_INPUT)
			{
				if (mixChannel[i].referenceInputID == inputClassesArray[(ui8)MixersInitReferenceArray[j].in]->GetID())
				{
					mixChannel[i].source = inputClassesArray[(ui8)MixersInitReferenceArray[j].in];
					mixChannel[i].source->SetState(IN_NEED_INIT);
				}
			}
		}

		for (ui8 j = 0; j < mixChannelsNumber; j++)
		{
			if (mixChannel[i].referenceOutputID == SF_NO)
				break;

			if ((mixChannel[i].referenceOutputID == systemFunction[(ui8)MixersInitReferenceArray[j].out].ID) &&
				(MixersInitReferenceArray[j].out != SF_NO))
				mixChannel[i].target = &systemFunction[(ui8)MixersInitReferenceArray[j].out];
		}
	}
}


MixChannel_t *FindMixerByNumber (MixChannel_t *mixers, MixChannelNum_t mixerNum)
{
	for (ui8 i = 0; i < MIX_CHANNELS_TOTAL_NUMBER; i++)
		if (mixers[i].number == mixerNum)
			return &mixers[i];

	return NULL;
}


MixChannel_t *FindMixerByInput (MixChannel_t *mixers, InputID_t mixerInput)
{
	for (ui8 i = 0; i < MIX_CHANNELS_TOTAL_NUMBER; i++)
		if (mixers[i].referenceInputID == mixerInput)
			return &mixers[i];

	return NULL;
}


MixChannel_t *FindMixerByOutput (MixChannel_t *mixers, SystemFunctionID_t mixerOut)
{
	for (ui8 i = 0; i < MIX_CHANNELS_TOTAL_NUMBER; i++)
		if (mixers[i].referenceOutputID == mixerOut)
			return &mixers[i];

	return NULL;
}


void MixesProcess (ui8 mixChannelsNumber, MixChannel_t *mixChannel)
{
	#if (TASK_MIXES_POLLING)

		while (1)
		{

	#endif

			for (ui8 i = 0; i < mixChannelsNumber; i++)
			{
				if ((mixChannel[i].source != MIX_HAVENO_INPUT) && (mixChannel[i].target != MIX_HAVENO_OUTPUT) &&
					(mixChannel[i].state == MIX_CHANNEL_ON))
				{
					/* Averaging */
					if (mixChannel[i].average > 1)
					{
						ui32 averageTemp = 0;

						for (ui8 k = 1; k < mixChannel[i].average; k++)
						{
							/* Fault defense */
							if (mixChannel[i].source->InputProcess != NO_PROCESS_FUNC)
								mixChannel[i].source->InputProcess();

							averageTemp += mixChannel[i].source->GetValue();
						}

						mixChannel[i].value = averageTemp / mixChannel[i].average;
					}

					else
					{
						if (mixChannel[i].source->InputProcess != NO_PROCESS_FUNC)
							mixChannel[i].source->InputProcess();

						mixChannel[i].value = mixChannel[i].source->GetValue();
					}

					/* Writing */
					if (mixChannel[i].target->ID != SF_NO)
					{
						if (mixChannel[i].inversion == MIX_CHANNEL_DIRECT)
						{
							mixChannel[i].target->value =
							constrain_(((mixChannel[i].value * mixChannel[i].multiplier)
							+ mixChannel[i].offset), mixChannel[i].min, mixChannel[i].max);
						}

						else
						{
							mixChannel[i].target->value =
							mixChannel[i].max - constrain_(((mixChannel[i].value * mixChannel[i].multiplier)
							+ mixChannel[i].offset), mixChannel[i].min, mixChannel[i].max);
						}
					}
				}
			}

	#if (TASK_MIXES_POLLING)

			omDelayMs(MIX_POLLING_TIME);

		}

	#endif
}
