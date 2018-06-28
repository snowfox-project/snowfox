#!/bin/bash

cd $(dirname $(readlink -f $0))

./run-build-libspectre.sh "$1"/config.cmake

cd ../..
mkdir -p "$1"/build
cd "$1"/build
cmake ..
make
