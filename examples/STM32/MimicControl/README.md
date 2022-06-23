Mimic Control STM32 Example
==========================================
[![Web-site](https://www.basecamelectronics.com/img/logo.basecam.onwhite.png)](https://www.basecamelectronics.com)

This is example sketch for STM32, that shows how to control
SimpleBGC-driven gimbal via Serial API. API specs are available at
[SerialAPI](http://www.basecamelectronics.com/serialapi/)

*Demo: gimbal will repeat motion of the remote controller build of 2 potentiometers and 2 push-buttons:*

- "Menu" button for gimbal controller

- "Rec" button for camera control via PWM->IR converter

## Hardware:

- NUCLEO-F767ZI

- 2 potentimeters (or encoders with analog output), connect GND, +3.3 V to the side outputs of potentiometers

- 2 Buttons (Menu, Rec)

- PWM-to-IR camera control adapter, connected to FC_PITCH of gimbal controller (optional)

## Gimbal settings:

- RC SPEED should be set high enough to track fast movements of a controller's handle (100..150)

- Acceleration limit is set to a value that gimbal can process without loosing sync in motors

*Note: This project has been builded with arm-none-eabi toolchain and mingw32-make builder.*
*C compiler = arm-none-eabi-gcc; C++ compiler = arm-none-eabi-g++*