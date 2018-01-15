#!/bin/bash
cd $(dirname $(readlink -f $0))

sudo apt-get install cmake

sudo apt-get install cppcheck

sudo apt-get install avr-libc binutils-avr gcc-avr avrdude

