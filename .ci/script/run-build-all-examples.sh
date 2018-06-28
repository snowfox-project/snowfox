#!/bin/bash

cd $(dirname $(readlink -f $0))

echo "[ATMEGA328P]"
echo "  [can]"
echo "    [MCP2515]"
./run-build-single-example.sh examples/driver/can/MCP2515/driver-mcp2515-spi-atmega328p-transmitter

echo "  [glcd]"
echo "    [RA6963]"
./run-build-single-example.sh examples/driver/glcd/RA6963/driver-ra6963-gpio-at90can128

echo "  [haptic]"
echo "    [DRV2605]"
./run-build-single-example.sh examples/driver/haptic/DRV2605/driver-drv2605-i2c-atmega328p

echo "  [ioexpander]"
echo "    [PCA9547]"
./run-build-single-example.sh examples/driver/ioexpander/PCA9547/driver-pca9547-i2c-atmega328p

echo "  [lora]"
echo "    [RFM9x]"
./run-build-single-example.sh examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-receiver
./run-build-single-example.sh examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-transmitter

