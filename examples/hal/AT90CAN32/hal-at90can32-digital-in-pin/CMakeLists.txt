##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET hal-at90can32-digital-in-pin)

##########################################################################

add_executable(
  ${TARGET}
  hal-at90can32-digital-in-pin.cpp
)

target_link_libraries(
  ${TARGET}
  spectre-at90can32
)


set_target_properties(
  ${TARGET}

  PROPERTIES
    LINK_FLAGS "-mmcu=${MCU_TYPE}"
)

##########################################################################
