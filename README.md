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
#### [/driver/can](include/spectre/driver/can) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/can)
* **MCP2515** (CAN Controller) ([Seedstudio CAN Shield V2.0](examples/eval-board-schematics/seedstudio-can-shield-v-2-0.pdf))

#### [/driver/glcd](include/spectre/driver/glcd) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/glcd)
* **RA6963** (GLCD Controller)

#### [/driver/haptic](include/spectre/driver/haptic) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/haptic)
* **DRV2605L** (Haptic Driver for LRA and ERM)

#### [/driver/ioexpander](include/spectre/driver/ioexpander) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/ioexpander)
* **MCP23017** (16-Bit I/O Expander)
* **PCA9547** (8-channel I2C-Bus multiplexer)

#### [/driver/lora](include/spectre/driver/lora) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/lora)
* **RFM9x** (HopeRF RFM95/96/97/98 Low Power Long Range Transceiver Module) ([Dragino LoRa Shield V1.4](examples/eval-board-schematics/dragino-lora-shield-v-1-4.png), [Moteino Mega USB](examples/eval-board-schematics/low-power-lab-moteino-mega-lora-usb.png))

#### [/driver/memory](include/spectre/driver/memory) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/memory)
* **AT45DBx** (SPI Data Flash)
* **PCF8570** (256 × 8-Bit Static Low-Voltage RAM)

#### [/driver/sensor](include/spectre/driver/sensor) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/sensor)
* **AD7151** (1-channel capacitance converter for proximity sensing)
* **AS5600** (12-Bit programmable contactless potentiometer)
* **BMG160** (3-axis digital output MEMS gyroscope)
* **INA220** (Low- or high-side, bidirectional, I2C current monitor)
* **L3GD20** (3-axis digital output MEMS gyroscope)
* **LIS2DSH** (3-axis digital output MEMS accelerometer)
* **LIS3DSH** (3-axis digital output MEMS accelerometer)
* **LIS3MDL** (3-axis digital output MEMS magnetometer)

#### [/driver/serial](include/spectre/driver/serial) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/serial)
* **UART** (Serial UART Driver)

#### [/driver/stepper](include/spectre/driver/stepper) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/stepper)
* **TMC26x** (Trinamic TMC26x configurable stepper driver) ([Trinamic TOS-100 TMC-26x Shield](examples/eval-board-schematics/trinamic-tmc26x-shield.pdf))

#### [/driver/tlcd](include/spectre/driver/tlcd)
* **HD44780** (Dot Matrix LCD Controller/Driver)

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
| Do I have to document that my product uses Spectre?	              | yes               | no                 |
| Can I redistribute Spectre in source code format?                   | yes               | no                 |
| Can I receive professional technical support on a commercial basis? | no                | yes                |

Contact Alexander Entinger / LXRobotics GmbH ([consulting@lxrobotics.com](mailto:consulting@lxrobotics.com)) to request additional information, customisation and/or a quote for a commercial license for the whole library or parts of it.
