##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  if(${MCU_TYPE} STREQUAL "at90can128")
    add_subdirectory(hal-at90can128-digital-in-pin  )
    add_subdirectory(hal-at90can128-digital-in-port )
    add_subdirectory(hal-at90can128-digital-out-pin )
    add_subdirectory(hal-at90can128-digital-out-port)
  endif()

  if(${MCU_TYPE} STREQUAL "atmega328p")
    add_subdirectory(hal-atmega328p-analog-digital-converter)
    add_subdirectory(hal-atmega328p-digital-in-pin          )
    add_subdirectory(hal-atmega328p-digital-in-port         )
    add_subdirectory(hal-atmega328p-digital-out-pin         )
    add_subdirectory(hal-atmega328p-digital-out-port        )
  endif()

  if(${MCU_TYPE} STREQUAL "atmega32u4")
    add_subdirectory(hal-atmega32u4-digital-in-pin)
  endif()
  
endif()

##########################################################################
