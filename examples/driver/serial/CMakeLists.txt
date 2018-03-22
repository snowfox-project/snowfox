##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  if(${MCU_TYPE} STREQUAL "at90can128")
    add_subdirectory(uart0-at90can128)
    add_subdirectory(uart1-at90can128)
  endif()

  if(${MCU_TYPE} STREQUAL "atmega328p")
    add_subdirectory(uart0-atmega328p)
  endif()

endif()

##########################################################################
