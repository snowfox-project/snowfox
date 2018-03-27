##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET hal-atmega2560-digital-out-port)

##########################################################################

add_executable(
  ${TARGET}
  hal-atmega2560-digital-out-port.cpp
)

target_link_libraries(
  ${TARGET}
  spectre-atmega2560
)


set_target_properties(
  ${TARGET}

  PROPERTIES
    LINK_FLAGS "-mmcu=${MCU_TYPE}"
)

##########################################################################
