##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET driver-mcp2515-spi-atmega328p-transmitter)

##########################################################################

add_executable(
  ${TARGET}
  driver-mcp2515-spi-atmega328p-transmitter.cpp
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
