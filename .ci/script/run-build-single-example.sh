#!/bin/bash

cd $(dirname $(readlink -f $0))

echo "  [LIBRARY]"
./run-build-libspectre.sh "$1"/config.cmake
echo "  [BINARY]"
cd ../..
mkdir -p "$1"/build
cd "$1"/build
cmake ..
make
