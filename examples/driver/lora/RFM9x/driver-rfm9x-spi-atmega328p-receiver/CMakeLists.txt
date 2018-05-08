##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET driver-rfm9x-spi-atmega328p-receiver)

##########################################################################

include_directories(include)

##########################################################################

add_executable(
  ${TARGET}
  
  src/driver-rfm9x-spi-atmega328p-receiver.cpp
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
