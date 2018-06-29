##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET hal-atmega328p-analog-digital-converter)

##########################################################################

set(SPECTRE_ROOT_PATH "../../../..")
include(config.cmake)
include(../../../.cmake/example.cmake)

##########################################################################

add_executable(
  ${TARGET}
  hal-atmega328p-analog-digital-converter.cpp
)

target_link_libraries(
  ${TARGET}
  spectre-atmega328p
)


set_target_properties(
  ${TARGET}

  PROPERTIES
    LINK_FLAGS "-mmcu=${MCU_TYPE}"
)

##########################################################################
