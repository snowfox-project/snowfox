##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET driver-lis3dsh-i2c-atmega328p)

##########################################################################

add_executable(
  ${TARGET}
  driver-lis3dsh-i2c-atmega328p.cpp
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
