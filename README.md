Snowfox = OS + HAL + IO + COMSTACK + CI + C++
=============================================
[![GPLv3 License](.ci/badge/license-gplv3-blue.svg)](LICENSE)
[![Build Status](https://travis-ci.org/lxrobotics/snowfox.svg?branch=master)](https://travis-ci.org/lxrobotics/snowfox)
[![Coverage Status](https://coveralls.io/repos/github/lxrobotics/snowfox/badge.svg?branch=master&service=github)](https://coveralls.io/github/lxrobotics/snowfox?branch=master)
[![Wiki](.ci/badge/docu-wiki-brightgreen.svg)](https://github.com/lxrobotics/snowfox/wiki)

<p align="center"> 
<img src=".ci/logo/snowfox-os-logo.jpg">
</p>

### What ?

Snowfox consists of a Operating System + a Hardware Abstraction Layer + IO driver support for various sensors, actuators and communication controllers + industrial communication stacks written mostly in C++. **The codebase can be simultaneously compiled for both host and desired target platform which enables the user to run and verify the complete firmware within the host pc without the need for target hardware.** Furthermore unit tests are run and code quality metrics are gathered automatically upon commit in order to ensure code quality and functionality.

### Why #1?

The application of OO principles such as SOLID leads to a clean code base and minimizes coupling between modules. This enables the application of Test Driven Development which gives developers instantenous feedback on their code therefore eliminating tedious integration and bug fixing sessions typical for Debug-Later-Programming.

### Why #2?

In his book "Refactoring: Improving the Design of Existing Code" Martin Fowler frankly states that *“Any fool can write code that a computer can understand. Good programmers write code that humans can understand.”* **This project aims to do just that for the embedded domain.** You are kindly invited to browse the code and form your own opinion about how well the code is adhering to our claim.

## OS

Run-To-Completion event based scheduler in progress ...

## Hardware Abstraction Layers
### Atmel/Microchip
| MCU                        | MCU_ARCH              | MCU_TYPE          | Eval-Boards                                                                                                                                                                                                                                                                                                                                                          |
|:--------------------------:|:---------------------:|:-----------------:|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| AT90CAN32                  | avr                   | at90can32         |                                                                                                                                                                                                                                                                                                                                                                      |
| AT90CAN64                  | ...                   | at90can64         |                                                                                                                                                                                                                                                                                                                                                                      |
| AT90CAN128                 | ...                   | at90can128        | [Olimex AVR-CAN](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/mcu/olimex-avr-can.pdf), [AL-ERAM128 V2.0](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/mcu/alvidi-eram128-can.pdf)                                                                                                                      |
| ATMega640                  | ...                   | atmega640         |                                                                                                                                                                                                                                                                                                                                                                      |
| ATMega1280                 | ...                   | atmega1280        |                                                                                                                                                                                                                                                                                                                                                                      |
| ATMega2560                 | ...                   | atmega2560        | [Arduino Mega](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/mcu/arduino-mega.pdf), [Controllino Mega](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/mcu/controllino-mega.pdf), [Controllino Maxi](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/mcu/controllino-maxi.pdf) |
| ATMega164P                 | ...                   | atmega164p        |                                                                                                                                                                                                                                                                                                                                                                      |
| ATMega324P                 | ...                   | atmega324p        |                                                                                                                                                                                                                                                                                                                                                                      |
| ATMega644P                 | ...                   | atmega644p        |                                                                                                                                                                                                                                                                                                                                                                      |
| ATMega1284P                | ...                   | atmega1284p       | [Moteino Mega USB](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/io/low-power-lab-moteino-mega-lora-usb.png)                                                                                                                                                                                                                           |
| ATMega328P                 | ...                   | atmega328p        | [Arduino Uno](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/mcu/arduino-uno.pdf), [Controllino Mini](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/mcu/controllino-mini.pdf)                                                                                                                             |
| ATMega16U4                 | ...                   | atmega16u4        |                                                                                                                                                                                                                                                                                                                                                                      |
| ATMega32U4                 | ...                   | atmega32u4        | [Arduino Leonardo](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/mcu/arduino-leonardo.pdf)                                                                                                                                                                                                                                             |
| ATMega3209                 | ...                   | atmega3209        |                                                                                                                                                                                                                                                                                                                                                                      |
| ATMega4809                 | ...                   | atmega4809        | [Arduino Uno WiFi Rev.2](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/mcu/arduino-uno-wifi-rev2.pdf)                                                                                                                                                                                                                                  |

### Host (Test Build)
| MCU                        | MCU_ARCH              | MCU_TYPE          |
|:--------------------------:|:---------------------:|:-----------------:|
| Host (Test Build)          | host                  | host              |


## I/O Device Drivers
#### [/driver/can](include/spectre/driver/can) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/can)
* **MCP2515** (CAN Controller) ([Seedstudio CAN Shield V2.0](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/io/seedstudio-can-shield-v-2-0.pdf))

#### [/driver/glcd](include/spectre/driver/glcd) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/glcd)
* **RA6963** (GLCD Controller)

#### [/driver/haptic](include/spectre/driver/haptic) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/haptic)
* **DRV2605L** (Haptic Driver for LRA and ERM)

#### [/driver/ioexpander](include/spectre/driver/ioexpander) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/ioexpander)
* **MCP23017** (16-Bit I/O Expander)
* **PCA9547** (8-channel I2C-Bus multiplexer)

#### [/driver/lora](include/spectre/driver/lora) [![Examples](.ci/badge/examples-yes-brightgreen.svg?sanitize=true")](examples/driver/lora)
* **RFM9x** (HopeRF RFM95/96/97/98 Low Power Long Range Transceiver Module) ([Dragino LoRa Shield V1.4](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/io/dragino-lora-shield-v-1-4.png), [Moteino Mega USB](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/io/low-power-lab-moteino-mega-lora-usb.png))

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
* **TMC26x** (Trinamic TMC26x configurable stepper driver) ([Trinamic TOS-100 TMC-26x Shield](https://github.com/lxrobotics/spectre-examples/tree/master/board-schematics/io/trinamic-tmc26x-shield.pdf))

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
**Tip:** Get the latest version of avr-gcc by [cross compiling](https://github.com/lxrobotics/spectre/wiki/%5BCross-Compiler%5D-AVR-GCC) from source.
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
mkdir build && cd build
cmake ..
make
sudo make install
(sudo make uninstall)
```

## Build Example

### Build Library
```
cp examples/debug/debug-serial-atmega328p-uart0/config.cmake config.cmake
mkdir build
cd build
cmake ..
make
sudo make install
```

### Build Executable
```
cd examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-transmitter-dragino-lora-shield-v1.4
mkdir build && cd build
cmake ..
make
```

## Licensing

Snowfox is open source and licensed under version 3 of the GNU GPL. Snowfox is free under this license and can be freely used and distributed under its terms.

The freedom that this GNU GPL license offers, comes with responsibilities and side effects that are not always desirable. This is especially the case if you want to integrate Snowfox in your closed source product and/or don’t want your customers to know that your product contains Snowfox.

As an alternative, Snowfox can be made available under a commercial license. Under the commercial license, Snowfox does not contain any references to the GNU GPL. Refer to the following license comparison matrix to determine the Snowfox license your product requires.

| Question                                                            | GNU GPL version 3 | Commercial License |
| ------------------------------------------------------------------- |:-----------------:|:------------------:|
| Is Snowfox free?                                                    | yes               | no                 |
| Do I have the right to change the Snowfox source code?              | yes               | yes                |
| Can I use Snowfox in my closed source product?                      | no                | yes                |
| Do I have to open my source code?                                   | yes               | no                 |
| Do I have to open source my changes to Snowfox?                     | yes               | no                 |
| Do I have to offer the Snowfox source code to users of my product?  | yes               | no                 |
| Do I have to document that my product uses Snowfox?	              | yes               | no                 |
| Can I redistribute Snowfox in source code format?                   | yes               | no                 |
| Can I receive professional technical support on a commercial basis? | no                | yes                |

For purchasing a commerical license, requesting a quote tailored for you or simply if you need additional information contact us at [consulting@lxrobotics.com](mailto:consulting@lxrobotics.com).
