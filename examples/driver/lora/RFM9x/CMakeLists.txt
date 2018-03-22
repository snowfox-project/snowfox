##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  if(${MCU_TYPE} STREQUAL "atmega328p")
    add_subdirectory(driver-rfm9x-spi-atmega328p)
  endif()

endif()

##########################################################################
