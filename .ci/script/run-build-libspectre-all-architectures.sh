#!/bin/bash
##########################################################################
cd $(dirname $(readlink -f $0))
set -e
##########################################################################
./run-build-libspectre.sh config/at90can32-default.cmake
./run-build-libspectre.sh config/at90can64-default.cmake
./run-build-libspectre.sh config/at90can128-default.cmake
./run-build-libspectre.sh config/atmega640-default.cmake
./run-build-libspectre.sh config/atmega1280-default.cmake
./run-build-libspectre.sh config/atmega2560-default.cmake
./run-build-libspectre.sh config/atmega164p-default.cmake
./run-build-libspectre.sh config/atmega324p-default.cmake
./run-build-libspectre.sh config/atmega644p-default.cmake
./run-build-libspectre.sh config/atmega1284p-default.cmake
./run-build-libspectre.sh config/atmega328p-default.cmake
./run-build-libspectre.sh config/atmega16u4-default.cmake
./run-build-libspectre.sh config/atmega32u4-default.cmake
