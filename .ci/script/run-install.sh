#!/bin/bash
sudo apt-get update
sudo apt-get install cppcheck
sudo apt-get install lcov
gem install coveralls-lcov
lcov --version
g++ --version
sudo apt-get install cmake
sudo apt-get install avr-libc=1:1.8.0+Atmel3.5.0-1
sudo apt-get install binutils-avr=2.25+Atmel3.5.0-2
sudo apt-get install gcc-avr=1:4.9.2+Atmel3.5.0-1
sudo apt-get install avrdude



