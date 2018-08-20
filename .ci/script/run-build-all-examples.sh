#!/bin/bash
##########################################################################
cd $(dirname $(readlink -f $0))
set -e
##########################################################################
declare -a EXAMPLE_LIST=("examples/debug/debug-serial-atmega328p-uart0"
                         "examples/debug/debug-serial-atmega1284p-uart0"
                         "examples/driver/can/MCP2515/driver-mcp2515-spi-atmega328p-debug"
                         "examples/driver/can/MCP2515/driver-mcp2515-spi-atmega328p-transmitter"
                         "examples/driver/glcd/RA6963/driver-ra6963-gpio-at90can128"
                         "examples/driver/haptic/DRV2605/driver-drv2605-i2c-atmega328p"
                         "examples/driver/haptic/DRV2605/driver-drv2605-i2c-atmega328p-debug"
                         "examples/driver/ioexpander/PCA9547/driver-pca9547-i2c-atmega328p"
                         "examples/driver/ioexpander/MCP23017/driver-mcp23017-i2c-atmega328p"
                         "examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega1284p-debug-moteino-mega-usb"
                         "examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-debug-dragino-lora-shield-v1.4"
                         "examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-receiver-dragino-lora-shield-v1.4"
                         "examples/driver/lora/RFM9x/driver-rfm9x-spi-atmega328p-transmitter-dragino-lora-shield-v1.4"
                         "examples/driver/memory/PCF8570/driver-pcf8570-i2c-atmega328p"
                         "examples/driver/sensor/AD7151/driver-ad7151-i2c-atmega328p"
                         "examples/driver/sensor/AD7151/driver-ad7151-i2c-atmega328p-debug"
                         "examples/driver/sensor/AS5600/driver-as5600-i2c-atmega328p"
                         "examples/driver/sensor/BMG160/driver-bmg160-i2c-atmega328p"
                         "examples/driver/sensor/INA220/driver-ina220-i2c-atmega328p"
                         "examples/driver/sensor/L3GD20/driver-l3gd20-i2c-atmega328p"
                         "examples/driver/sensor/LIS2DSH/driver-lis2dsh-i2c-atmega328p"
                         "examples/driver/sensor/LIS3DSH/driver-lis3dsh-i2c-atmega328p"
                         "examples/driver/sensor/LIS3MDL/driver-lis3mdl-i2c-atmega328p"
                         "examples/driver/serial/uart0-at90can128"
                         "examples/driver/serial/uart0-atmega328p"
                         "examples/driver/serial/uart1-at90can128"
                         "examples/driver/stepper/TMC260x/driver-tmc260x-spi-atmega328p"
                         "examples/driver/tlcd/HD44780/driver-hd44780-gpio-atmega328p"
                         "examples/hal/AT90CAN128/hal-at90can128-digital-in-pin"
                         "examples/hal/AT90CAN128/hal-at90can128-digital-in-port"
                         "examples/hal/AT90CAN128/hal-at90can128-digital-out-pin"
                         "examples/hal/AT90CAN128/hal-at90can128-digital-out-port"
                         "examples/hal/AT90CAN32/hal-at90can32-digital-in-pin"
                         "examples/hal/AT90CAN32/hal-at90can32-digital-out-pin"
                         "examples/hal/AT90CAN64/hal-at90can64-digital-in-pin"
                         "examples/hal/AT90CAN64/hal-at90can64-digital-out-pin"
                         "examples/hal/ATMEGA1284P/hal-atmega1284p-digital-in-pin"
                         "examples/hal/ATMEGA1284P/hal-atmega1284p-digital-out-pin"
                         "examples/hal/ATMEGA2560/hal-atmega2560-digital-in-pin"
                         "examples/hal/ATMEGA2560/hal-atmega2560-digital-in-port"
                         "examples/hal/ATMEGA2560/hal-atmega2560-digital-out-pin"
                         "examples/hal/ATMEGA2560/hal-atmega2560-digital-out-port"
                         "examples/hal/ATMEGA32U4/hal-atmega32u4-digital-in-pin"
                         "examples/hal/ATMEGA32U4/hal-atmega32u4-digital-in-port"
                         "examples/hal/ATMEGA32U4/hal-atmega32u4-digital-out-pin"
                         "examples/hal/ATMEGA32U4/hal-atmega32u4-digital-out-port"
                         "examples/hal/ATMEGA328P/hal-atmega328p-analog-digital-converter"
                         "examples/hal/ATMEGA328P/hal-atmega328p-digital-in-pin"
                         "examples/hal/ATMEGA328P/hal-atmega328p-digital-in-port"
                         "examples/hal/ATMEGA328P/hal-atmega328p-digital-out-pin"
                         "examples/hal/ATMEGA328P/hal-atmega328p-digital-out-port"
                        )

NUM_LIST_ENTRIES=${#EXAMPLE_LIST[@]}

RED='tput setaf 1'
RESET='tput sgr0'

for (( i=0; i<${NUM_LIST_ENTRIES}; i++ ));
do
  $RED
  echo "[ " $(($i+1)) " / " ${NUM_LIST_ENTRIES} " ] " ${EXAMPLE_LIST[$i]}
  $RESET
  ./run-build-example.sh ${EXAMPLE_LIST[$i]}
done

##########################################################################

