##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  if(${MCU_TYPE} STREQUAL "at90can128")
    add_subdirectory(driver-ra6963-gpio-at90can128 )
    add_subdirectory(driver-serial-at90can128-uart0)
    add_subdirectory(driver-serial-at90can128-uart1)
  endif()

  if(${MCU_TYPE} STREQUAL "atmega328p")
    add_subdirectory(driver-ad7151-i2c-atmega328p  )
    add_subdirectory(driver-as5600-i2c-atmega328p  )
    add_subdirectory(driver-bmg160-i2c-atmega328p  )
    add_subdirectory(driver-drv2605-i2c-atmega328p )
    add_subdirectory(driver-ina220-i2c-atmega328p  )
    add_subdirectory(driver-l3gd20-i2c-atmega328p  )
    add_subdirectory(driver-mcp2515-spi-atmega328p )
    add_subdirectory(driver-pca9547-i2c-atmega328p )
    add_subdirectory(driver-pcf8570-i2c-atmega328p )
    add_subdirectory(driver-serial-atmega328p-uart0)
    add_subdirectory(driver-tmc260x-spi-atmega328p )
    add_subdirectory(driver-rfm9x-spi-atmega328p   )
  endif()

endif()

##########################################################################
