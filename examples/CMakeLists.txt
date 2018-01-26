##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  if(${MCU_TYPE} STREQUAL "at90can128")
    add_subdirectory(hal-at90can128-digital-in-pin )
    add_subdirectory(hal-at90can128-digital-out-pin)
  endif()

  if(${MCU_TYPE} STREQUAL "atmega328p")
    add_subdirectory(driver-drv2605-i2c-atmega328p )
    add_subdirectory(driver-mcp2515-spi-atmega328p )
    add_subdirectory(driver-pca9547-i2c-atmega328p )
    add_subdirectory(driver-pcf8570-i2c-atmega328p )
    add_subdirectory(hal-atmega328p-digital-in-pin )
    add_subdirectory(hal-atmega328p-digital-out-pin)
    add_subdirectory(hal-atmega328p-uart0          )
  endif()

endif()

##########################################################################
