##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  if(${MCU_TYPE} STREQUAL "at90can128")
    add_subdirectory(driver-serial-at90can128-uart0)
    add_subdirectory(driver-serial-at90can128-uart1)
  endif()

  if(${MCU_TYPE} STREQUAL "atmega328p")
    add_subdirectory(driver-serial-atmega328p-uart0)
  endif()

endif()

##########################################################################
