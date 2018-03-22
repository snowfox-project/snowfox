##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  if(${MCU_TYPE} STREQUAL "at90can128")
    add_subdirectory(at90can128)
  endif()

  if(${MCU_TYPE} STREQUAL "atmega2560")
    add_subdirectory(atmega2560)
  endif()

  if(${MCU_TYPE} STREQUAL "atmega328p")
    add_subdirectory(atmega328p)
  endif()

  if(${MCU_TYPE} STREQUAL "atmega32u4")
    add_subdirectory(atmega32u4)
  endif()
  
endif()

##########################################################################
