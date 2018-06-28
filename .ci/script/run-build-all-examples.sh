#!/bin/bash

cd $(dirname $(readlink -f $0))

#######################################################################################################

echo "[debug::ATMEGA328P::serial]"
./run-build-single-example.sh examples/debug/debug-serial-atmega328p-uart0

#######################################################################################################

echo "[driver::ATMEGA328P::can::MCP2515]"
./run-build-single-example.sh examples/driver/can/MCP2515/driver-mcp2515-spi-atmega328p-transmitter

echo "[driver::AT90CAN128::glcd::RA6963]"
./run-build-single-example.sh examples/driver/glcd/RA6963/driver-ra6963-gpio-at90can128

echo "[driver::ATMEGA328P::haptic::DRV2605]"
./run-build-single-example.sh examples/driver/haptic/DRV2605/driver-drv2605-i2c-atmega328p

echo "[driver::ATMEGA328P::ioexpander::PCA9547]"
./run-build-single-example.sh examples/driver/ioexpander/PCA9547/driver-pca9547-i2c-atmega328p

echo "[driver::ATMEGA328P::lora::RFM9x]"
./run-build-single-example.sh examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-receiver
./run-build-single-example.sh examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-transmitter

echo "[driver::ATMEGA328P::memory::PCF8570]"
./run-build-single-example.sh examples/driver/memory/PCF8570/driver-pcf8570-i2c-atmega328p

echo "[driver::AT90CAN128::serial]"
./run-build-single-example.sh examples/driver/serial/uart0-at90can128
./run-build-single-example.sh examples/driver/serial/uart1-at90can128
echo "[driver::ATMEGA328P::serial]"
./run-build-single-example.sh examples/driver/serial/uart0-atmega328p

echo "[driver::ATMEGA328P::stepper::TMC260x]"
./run-build-single-example.sh examples/driver/stepper/TMC260x/driver-tmc260x-spi-atmega328p

#######################################################################################################
