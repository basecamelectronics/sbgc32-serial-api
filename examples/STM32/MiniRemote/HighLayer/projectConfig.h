/** ____________________________________________________________________
 *
 *	@file		projectConfig.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_PROJECT_CONFIG_H_
#define		_PROJECT_CONFIG_H_

#ifdef		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"initialConfig.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Remote System Config
 */
/* Default recovery parameters ---------------------
 */
/* Adjustable variable synchronization default way */
#define		REMOTE_DEFAULT_AV_SYNC_PRIORITY	AVS_GIMBAL_PRIORITY

/* Common ------------------------------------------
 */
#define		MINI_REMOTE_DEVELOPER_RIGHT		SET_ON	// Turn on developer functional

#define		MINI_REMOTE_FIRMWARE_VERSION	100000	// 1 - major version, 2 : 3 - minor version, 4 : 5 : 6 - build

#define		STATE_LIFO_SIZE					8		// Size of state machine LIFO buffer

#define		BUTTONS_CONTINUOUS_PASS_TIME	700		// Units: ms. Note: multitouch not supported

#define		NAVIGATION_FILTER				4U		// 3 Min --> 10 Max. Determine navigation state bounds

#define		NAVIGATION_MAX_ACCEPT_ERROR		500		// Maximal acceptable center position error
#define		NAVIGATION_INIT_BLOCK_TIME		0		// Units: ms
#define		NAVIGATION_CONTINUOUS_PASS_TIME	500		// Units: ms
#define		NAVIGATION_CONTINUOUS_STEP_TIME	150		// Units: ms

#define		TOGGLE_BUTTON_UPDATE_TIME		50		// Units: ms

#define		BACKGROUND_TASK_DELAY			10		// Units: ms

/* Mixers Config -----------------------------------
 */
#define		TASK_MIXES_POLLING		SET_ON			// SET_OFF: manual calling | SET_ON: task manager handle
	#define	MIX_POLLING_TIME		20				// Units: ms
	#define	omDelayMs(ms)			__DelayMs(ms)	// Mixers processing delay function


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										  GUI Config
 */
/* Default recovery parameters ---------------------
 */
#define		DEFAULT_INITIAL_BRIGHTNESS		55		// <BRIGHTNESS_MIN_VALUE> Min --> <BRIGHTNESS_MAX_VALUE> Max
#define		DEFAULT_ENERGY_ECONOMIC_RATIO	40		// Unit: percents
#define		DEFAULT_ENERGY_ECONOMIC_TIMER	60		// Unit: sec

/* Common ------------------------------------------
 */
#define		DISPLAY_WIDTH			160				// Units: pixels
#define		DISPLAY_HEIGHT			80				// Units: pixels

#define		SMALL_FONT_HEIGHT		12				// Units: pixels
#define		MEDIUM_FONT_HEIGHT		14				// Units: pixels
#define		LARGE_FONT_HEIGHT		16				// Units: pixels

#define		PROGRESSBARS_THICK		8				// Units: pixels
#define		WIDGET_IMAGE_SIZE		18				// Units: pixels. Width and height

#define		SHOW_LOGO_TIME			2000			// Units: ms
#define		SHOW_MESSAGE_TIME		2000			// Units: ms

#define		STRING_SCROLLING_SPEED	2				// 1 Min --> 4 Max. Units: pixels
#define		STRING_SCROLLING_DELAY	1500			// Units: milliseconds

#define		SELECT_ARROW_SIZE		18				// Units: pixels
#define		SELECT_ARROW_CLEARANCE	5				// Units: pixels

#define		BRIGHTNESS_MIN_VALUE	0				// Driver-dependent value
#define		BRIGHTNESS_MAX_VALUE	100				// Driver-dependent value

#define		GUI_ECONOMIC_BRIGHTNESS	20				// <BRIGHTNESS_MIN_VALUE> Min --> <BRIGHTNESS_MAX_VALUE> Max

#define		CONTAINER_PROCESS_DELAY	50				// Unit: ms. General system task rate
#define		CONTAINER_BLINK_DELAY	150				// Unit: ms. Elements blink time

#define		CONTAINER_TOP_BOTTOM_HEIGHT		18		// Units: pixels

#define		ENERGY_ECONOMIC_RATIO_MIN		1		// Unit: percents, constantly
#define		ENERGY_ECONOMIC_RATIO_MAX		100		// Unit: percents, constantly

#define		ENERGY_ECONOMIC_TIMER_MIN		5		// Unit: sec
#define		ENERGY_ECONOMIC_TIMER_MAX		(300 + \
											(1))	//  Unit: sec. Max + 1 == infinity backlight

#define		REALTIME_DATA_UPDATE_TIME		500		// Units: ms. A period of realtime data requesting

/* Message Window Container Config -----------------
 */
#define		MESSAGE_WINDOW_DIALOG_BOX_W		50		// Units: pixels
#define		MESSAGE_WINDOW_DIALOG_BOX_H		20		// Units: pixels
#define		MESSAGE_WINDOW_DIALOG_CLEARANCE	10		// Units: pixels. Y pos / 2

#define		MESSAGE_WINDOW_CALIB_DURATION	5		// Units: sec

/* Control Container Config ------------------------
 */
#define		CONTROL_PROGRESSBAR_RESOLUTION	256		// Relatively

#define		CONTROL_CONTAINER_PROCESS_DELAY	10		// Units: ms. Control container update time

#define		CONROL_ANGLES_DATA_STREAM_RATE	500		// Units: ms

/* Debug Console Container Config ------------------
 */
#define		DEBUG_CONSOLE_BUFFER_SIZE		200		// Size of console buffer

#define		DEBUG_CONSOLE_MESSAGE_DELAY		2000	// Units: ms

#define		DEBUG_CONSOLE_EXLUDING_BEHAVIOR	SET_OFF	// A debug console will show new data

/* AdjVar and Parameter Edit Container Config ------
 */
#define		EDIT_TITLE_TOTAL_HEIGHT			20		// Units: pixels. With additional space
#define		EDIT_TOP_BOTTOM_LABELS_RAISE	3		// Units: pixels. Needed for correct drawing some font's symbols
#define		EDIT_PROGRESSBARS_WIDTH			100		// Units: pixels
#define		EDIT_VALUE_PRBAR_CLEARANCE		2		// Units: pixels

#define		EDIT_BOUND_LABELS_WIDTH			50		// Units: pixels
#define		EDIT_MIN_LABEL_X_COORD			5		// Units: pixels
#define		EDIT_MAX_LABEL_X_COORD			105		// Units: pixels

#define		EDIT_FILTER_DIVIDER_CONSTANT	800.0F	// Relatively
#define		EDIT_SENS_PARAMETER_ADJUST		0.002F	// Relatively

/* Stick and Pot Calib Container Config -------------
 */
#define		CALIB_LABELS_HEIGHT		16				// Units: pixels

#define		CALIB_WINDOW_X_COORD	116				// Units: pixels
#define		CALIB_WINDOW_Y_COORD	25				// Units: pixels

#define		CALIB_WINDOW_SIZE		32				// Units: pixels. Width and height
#define		CALIB_CIRCLE_RADIUS		3				// Units: pixels

#define		CALIB_STATE_LABEL_WIDTH			116		// Units: pixels
#define		CALIB_STATE_LABEL_X_COORD		0		// Units: pixels
#define		CALIB_STATE_LABEL_Y_COORD		25		// Units: pixels

#define		CALIB_VALUES_LABEL_WIDTH		116		// Units: pixels
#define		CALIB_VALUES_LABEL_X_COORD		0		// Units: pixels
#define		CALIB_VALUES_LABEL_Y_COORD		43		// Units: pixels

/* Shortcut Container Config ------------------------
 */
#define		CALIBRATION_TIMEOUT_WAITING		1500	// Units: ms. Needed in case of disconnection

#define		RESET_UPDATE_TIME		4000			// Units: ms
#define		CALIB_INFO_UPDATE_TIME	200				// Units: ms. A period of calib info requesting

#define		AUTO_PID_TIMEOUT		90				// Units: sec. Reset calibration state if PID auto tune isn't completed

#define		SCRIPT_FINISH_CMD_PARSER_WAIT	10000	// Units: ms. Defined by maximal script-command delay


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						 SBGC32 Communication Config
 */
/* Default recovery parameters ---------------------
 */
#define		SBGC_DEFAULT_CONTROL_PROFILE	CTRLP_1	// CTRLP_1 : CTRLP_2 : CTRLP_3
#define		SBGC_DEFAULT_CONTROL_SPEED		5000	// 0 Min --> 16384 Max, unipolar. Axis default control speed
#define		SBGC_DEFAULT_CONTROL_LPF		5		// 0 Min --> 15 Max. Axis default control LPF
#define		SBGC_DEFAULT_CONTROL_SENS		25		// 0 Min --> 50 Max. Default sensitivity for all axis to control
#define		SBGC_DEFAULT_CONTROL_INVERT		FALSE__	// Default inversion for all axis to control
#define		SBGC_DEFAULT_CONTROL_MODE		GIMBAL_ABSOLUTE_CONTROL

/* Mutually exclusive */
#define		SBGC_DEFAULT_COMMUNICATION_WAY	CW_UART

/* Control parameters ------------------------------
 */
#define		SBGC_CONTROL_PROFILES_NUM		3		// Control profiles quantity
#define		SBGC_CONTROL_HANDLERS_NUM		3		// Handlers quantity. Joy X axis, Joy Y axis, Potentiometer

#define		SBGC_CONTROL_SPEED_DIVIDER		327.68F	// Units: Relatively. Uses for ParameterEdit container
#define		SBGC_CONTROL_SPEED_MIN_VALUE	0		// Units: Relatively
#define		SBGC_CONTROL_SPEED_MAX_VALUE	50		// Units: Relatively

#define		SBGC_CONTROL_LPF_MIN_VALUE		0		// Units: Relatively
#define		SBGC_CONTROL_LPF_MAX_VALUE		15		// Units: Relatively

#define		SBGC_CONTROL_SENS_MULTIPLIER	200		// Units: Relatively. Don't uses for ParameterEdit container. Control container only
#define		SBGC_CONTROL_SENS_MIN_VALUE		0		// Units: Relatively
#define		SBGC_CONTROL_SENS_MAX_VALUE		50		// Units: Relatively

/* Other -------------------------------------------
 */
#define		SBGC_TARGET_IMU			IMU_TYPE_MAIN	// Main IMU sensor for the program

#define		SBGC_NEED_CLEAN_UNEXP_CMD_BUFF	SET_ON	// Clean unexpected commands buffer in disconnection case
#define		SBGC_NEED_RESET_DRIVER			SET_ON	// Need to reset STM32 driver if connection don't recovers so long
	#define	SBGC_DRIVER_RESET_TIMEOUT		5000	// Units: ms
	#define	SBGC_DRIVER_RESET_CYCLIC		SET_OFF	// Periodically reset STM32 driver unless connection recovers

#define		CONTROL_UPDATE_TIME		20				// Units: ms
#define		DATA_STREAM_UPDATE_TIME	2000			// Units: ms

/* No connection constants */
#define		SBGC_NEED_PING					SET_ON	// ON : OFF a realtime ping system
	#define	DISCONNECTION_UPDATE_TIME		2000	// Units: ms. Disconnection state waiting
	#define	SBGC_PING_UPDATE_TIME			500		// Units: ms. Realtime ping. Not needed if data stream is on
	#define	SBGC_REDUCED_COMMUNICATION_TIME	5		// Units: ms. Timeout in disconnection case. Big values freeze a system


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									   Loader Config
 */
#define		LOADER_NEED_CHANGE_SETTINGS		SET_OFF	// SET_ON if the system settings were change its structure

/* Interconnected parameters */
#define		FLASH_LOADER_SECTOR		FLASH_SECTOR_7
#define		FLASH_LOADER_ADDRESS	0x08060000


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										Service Code
 */
#if (SBGC_STARTUP_UART & SBGC_STARTUP_RS422)
	#error "Choose one communication method at startup"
#endif


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _PROJECT_CONFIG_H_ */
