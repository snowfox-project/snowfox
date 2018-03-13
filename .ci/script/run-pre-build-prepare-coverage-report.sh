#!/bin/bash
cd $(dirname $(readlink -f $0))
cd ..

cd ../build

lcov --directory . --zerocounters
