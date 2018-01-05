#!/bin/bash
cd $(dirname $(readlink -f $0))

mkdir -p ../../build
cd ../../build
cmake ..
make
