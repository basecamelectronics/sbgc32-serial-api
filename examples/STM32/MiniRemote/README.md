Mini-Remote Controller STM32 Example
====================================
[![Web-site](https://www.basecamelectronics.com/img/logo.basecam.onwhite.png)](https://www.basecamelectronics.com)

This is an example sketch for STM32, that shows how to control
SimpleBGC-driven gimbal via Serial API. API specs are available at
[SerialAPI](http://www.basecamelectronics.com/serialapi/)

This project is a small remote controller for the SBGC32-based devices.
MiniRemote works in two modes – menu navigation and gimbal control. It allows to perform 
operations such as gimbal control, changing run-time adjustable variables, making sensors 
calibrations, running scripts, switching profiles, executing actions, viewing real-time state.

For more information, see the MiniRemote Description.pdf in this folder.


*Note: This project has been built with an arm-none-eabi toolchain and a mingw32-make builder.*
*C compiler = arm-none-eabi-gcc; C++ compiler = arm-none-eabi-g++*
