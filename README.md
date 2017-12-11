spectre = RTOS + HAL + IO + COMSTACK + C++
==========================================
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://github.com/lxrobotics/spectre/blob/master/LICENSE)

spectre consists of an Real Time Operating System + an Hardware Abstraction Layer for dedicated architectures + IO driver support for various sensors and actuators + various industrial communication stacks encapsulated in a comfortable, small and elegant C++ API.

## Build
---
### Install toolchain ###
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
### Build
```
cd spectre
cmake .
make
```

## Licensing

spectre is open source and licensed under version 3 of the GNU GPL. spectre is free under this license and can be freely used and distributed under its terms.

The freedom that this GNU GPL license offers, comes with responsibilities and side effects that are not always desirable. This is especially the case if you want to integrate spectre in your closed source product and/or don’t want your customers to know that your product contains spectre.

As an alternative, spectre can be made available under a commercial license. Under the commercial license, spectre does not contain any references to the GNU GPL. Refer to the following license comparison matrix to determine the spectre license your product requires.

| Question                                                            | GNU GPL version 3 | Commercial License |
| ------------------------------------------------------------------- |:-----------------:|:------------------:|
| Is spectre free?                                                    | yes               | no                 |
| Do I have the right to change the spectre source code?	            | yes               | yes                |
| Can I use spectre in my closed source product?	                    | no                | yes                |
| Do I have to open my source code?	                                  | yes               | no                 |
| Do I have to open source my changes to spectre?	                    | yes               | no                 |
| Do I have to offer the spectre source code to users of my product?	| yes               | no                 |
| Do I have to document that my product uses spectre?	                | yes               | no                 |
| Can I redistribute spectre in source code format?	                  | yes               | no                 |
| Can I receive professional technical support on a commercial basis? | no                | yes                |

Contact Alexander Entinger / LXRobotics GmbH ([consulting@lxrobotics.com](mailto:consulting@lxrobotics.com)) to request additional information, customisation and/or a quote for a commercial license for the whole library or parts of it.
