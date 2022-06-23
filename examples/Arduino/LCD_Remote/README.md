LCD Remote Arduino Example
==========================================
[![Web-site](https://www.basecamelectronics.com/img/logo.basecam.onwhite.png)](https://www.basecamelectronics.com)

This is example sketch for Arduino, that shows how to control
SimpleBGC-driven gimbal via Serial API. API specs are available at
[SerialAPI](http://www.basecamelectronics.com/serialapi/)

## Basic functions:

- Display system status using multiple pages (Up/Down arrow to scroll):

	- Battery voltage

	- Active profile

	- Average error of stabilization in 0.001 degrees

	- Communication errors, I2C errors, various debug info

	- Display a customizable set of adjustable variables (Left/Right arrow or encoder Push-button to scroll),
			change their values by the rotary encoder and save to EEPROM by pressing an encoder button

- Trim ROLL axis with 0.1 degree precision

- Use analog joystick to control PITCH and YAW axis (passed to SBGC controller as regular RC channels)

- Joystick push-button acts as "Menu" button

- Navigation "select" button turns motors ON/OFF

## Hardware:

-Arduino Mega 2560

- LCD Key Shield from ELECFREAKS, that includes:

	- 1602 LCD display

	- Rotary encoder with push button

	- 5 navigation buttons (Left, Right, Up, Down, Select)

- 2-axis joystick with push button

- Wireless serial connection (optional)

## Gimbal settings:

- Firmware version 2.61 or above

- RC control in SPEED or ANGLE mode

- Assign desired actions to menu button in the "Service" tab

*Note: Project has been builded with PlatformIO framework*
