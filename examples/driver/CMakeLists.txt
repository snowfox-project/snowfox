##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  if(${MCU_TYPE} STREQUAL "at90can128")
    add_subdirectory(driver-ra6963-gpio-at90can128 )
  endif()

  if(${MCU_TYPE} STREQUAL "atmega328p")
    add_subdirectory(driver-pca9547-i2c-atmega328p )
    add_subdirectory(driver-pcf8570-i2c-atmega328p )
  endif()

endif()

##########################################################################

add_subdirectory(can    )
add_subdirectory(lora   )
add_subdirectory(sensor )
add_subdirectory(serial )
add_subdirectory(stepper)

##########################################################################
