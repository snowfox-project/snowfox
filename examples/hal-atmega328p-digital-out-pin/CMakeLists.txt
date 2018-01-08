##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET hal-atmega328p-digital-out-pin)

##########################################################################

add_executable(
  ${TARGET}
  hal-atmega328p-digital-out-pin.cpp
)

target_link_libraries(
  ${TARGET}
  spectre-atmega328p
)


set_target_properties(
  ${TARGET}

  PROPERTIES
    COMPILE_FLAGS "-mmcu=${MCU_TYPE} -DF_CPU=${MCU_SPEED} -Os -Wall -pedantic -pedantic-errors -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -std=c++11"
    LINK_FLAGS    "-mmcu=${MCU_TYPE}"
)

##########################################################################
