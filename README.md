Spectre = RTOS + HAL + IO + COMSTACK + C++
==========================================
[![GPLv3 license](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://github.com/lxrobotics/spectre/blob/master/LICENSE)
[![GitHub Issues](https://img.shields.io/github/issues/lxrobotics/spectre.svg)](https://github.com/lxrobotics/spectre/issues)
[![Build Status](https://travis-ci.org/lxrobotics/spectre.svg?branch=master)](https://travis-ci.org/lxrobotics/spectre)
[![Coverage Status](https://coveralls.io/repos/github/lxrobotics/spectre/badge.svg?branch=master)](https://coveralls.io/github/lxrobotics/spectre?branch=master)

Spectre consists of an Real Time Operating System + an Hardware Abstraction Layer for dedicated architectures + IO driver support for various sensors and actuators + various industrial communication stacks encapsulated in a comfortable, small and elegant C++ API. Additionally a continous integration approach is employed with integrated unit testing ensuring code quality and functionality.

## Hardware Abstraction Layers
| MCU                          | MCU_ARCH              | MCU_TYPE          |
|:----------------------------:|:---------------------:|:-----------------:|
| Atmel/Microchip AT90CAN128   | avr                   | at90can128        |
| Atmel/Microchip ATMega328P   | avr                   | atmega328p        |
| Host (Test Build)            | host                  |                   |


## I/O Device Drivers
### GLCD Drivers ([/driver/glcd](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/glcd))
* **RA6963** (GLCD Controller)

### Haptic Actuator Drivers ([/haptic](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/haptic))

* **DRV2605L** (Haptic Driver for LRA and ERM)

### I/O Expanders ([/driver/ioexpander](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/ioexpander))

* **PCA9547** (8-channel I2C-Bus multiplexer)

### Memories ([/driver/memory](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/memory))

* **AT45DBx** (SPI Data Flash)
* **PCF8570** (256 × 8-Bit Static Low-Voltage RAM)

### Sensors ([/driver/sensor](https://github.com/lxrobotics/spectre/tree/master/include/spectre/driver/sensor))
* **AD7151** (Ultra-low power, 1-channel, capacitance converter for proximity sensing)
* **AS5600** (12-Bit programmable contactless potentiometer)
* **BMG160** (MEMS three-axis digital output gyroscope)
* **INA220** (Low- or high-side, bidirectional, zero-drift, I2C power/current monitor)
* **L3GD20** (MEMS three-axis digital output gyroscope)
* **LIS2DSH** (Ultra-low power, high performance, three-axis digital output accelerometer)
* **LIS3DSH** (Ultra-low power, high performance, three-axis digital output accelerometer)
* **LIS3MDL** (Ultra-low power, high performance, three-axis digital output magnetometer)
* **TPA81** (I2C infrared thermopile sensor array)

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
```

### Copy and edit configuration
```
cp config/atmega328p-default.cmake config.cmake
vim config.cmake
```

### Build
```
cd spectre
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
