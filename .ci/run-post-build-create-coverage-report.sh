#!/bin/bash

cd $(dirname $(readlink -f $0))

cd ../build

lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info 'test/*' '/usr/*' --output-file coverage.info
lcov --list coverage.info
