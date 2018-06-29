##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET driver-serial-uart0-at90can128)

##########################################################################

set(SPECTRE_ROOT_PATH "../../../..")
include(config.cmake)
include(../../../.cmake/example.cmake)

##########################################################################

add_executable(
  ${TARGET}
  driver-serial-uart0-at90can128.cpp
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
