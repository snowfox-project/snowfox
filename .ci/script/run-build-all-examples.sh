#!/bin/bash

cd $(dirname $(readlink -f $0))

echo "[ATMEGA328P]"
./run-build-single-example.sh examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-transmitter

