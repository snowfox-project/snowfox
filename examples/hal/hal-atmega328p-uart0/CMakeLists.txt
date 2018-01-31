##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET hal-atmega328p-uart0)

##########################################################################

add_executable(
  ${TARGET}
  hal-atmega328p-uart0.cpp
  SystemBuilder.cpp
  UARTTaskInputHandler.cpp
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
