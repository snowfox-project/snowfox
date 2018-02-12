##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET driver-serial-at90can128-uart1)

##########################################################################

add_executable(
  ${TARGET}
  driver-serial-at90can128-uart1
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
