#!/bin/bash

cd $(dirname $(readlink -f $0))

../build/bin/test-host-hal-avr
