##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET driver-serial-atmega328p)

##########################################################################

add_executable(
  ${TARGET}
  driver-serial-atmega328p
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
