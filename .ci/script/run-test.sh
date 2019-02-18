#!/bin/bash

cd $(dirname $(readlink -f $0))

cd ../../build/bin
./test-host
