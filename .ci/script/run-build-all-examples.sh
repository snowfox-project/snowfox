#!/bin/bash

cd $(dirname $(readlink -f $0))

echo "[ATMEGA328P]"
echo "  [ioexpander]"
echo "    [PCA9547]"
./run-build-single-example.sh examples/driver/ioexpander/PCA9547/driver-pca9547-i2c-atmega328p
echo "  [lora]"
echo "    [RFM9x]"
./run-build-single-example.sh examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-receiver
./run-build-single-example.sh examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-transmitter

