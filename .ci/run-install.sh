#!/bin/bash
cd $(dirname $(readlink -f $0))

sudo apt-get install cppcheck
sudo apt-get install lcov
gem install coveralls-lcov
lcov --version
g++ --version

sudo apt-get install cmake
sudo apt-get install avr-libc binutils-avr gcc-avr avrdude



