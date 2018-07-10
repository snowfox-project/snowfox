##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET hal-atmega1284p-digital-out-pin)

##########################################################################

set(SPECTRE_ROOT_PATH "../../../..")
include(config.cmake)
include(../../../.cmake/example.cmake)

##########################################################################

add_executable(
  ${TARGET}
  hal-atmega1284p-digital-out-pin.cpp
)

target_link_libraries(
  ${TARGET}
  spectre-atmega1284p
)


set_target_properties(
  ${TARGET}

  PROPERTIES
    LINK_FLAGS "-mmcu=${MCU_TYPE}"
)

##########################################################################
