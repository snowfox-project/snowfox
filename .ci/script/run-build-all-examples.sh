#!/bin/bash
##########################################################################
cd $(dirname $(readlink -f $0))
set -e
##########################################################################
EXAMPLES_DEBUG="examples/debug"
./run-build-example.sh $EXAMPLES_DEBUG/debug-serial-atmega328p-uart0
./run-build-example.sh $EXAMPLES_DEBUG/debug-serial-atmega1284p-uart0
##########################################################################
EXAMPLES_DRIVER_CAN="examples/driver/can"
./run-build-example.sh $EXAMPLES_DRIVER_CAN/MCP2515/driver-mcp2515-spi-atmega328p-transmitter
##########################################################################
EXAMPLES_DRIVER_GLCD="examples/driver/glcd"
./run-build-example.sh $EXAMPLES_DRIVER_GLCD/RA6963/driver-ra6963-gpio-at90can128
##########################################################################
EXAMPLES_DRIVER_HAPTIC="examples/driver/haptic"
./run-build-example.sh $EXAMPLES_DRIVER_HAPTIC/DRV2605/driver-drv2605-i2c-atmega328p
##########################################################################
EXAMPLES_DRIVER_IOEXPANDER="examples/driver/ioexpander"
./run-build-example.sh $EXAMPLES_DRIVER_IOEXPANDER/PCA9547/driver-pca9547-i2c-atmega328p
./run-build-example.sh $EXAMPLES_DRIVER_IOEXPANDER/MCP23017/driver-mcp23017-i2c-atmega328p
##########################################################################
EXAMPLES_DRIVER_LORA="examples/driver/lora"
./run-build-example.sh $EXAMPLES_DRIVER_LORA/RFM9x/driver-rfm9x-spi-atmega1284p-debug-moteino-mega-usb
./run-build-example.sh $EXAMPLES_DRIVER_LORA/RFM9x/driver-rfm9x-spi-atmega328p-receiver
./run-build-example.sh $EXAMPLES_DRIVER_LORA/RFM9x/driver-rfm9x-spi-atmega328p-transmitter
##########################################################################
EXAMPLES_DRIVER_MEMORY="examples/driver/memory"
./run-build-example.sh $EXAMPLES_DRIVER_MEMORY/PCF8570/driver-pcf8570-i2c-atmega328p
##########################################################################
EXAMPLES_DRIVER_SENSOR="examples/driver/sensor"
./run-build-example.sh $EXAMPLES_DRIVER_SENSOR/AD7151/driver-ad7151-i2c-atmega328p
./run-build-example.sh $EXAMPLES_DRIVER_SENSOR/AS5600/driver-as5600-i2c-atmega328p
./run-build-example.sh $EXAMPLES_DRIVER_SENSOR/BMG160/driver-bmg160-i2c-atmega328p
./run-build-example.sh $EXAMPLES_DRIVER_SENSOR/INA220/driver-ina220-i2c-atmega328p
./run-build-example.sh $EXAMPLES_DRIVER_SENSOR/L3GD20/driver-l3gd20-i2c-atmega328p
./run-build-example.sh $EXAMPLES_DRIVER_SENSOR/LIS2DSH/driver-lis2dsh-i2c-atmega328p
./run-build-example.sh $EXAMPLES_DRIVER_SENSOR/LIS3DSH/driver-lis3dsh-i2c-atmega328p
./run-build-example.sh $EXAMPLES_DRIVER_SENSOR/LIS3MDL/driver-lis3mdl-i2c-atmega328p
##########################################################################
EXAMPLES_DRIVER_SERIAL="examples/driver/serial"
./run-build-example.sh $EXAMPLES_DRIVER_SERIAL/uart0-at90can128
./run-build-example.sh $EXAMPLES_DRIVER_SERIAL/uart0-atmega328p
./run-build-example.sh $EXAMPLES_DRIVER_SERIAL/uart1-at90can128
##########################################################################
EXAMPLES_DRIVER_STEPPER="examples/driver/stepper"
./run-build-example.sh $EXAMPLES_DRIVER_STEPPER/TMC260x/driver-tmc260x-spi-atmega328p
##########################################################################
EXAMPLES_HAL_AT90CAN128="examples/hal/AT90CAN128"
./run-build-example.sh $EXAMPLES_HAL_AT90CAN128/hal-at90can128-digital-in-pin
./run-build-example.sh $EXAMPLES_HAL_AT90CAN128/hal-at90can128-digital-in-port
./run-build-example.sh $EXAMPLES_HAL_AT90CAN128/hal-at90can128-digital-out-pin
./run-build-example.sh $EXAMPLES_HAL_AT90CAN128/hal-at90can128-digital-out-port
##########################################################################
EXAMPLES_HAL_AT90CAN32="examples/hal/AT90CAN32"
./run-build-example.sh $EXAMPLES_HAL_AT90CAN32/hal-at90can32-digital-in-pin
./run-build-example.sh $EXAMPLES_HAL_AT90CAN32/hal-at90can32-digital-out-pin
##########################################################################
EXAMPLES_HAL_AT90CAN64="examples/hal/AT90CAN64"
./run-build-example.sh $EXAMPLES_HAL_AT90CAN64/hal-at90can64-digital-in-pin
./run-build-example.sh $EXAMPLES_HAL_AT90CAN64/hal-at90can64-digital-out-pin
##########################################################################
EXAMPLES_HAL_ATMEGA1284P="examples/hal/ATMEGA1284P"
./run-build-example.sh $EXAMPLES_HAL_ATMEGA1284P/hal-atmega1284p-digital-in-pin
./run-build-example.sh $EXAMPLES_HAL_ATMEGA1284P/hal-atmega1284p-digital-out-pin
##########################################################################
EXAMPLES_HAL_ATMEGA2560="examples/hal/ATMEGA2560"
./run-build-example.sh $EXAMPLES_HAL_ATMEGA2560/hal-atmega2560-digital-in-pin
./run-build-example.sh $EXAMPLES_HAL_ATMEGA2560/hal-atmega2560-digital-in-port
./run-build-example.sh $EXAMPLES_HAL_ATMEGA2560/hal-atmega2560-digital-out-pin
./run-build-example.sh $EXAMPLES_HAL_ATMEGA2560/hal-atmega2560-digital-out-port
##########################################################################
EXAMPLES_HAL_ATMEGA32U4="examples/hal/ATMEGA32U4"
./run-build-example.sh $EXAMPLES_HAL_ATMEGA32U4/hal-atmega32u4-digital-in-pin
./run-build-example.sh $EXAMPLES_HAL_ATMEGA32U4/hal-atmega32u4-digital-in-port
./run-build-example.sh $EXAMPLES_HAL_ATMEGA32U4/hal-atmega32u4-digital-out-pin
./run-build-example.sh $EXAMPLES_HAL_ATMEGA32U4/hal-atmega32u4-digital-out-port
##########################################################################
EXAMPLES_HAL_ATMEGA328P="examples/hal/ATMEGA328P"
./run-build-example.sh $EXAMPLES_HAL_ATMEGA328P/hal-atmega328p-analog-digital-converter
./run-build-example.sh $EXAMPLES_HAL_ATMEGA328P/hal-atmega328p-digital-in-pin
./run-build-example.sh $EXAMPLES_HAL_ATMEGA328P/hal-atmega328p-digital-in-port
./run-build-example.sh $EXAMPLES_HAL_ATMEGA328P/hal-atmega328p-digital-out-pin
./run-build-example.sh $EXAMPLES_HAL_ATMEGA328P/hal-atmega328p-digital-out-port
