#!/bin/bash
set -e

cd $(dirname $(readlink -f $0))

#######################################################################################################

cd ../..

cp "$1"/config.cmake config.cmake

(rm -rf build && mkdir build && cd build; cmake ..; make -j4; sudo make install)
(cd "$1"; rm -rf build && mkdir -p build && cd build; cmake ..; make -j4)
(cd build; sudo make uninstall)

#######################################################################################################
