#!/bin/bash

cd $(dirname $(readlink -f $0))

mkdir -p ../../build
cd ../..
cp "$1" config.cmake
cd build
cmake ..
make
