Spectre = RTOS + HAL + IO + COMSTACK + CI + C++
===============================================
[![GPLv3 License](.ci/badge/license-gplv3-blue.svg)](LICENSE)
[![Build Status](https://travis-ci.org/lxrobotics/spectre.svg?branch=master)](https://travis-ci.org/lxrobotics/spectre)
[![Coverage Status](https://coveralls.io/repos/github/lxrobotics/spectre/badge.svg?branch=master&service=github)](https://coveralls.io/github/lxrobotics/spectre?branch=master)

### What ?

Spectre consists of a Real Time Operating System + a Hardware Abstraction Layer + IO driver support for various sensors, actuators and communication controllers + industrial communication stacks written mostly in C++. **The codebase can be simultaneously compiled for both host and desired target platform which enables the user to run and verify the complete firmware within the host pc without the need for target hardware.** Furthermore unit tests are run and code quality metrics are gathered automatically upon commit in order to ensure code quality and functionality.

### Why #1?

The application of OO principles such as SOLID leads to a clean code base and minimizes coupling between modules. This enables the application of Test Driven Development which gives developers instantenous feedback on their code therefore eliminating tedious integration and bug fixing sessions typical for Debug-Later-Programming. **Deliver your projects on budget, time and scope.**

### Why #2?

In his book "Refactoring: Improving the Design of Existing Code" Martin Fowler frankly states that *“Any fool can write code that a computer can understand. Good programmers write code that humans can understand.”* **This project aims to do just that for the embedded domain.** You are kindly invited to browse the code and form your own opinion about how well the code is adhering to our claim.

## RTOS

Work in progress ...

## Hardware Abstraction Layers
### Atmel/Microchip
| MCU                        | MCU_ARCH              | MCU_TYPE          | Eval-Boards                                                                                |
|:--------------------------:|:---------------------:|:-----------------:|:------------------------------------------------------------------------------------------:|
| AT90CAN32                  | avr                   | at90can32         |                                                                                            |
| AT90CAN64                  | ...                   | at90can64         |                                                                                            |
| AT90CAN128                 | ...                   | at90can128        | [Olimex AVR-CAN](examples/eval-board-schematics/olimex-avr-can.pdf)                        |
| ATMega640                  | ...                   | atmega640         |                                                                                            |
| ATMega1280                 | ...                   | atmega1280        |                                                                                            |
| ATMega2560                 | ...                   | atmega2560        | [Arduino Mega](examples/eval-board-schematics/arduino-mega.pdf)                            |
| ATMega164P                 | ...                   | atmega164p        |                                                                                            |
| ATMega324P                 | ...                   | atmega324p        |                                                                                            |
| ATMega644P                 | ...                   | atmega644p        |                                                                                            |
| ATMega1284P                | ...                   | atmega1284p       | [Moteino Mega USB](examples/eval-board-schematics/low-power-lab-moteino-mega-lora-usb.png) |
| ATMega328P                 | ...                   | atmega328p        | [Arduino Uno](examples/eval-board-schematics/arduino-uno.pdf)                              |
| ATMega16U4                 | ...                   | atmega16u4        |                                                                                            |
| ATMega32U4                 | ...                   | atmega32u4        | [Arduino Leonardo](examples/eval-board-schematics/arduino-leonardo.pdf)                    |

### Host (Test Build)
| MCU                        | MCU_ARCH              | MCU_TYPE          |
|:--------------------------:|:---------------------:|:-----------------:|
| Host (Test Build)          | host                  | host              |


## I/O Device Drivers
#### [/driver/can](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/can)
* **MCP2515** (CAN Controller)
[![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/can/MCP2515)

#### [/driver/glcd](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/glcd)
* **RA6963** (GLCD Controller)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/glcd/RA6963)

#### [/driver/haptic](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/haptic)
* **DRV2605L** (Haptic Driver for LRA and ERM)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/haptic/DRV2605)

#### [/driver/ioexpander](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/ioexpander)
* **MCP23017** (16-Bit I/O Expander)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/ioexpander/MCP23017)
* **PCA9547** (8-channel I2C-Bus multiplexer)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/ioexpander/PCA9547)

#### [/driver/lora](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/lora)
* **RFM9x** (HopeRF RFM95/96/97/98 Low Power Long Range Transceiver Module) *(Moteino Mega USB, Dragino LoRa Shield V1.4)*
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/lora)

#### [/driver/memory](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/memory)
* **AT45DBx** (SPI Data Flash)
* **PCF8570** (256 × 8-Bit Static Low-Voltage RAM)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/memory)

#### [/driver/sensor](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/sensor)
* **AD7151** (1-channel capacitance converter for proximity sensing)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/sensor/AD7151)
* **AS5600** (12-Bit programmable contactless potentiometer)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/sensor/AS5600)
* **BMG160** (3-axis digital output MEMS gyroscope)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/sensor/BMG160)
* **INA220** (Low- or high-side, bidirectional, I2C current monitor)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/sensor/INA220)
* **L3GD20** (3-axis digital output MEMS gyroscope)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/sensor/L3GD20)
* **LIS2DSH** (3-axis digital output MEMS accelerometer)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/sensor/LIS2DSH)
* **LIS3DSH** (3-axis digital output MEMS accelerometer)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/sensor/LIS3DSH)
* **LIS3MDL** (3-axis digital output MEMS magnetometer)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/sensor/LIS3MDL)

#### [/driver/serial](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/serial)
* **UART** (Serial UART Driver)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/serial)

#### [/driver/stepper](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/stepper)
* **TCM26x** (Trinamic TCM26x configurable stepper driver)
[![Examples](https://github.com/lxrobotics/spectre/blob/master/.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](https://github.com/lxrobotics/spectre/tree/master/examples/driver/stepper/TMC260x)

## Communication Stacks

* **CANOpen** ( Work in progress ... )

## Getting started
### Install toolchain
* **ALL**
```
sudo apt-get install cmake
```
* **AVR**
```
sudo apt-get install avr-libc binutils-avr gcc-avr avrdude
```

### Clone repository
```
git clone https://github.com/lxrobotics/spectre.git
cd spectre
```

### Copy and edit configuration
```
cp config/atmega328p-default.cmake config.cmake
vim config.cmake
```

### Build
```
mkdir build
cd build
cmake ..
make
```

## Licensing

Spectre is open source and licensed under version 3 of the GNU GPL. Spectre is free under this license and can be freely used and distributed under its terms.

The freedom that this GNU GPL license offers, comes with responsibilities and side effects that are not always desirable. This is especially the case if you want to integrate Spectre in your closed source product and/or don’t want your customers to know that your product contains Spectre.

As an alternative, Spectre can be made available under a commercial license. Under the commercial license, Spectre does not contain any references to the GNU GPL. Refer to the following license comparison matrix to determine the Spectre license your product requires.

| Question                                                            | GNU GPL version 3 | Commercial License |
| ------------------------------------------------------------------- |:-----------------:|:------------------:|
| Is Spectre free?                                                    | yes               | no                 |
| Do I have the right to change the Spectre source code?              | yes               | yes                |
| Can I use Spectre in my closed source product?                      | no                | yes                |
| Do I have to open my source code?                                   | yes               | no                 |
| Do I have to open source my changes to Spectre?                     | yes               | no                 |
| Do I have to offer the Spectre source code to users of my product?  | yes               | no                 |
| Do I have to document that my product uses Spectre?	                | yes               | no                 |
| Can I redistribute Spectre in source code format?                   | yes               | no                 |
| Can I receive professional technical support on a commercial basis? | no                | yes                |

Contact Alexander Entinger / LXRobotics GmbH ([consulting@lxrobotics.com](mailto:consulting@lxrobotics.com)) to request additional information, customisation and/or a quote for a commercial license for the whole library or parts of it.
