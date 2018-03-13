#!/bin/bash
cd $(dirname $(readlink -f $0))
cd ..

mkdir -p ../build
cd ..
cp config/"$1" config.cmake
cd build
cmake ..
make
