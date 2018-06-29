#!/bin/bash

cd $(dirname $(readlink -f $0))

##########################################################################
# DEBUG ##################################################################
##########################################################################

./run-build-single-example.sh examples/debug/debug-serial-atmega328p-uart0


##########################################################################
# DRIVER #################################################################
##########################################################################

##########################################################################
# CAN
##########################################################################

./run-build-single-example.sh examples/driver/can/MCP2515/driver-mcp2515-spi-atmega328p-transmitter

##########################################################################
# GLCD
##########################################################################

./run-build-single-example.sh examples/driver/glcd/RA6963/driver-ra6963-gpio-at90can128

##########################################################################
# HAPTIC
##########################################################################

./run-build-single-example.sh examples/driver/haptic/DRV2605/driver-drv2605-i2c-atmega328p

##########################################################################
# IOEXPANDER
##########################################################################

./run-build-single-example.sh examples/driver/ioexpander/PCA9547/driver-pca9547-i2c-atmega328p

##########################################################################
# LORA
##########################################################################

./run-build-single-example.sh examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-receiver
./run-build-single-example.sh examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-transmitter

##########################################################################
# MEMORY
##########################################################################

./run-build-single-example.sh examples/driver/memory/PCF8570/driver-pcf8570-i2c-atmega328p

##########################################################################
# SENSOR
##########################################################################

./run-build-single-example.sh examples/driver/sensor/AD7151/driver-ad7151-i2c-atmega328p
./run-build-single-example.sh examples/driver/sensor/AS5600/driver-as5600-i2c-atmega328p
./run-build-single-example.sh examples/driver/sensor/BMG160/driver-bmg160-i2c-atmega328p
./run-build-single-example.sh examples/driver/sensor/INA220/driver-ina220-i2c-atmega328p
./run-build-single-example.sh examples/driver/sensor/L3GD20/driver-l3gd20-i2c-atmega328p
./run-build-single-example.sh examples/driver/sensor/LIS2DSH/driver-lis2dsh-i2c-atmega328p
./run-build-single-example.sh examples/driver/sensor/LIS3DSH/driver-lis3dsh-i2c-atmega328p
./run-build-single-example.sh examples/driver/sensor/LIS3MDL/driver-lis3mdl-i2c-atmega328p

##########################################################################
# SERIAL
##########################################################################

./run-build-single-example.sh examples/driver/serial/uart0-at90can128
./run-build-single-example.sh examples/driver/serial/uart1-at90can128
./run-build-single-example.sh examples/driver/serial/uart0-atmega328p

##########################################################################
# STEPPER
##########################################################################

./run-build-single-example.sh examples/driver/stepper/TMC260x/driver-tmc260x-spi-atmega328p


##########################################################################
# HAL ####################################################################
##########################################################################

##########################################################################
# AT90CAN128
##########################################################################

./run-build-single-example.sh examples/hal/AT90CAN128/hal-at90can128-digital-in-pin
./run-build-single-example.sh examples/hal/AT90CAN128/hal-at90can128-digital-in-port
./run-build-single-example.sh examples/hal/AT90CAN128/hal-at90can128-digital-out-pin
./run-build-single-example.sh examples/hal/AT90CAN128/hal-at90can128-digital-out-port

##########################################################################
# AT90CAN32
##########################################################################

./run-build-single-example.sh examples/hal/AT90CAN32/hal-at90can32-digital-in-pin
./run-build-single-example.sh examples/hal/AT90CAN32/hal-at90can32-digital-out-pin

##########################################################################
# AT90CAN64
##########################################################################

./run-build-single-example.sh examples/hal/AT90CAN64/hal-at90can64-digital-in-pin
./run-build-single-example.sh examples/hal/AT90CAN64/hal-at90can64-digital-out-pin


##########################################################################
