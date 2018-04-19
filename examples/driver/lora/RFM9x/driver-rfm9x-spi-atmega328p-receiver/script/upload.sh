#!/bin/bash
cd $(dirname $(readlink -f $0))
cd ../../../../../../bin
avrdude -p atmega328p -c avrisp2 -e -U flash:w:driver-rfm9x-spi-atmega328p-receiver
