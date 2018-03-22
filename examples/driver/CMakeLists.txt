##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  if(${MCU_TYPE} STREQUAL "at90can128")
    add_subdirectory(driver-ra6963-gpio-at90can128 )
  endif()

  if(${MCU_TYPE} STREQUAL "atmega328p")
    add_subdirectory(driver-l3gd20-i2c-atmega328p  )
    add_subdirectory(driver-lis2dsh-i2c-atmega328p )
    add_subdirectory(driver-lis3dsh-i2c-atmega328p )
    add_subdirectory(driver-lis3mdl-i2c-atmega328p )
    add_subdirectory(driver-mcp2515-spi-atmega328p )
    add_subdirectory(driver-pca9547-i2c-atmega328p )
    add_subdirectory(driver-pcf8570-i2c-atmega328p )
    add_subdirectory(driver-tmc260x-spi-atmega328p )
    add_subdirectory(driver-rfm9x-spi-atmega328p   )
  endif()

endif()

##########################################################################

add_subdirectory(sensor)
add_subdirectory(serial)

##########################################################################
