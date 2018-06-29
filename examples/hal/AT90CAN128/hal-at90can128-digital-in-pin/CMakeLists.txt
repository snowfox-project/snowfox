##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET hal-at90can128-digital-in-pin)

##########################################################################

set(SPECTRE_ROOT_PATH "../../../..")
include(config.cmake)
include(../../../.cmake/example.cmake)

##########################################################################

add_executable(
  ${TARGET}
  hal-at90can128-digital-in-pin.cpp
)

target_link_libraries(
  ${TARGET}
  spectre-at90can128
)


set_target_properties(
  ${TARGET}

  PROPERTIES
    LINK_FLAGS "-mmcu=${MCU_TYPE}"
)

##########################################################################
