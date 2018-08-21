##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET driver-mcp23017-i2c-atmega328p-debug)

##########################################################################

set(SPECTRE_ROOT_PATH "../../../../..")
include(config.cmake)
include(../../../../.cmake/example.cmake)

##########################################################################

add_executable(
  ${TARGET}
  driver-mcp23017-i2c-atmega328p-debug.cpp
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
