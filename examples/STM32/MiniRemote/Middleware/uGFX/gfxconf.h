/**
 * This file has a different license to the rest of the uGFX system.
 * You can copy, modify and distribute this file as you see fit.
 * You do not need to publish your source modifications to this file.
 * The only thing you are not permitted to do is to relicense it
 * under a different license.
 */

/**
 * Copy this file into your project directory and rename it as gfxconf.h
 * Edit your copy to turn on the uGFX features you want to use.
 * The values below are the defaults.
 *
 * Only remove the comments from lines where you want to change the
 * default value. This allows definitions to be included from
 * driver makefiles when required and provides the best future
 * compatibility for your project.
 *
 * Please use spaces instead of tabs in this file.
 */

#ifndef _GFXCONF_H
#define _GFXCONF_H

///////////////////////////////////////////////////////////////////////////
// GFX - Compatibility options                                           //
///////////////////////////////////////////////////////////////////////////
//#define GFX_COMPAT_V2                                GFXON
#define GFX_COMPAT_OLDCOLORS                         GFXOFF

///////////////////////////////////////////////////////////////////////////
// GOS - One of these must be defined, preferably in your Makefile       //
///////////////////////////////////////////////////////////////////////////
//#define GFX_USE_OS_CHIBIOS                           GFXOFF
#define GFX_USE_OS_FREERTOS                          GFXON
//    #define GFX_FREERTOS_USE_TRACE                   GFXOFF
//#define GFX_USE_OS_WIN32                             GFXOFF
//#define GFX_USE_OS_LINUX                             GFXOFF
//#define GFX_USE_OS_OSX                               GFXOFF
//#define GFX_USE_OS_ECOS                              GFXOFF
//#define GFX_USE_OS_RAWRTOS                           GFXON
//#define GFX_USE_OS_ARDUINO                           GFXOFF
//#define GFX_USE_OS_KEIL                              GFXOFF
//#define GFX_USE_OS_RTX5                              GFXOFF
//#define GFX_USE_OS_CMSIS                             GFXOFF
//#define GFX_USE_OS_CMSIS2                            GFXOFF
//#define GFX_USE_OS_RAW32                             GFXON
//#define GFX_USE_OS_ZEPHYR                            GFXOFF
//#define GFX_USE_OS_NIOS                              GFXOFF
//#define GFX_USE_OS_QT                                GFXOFF
//    #define INTERRUPTS_OFF()                         optional_code
//    #define INTERRUPTS_ON()                          optional_code

// Options that (should where relevant) apply to all operating systems
//    #define GFX_NO_INLINE                            GFXOFF
    #define GFX_COMPILER                             GFX_COMPILER_GCC
//    #define GFX_SHOW_COMPILER                        GFXOFF
//    #define GFX_CPU                                  GFX_CPU_CORTEX_M4
//    #define GFX_CPU_NO_ALIGNMENT_FAULTS              GFXOFF
//    #define GFX_CPU_ENDIAN                           GFX_CPU_ENDIAN_UNKNOWN
//    #define GFX_OS_HEAP_SIZE                         0
    #define GFX_OS_NO_INIT                           GFXON
    #define GFX_OS_INIT_NO_WARNING                   GFXON
//    #define GFX_OS_PRE_INIT_FUNCTION                 myHardwareInitRoutine
//    #define GFX_OS_EXTRA_INIT_FUNCTION               myOSInitRoutine
//    #define GFX_OS_EXTRA_DEINIT_FUNCTION             myOSDeInitRoutine
//    #define GFX_OS_CALL_UGFXMAIN                     GFXOFF
//    #define GFX_OS_UGFXMAIN_STACKSIZE                0
//    #define GFX_EMULATE_MALLOC                       GFXOFF


///////////////////////////////////////////////////////////////////////////
// GDISP                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GDISP                                GFXON

//#define GDISP_NEED_AUTOFLUSH                         GFXOFF
//#define GDISP_NEED_TIMERFLUSH                        GFXOFF
#define GDISP_NEED_VALIDATION                        GFXON
#define GDISP_NEED_CLIP                              GFXON
#define GDISP_NEED_CIRCLE                            GFXON
#define GDISP_NEED_DUALCIRCLE                        GFXON
//#define GDISP_NEED_ELLIPSE                           GFXOFF
#define GDISP_NEED_ARC                               GFXON
#define GDISP_NEED_ARCSECTORS                        GFXON
#define GDISP_NEED_CONVEX_POLYGON                    GFXON
#define GDISP_NEED_SCROLL                            GFXON
#define GDISP_NEED_PIXELREAD                         GFXON
#define GDISP_NEED_CONTROL                           GFXON
//#define GDISP_NEED_QUERY                             GFXOFF
#define GDISP_NEED_MULTITHREAD                       GFXON
//#define GDISP_NEED_STREAMING                         GFXOFF
#define GDISP_NEED_TEXT                              GFXON
    #define GDISP_NEED_TEXT_WORDWRAP                 GFXON
//    #define GDISP_NEED_TEXT_BOXPADLR                 GFXOFF
//    #define GDISP_NEED_TEXT_BOXPADTB                 GFXOFF
    #define GDISP_NEED_ANTIALIAS                     GFXON
    #define GDISP_NEED_UTF8                          GFXON
    #define GDISP_NEED_TEXT_KERNING                  GFXON
//    #define GDISP_INCLUDE_FONT_UI1                   GFXOFF
//    #define GDISP_INCLUDE_FONT_UI2                   GFXON		// The smallest preferred font.
//    #define GDISP_INCLUDE_FONT_LARGENUMBERS          GFXOFF
    //#define GDISP_INCLUDE_FONT_DEJAVUSANS10          GFXON
    //#define GDISP_INCLUDE_FONT_DEJAVUSANS12          GFXON
    //#define GDISP_INCLUDE_FONT_DEJAVUSANS16          GFXON
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS20          GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS24          GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS32          GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANSBOLD12      GFXOFF
//    #define GDISP_INCLUDE_FONT_FIXED_10X20           GFXOFF
    #define GDISP_INCLUDE_FONT_FIXED_7X14            GFXON
//    #define GDISP_INCLUDE_FONT_FIXED_5X8             GFXOFF
    #define GDISP_INCLUDE_FONT_DEJAVUSANS12_AA       GFXON
    #define GDISP_INCLUDE_FONT_DEJAVUSANS16_AA       GFXON
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS20_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS24_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS32_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANSBOLD12_AA   GFXOFF
    #define GDISP_INCLUDE_USER_FONTS                 GFXON

#define GDISP_NEED_IMAGE GFXON
    #define GDISP_NEED_IMAGE_BMP                     GFXON
#define GDISP_NEED_IMAGE_BMP_8 GFXON
    //#define GDISP_NEED_IMAGE_GIF                  GFXON
   //     #define GDISP_NEED_IMAGE_BMP_1               GFXON
   //#define GDISP_NEED_IMAGE_NATIVE                  GFXON
//    #define GDISP_NEED_IMAGE_ACCOUNTING              GFXOFF

#define GDISP_NEED_PIXMAP                            GFXON
//    #define GDISP_NEED_PIXMAP_IMAGE                  GFXOFF

//#define GDISP_DEFAULT_ORIENTATION                    gOrientationLandscape    // If not defined the native hardware orientation is used.
//#define GDISP_LINEBUF_SIZE                           128
//#define GDISP_STARTUP_COLOR                          GFX_BLACK
#define GDISP_NEED_STARTUP_LOGO                      GFXOFF

#define GDISP_TOTAL_DISPLAYS                         1

//#define GDISP_DRIVER_LIST                            GDISPVMT_Win32, GDISPVMT_Win32
//    #ifdef GDISP_DRIVER_LIST
//        // For code and speed optimization define as GFXON or GFXOFF if all controllers have the same capability
//        #define GDISP_HARDWARE_STREAM_WRITE          GFXOFF
//        #define GDISP_HARDWARE_STREAM_READ           GFXOFF
//        #define GDISP_HARDWARE_STREAM_POS            GFXOFF
//        #define GDISP_HARDWARE_DRAWPIXEL             GFXOFF
//        #define GDISP_HARDWARE_CLEARS                GFXOFF
//        #define GDISP_HARDWARE_FILLS                 GFXOFF
//        #define GDISP_HARDWARE_BITFILLS              GFXOFF
//        #define GDISP_HARDWARE_SCROLL                GFXOFF
//        #define GDISP_HARDWARE_PIXELREAD             GFXOFF
//        #define GDISP_HARDWARE_CONTROL               GFXOFF
//        #define GDISP_HARDWARE_QUERY                 GFXOFF
//        #define GDISP_HARDWARE_CLIP                  GFXOFF

        #define GDISP_PIXELFORMAT                    GDISP_PIXELFORMAT_RGB565
//    #endif

//#define GDISP_USE_GFXNET                             GFXOFF
//    #define GDISP_GFXNET_PORT                        13001
//    #define GDISP_GFXNET_CUSTOM_LWIP_STARTUP         GFXOFF
//    #define GDISP_DONT_WAIT_FOR_NET_DISPLAY          GFXOFF
//    #define GDISP_GFXNET_UNSAFE_SOCKETS              GFXOFF


///////////////////////////////////////////////////////////////////////////
// GWIN                                                                  //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GWIN                                 GFXON

#define GWIN_NEED_WINDOWMANAGER                      GFXON
    #define GWIN_REDRAW_IMMEDIATE                    GFXON
    #define GWIN_REDRAW_SINGLEOP                     GFXON
    #define GWIN_NEED_FLASHING                       GFXON
        #define GWIN_FLASHING_PERIOD                 1

#define GWIN_NEED_CONSOLE                            GFXON
    #define GWIN_CONSOLE_USE_HISTORY                 GFXON
        #define GWIN_CONSOLE_HISTORY_AVERAGING       GFXOFF
        #define GWIN_CONSOLE_HISTORY_ATCREATE        GFXON
    #define GWIN_CONSOLE_ESCSEQ                      GFXON
    #define GWIN_CONSOLE_USE_BASESTREAM              GFXOFF
    #define GWIN_CONSOLE_USE_FLOAT                   GFXON
#define GWIN_NEED_GRAPH                              GFXOFF
#define GWIN_NEED_GL3D                               GFXOFF

#define GWIN_NEED_WIDGET                             GFXON
//#define GWIN_FOCUS_HIGHLIGHT_WIDTH                   1
    #define GWIN_NEED_LABEL                          GFXON
        #define GWIN_LABEL_ATTRIBUTE                 GFXON
    #define GWIN_NEED_BUTTON                         GFXON
//        #define GWIN_BUTTON_LAZY_RELEASE             GFXOFF
    #define GWIN_NEED_SLIDER                         GFXON
//        #define GWIN_SLIDER_NOSNAP                   GFXOFF
//        #define GWIN_SLIDER_DEAD_BAND                5
//        #define GWIN_SLIDER_TOGGLE_INC               20
    #define GWIN_NEED_CHECKBOX                       GFXON
    #define GWIN_NEED_IMAGE                          GFXON
//        #define GWIN_NEED_IMAGE_ANIMATION            GFXOFF
    #define GWIN_NEED_RADIO                          GFXON
    #define GWIN_NEED_LIST                           GFXON
        #define GWIN_NEED_LIST_IMAGES                GFXON
    #define GWIN_NEED_PROGRESSBAR                    GFXON
        #define GWIN_PROGRESSBAR_AUTO                GFXON
//    #define GWIN_NEED_KEYBOARD                       GFXOFF
//        #define GWIN_KEYBOARD_DEFAULT_LAYOUT         VirtualKeyboard_English1
//        #define GWIN_NEED_KEYBOARD_ENGLISH1          GFXON
//    #define GWIN_NEED_TEXTEDIT                       GFXOFF
    #define GWIN_FLAT_STYLING                        GFXON
//    #define GWIN_WIDGET_TAGS                         GFXOFF

#define GWIN_NEED_CONTAINERS                         GFXON
    #define GWIN_NEED_CONTAINER                      GFXON
//    #define GWIN_NEED_FRAME                          GFXOFF
//    #define GWIN_NEED_TABSET                         GFXOFF
//        #define GWIN_TABSET_TABHEIGHT                18


///////////////////////////////////////////////////////////////////////////
// GTRANS                                                                //
///////////////////////////////////////////////////////////////////////////
//#define GFX_USE_GTRANS                               GFXOFF


///////////////////////////////////////////////////////////////////////////
// GEVENT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GEVENT                               GFXON

//#define GEVENT_ASSERT_NO_RESOURCE                    GFXOFF
//#define GEVENT_MAXIMUM_SIZE                          32
//#define GEVENT_MAX_SOURCE_LISTENERS                  32


///////////////////////////////////////////////////////////////////////////
// GTIMER                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GTIMER                               GFXON

#define GTIMER_THREAD_PRIORITY                       NORMAL_PRIORITY
#define GTIMER_THREAD_WORKAREA_SIZE                  2048


///////////////////////////////////////////////////////////////////////////
// GQUEUE                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GQUEUE                               GFXON

#define GQUEUE_NEED_ASYNC                            GFXON
//#define GQUEUE_NEED_GSYNC                            GFXOFF
//#define GQUEUE_NEED_FSYNC                            GFXOFF
//#define GQUEUE_NEED_BUFFERS                          GFXOFF

///////////////////////////////////////////////////////////////////////////
// GINPUT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GINPUT                               GFXON

//#define GINPUT_NEED_MOUSE                            GFXON
	//#define GINPUT_TOUCH_STARTRAW                    GFXON
//    #define GINPUT_TOUCH_NOTOUCH                     GFXOFF
//    #define GINPUT_TOUCH_NOCALIBRATE                 GFXOFF
//    #define GINPUT_TOUCH_NOCALIBRATE_GUI             GFXOFF
	//#define GINPUT_MOUSE_POLL_PERIOD                 10
//    #define GINPUT_MOUSE_CLICK_TIME                  300
//    #define GINPUT_TOUCH_CXTCLICK_TIME               700
   // #define GINPUT_TOUCH_USER_CALIBRATION_LOAD       GFXON
//    #define GINPUT_TOUCH_USER_CALIBRATION_SAVE       GFXOFF
//    #define GMOUSE_DRIVER_LIST                       GMOUSEVMT_Win32, GMOUSEVMT_Win32
//    #define GINPUT_TOUCH_CALIBRATION_FONT1           "* Double"
//    #define GINPUT_TOUCH_CALIBRATION_FONT2           "* Narrow"
//    #define GINPUT_TOUCH_CALIBRATION_TITLE           "Calibration"
//    #define GINPUT_TOUCH_CALIBRATION_ERROR           "Calibration Failed!"
//#define GINPUT_NEED_KEYBOARD                         GFXOFF
//    #define GINPUT_KEYBOARD_POLL_PERIOD              200
//    #define GKEYBOARD_DRIVER_LIST                    GKEYBOARDVMT_Win32, GKEYBOARDVMT_Win32
//    #define GKEYBOARD_LAYOUT_OFF                     GFXOFF
//        #define GKEYBOARD_LAYOUT_SCANCODE2_US        GFXOFF
//#define GINPUT_NEED_TOGGLE                           GFXOFF
//#define GINPUT_NEED_DIAL                             GFXOFF


///////////////////////////////////////////////////////////////////////////
// GFILE                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GFILE                                GFXON

#define GFILE_NEED_PRINTG                            GFXON
//#define GFILE_NEED_SCANG                             GFXOFF
#define GFILE_NEED_STRINGS                           GFXON
//#define GFILE_NEED_FILELISTS                         GFXOFF
//#define GFILE_NEED_STDIO                             GFXOFF
//#define GFILE_NEED_NOAUTOMOUNT                       GFXOFF
//#define GFILE_NEED_NOAUTOSYNC                        GFXOFF

//#define GFILE_NEED_MEMFS                             GFXOFF
#define GFILE_NEED_ROMFS                             GFXON
//#define GFILE_NEED_RAMFS                             GFXOFF
//#define GFILE_NEED_FATFS                             GFXON
//#define GFILE_NEED_NATIVEFS                          GFXOFF
//#define GFILE_NEED_CHBIOSFS                          GFXOFF
//#define GFILE_NEED_USERFS                            GFXOFF

//#define GFILE_ALLOW_FLOATS                           GFXOFF
//#define GFILE_ALLOW_DEVICESPECIFIC                   GFXOFF
#define GFILE_MAX_GFILES                             5

///////////////////////////////////////////////////////////////////////////
// GADC                                                                  //
///////////////////////////////////////////////////////////////////////////
//#define GFX_USE_GADC                                 GFXOFF
//    #define GADC_MAX_LOWSPEED_DEVICES                4

///////////////////////////////////////////////////////////////////////////
// GAUDIO                                                                //
///////////////////////////////////////////////////////////////////////////
//#define GFX_USE_GAUDIO                               GFXOFF
//    #define GAUDIO_NEED_PLAY                         GFXOFF
//    #define GAUDIO_NEED_RECORD                       GFXOFF

///////////////////////////////////////////////////////////////////////////
// GMISC                                                                 //
///////////////////////////////////////////////////////////////////////////
//#define GFX_USE_GMISC                                GFXOFF

//#define GMISC_NEED_ARRAYOPS                          GFXOFF
//#define GMISC_NEED_FASTTRIG                          GFXOFF
//#define GMISC_NEED_FIXEDTRIG                         GFXOFF
//#define GMISC_NEED_INVSQRT                           GFXOFF
//    #define GMISC_INVSQRT_MIXED_ENDIAN               GFXOFF
//    #define GMISC_INVSQRT_REAL_SLOW                  GFXOFF
//#define GMISC_NEED_MATRIXFLOAT2D                     GFXOFF
//#define GMISC_NEED_MATRIXFIXED2D                     GFXOFF
//#define GMISC_NEED_HITTEST_POLY                      GFXOFF

/* Custom */
#define GWIN_NEED_MENU          GFXON
#define GWIN_NEED_MENU_PREF     GFXON
#define GWIN_NEED_CUSTOM_IMAGE_WIDGET GFXON
//#define GDISP_PIXELFORMAT 		GDISP_PIXELFORMAT_MONO


#endif /* _GFXCONF_H */
