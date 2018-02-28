##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  if(${MCU_TYPE} STREQUAL "atmega328p")
    add_subdirectory(debug-serial-atmega328p-uart0)
  endif()

endif()

##########################################################################
