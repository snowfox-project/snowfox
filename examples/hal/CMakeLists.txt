##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  if(${MCU_TYPE} STREQUAL "at90can128")
    add_subdirectory(AT90CAN128)
  endif()
  
  if(${MCU_TYPE} STREQUAL "at90can32")
    add_subdirectory(AT90CAN32)
  endif()
  
  if(${MCU_TYPE} STREQUAL "at90can64")
    add_subdirectory(AT90CAN64)
  endif()
  
  if(${MCU_TYPE} STREQUAL "atmega2560")
    add_subdirectory(ATMEGA2560)
  endif()

  if(${MCU_TYPE} STREQUAL "atmega328p")
    add_subdirectory(ATMEGA328P)
  endif()

  if(${MCU_TYPE} STREQUAL "atmega32u4")
    add_subdirectory(ATMEGA32U4)
  endif()
  
endif()

##########################################################################
