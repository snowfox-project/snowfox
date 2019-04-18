#!/bin/bash
sudo apt-get update
sudo apt-get install cmake avr-libc binutils-avr gcc-avr avrdude
avr-gcc --version
avr-g++ --version
