##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET hal-atmega328p-uart0)

##########################################################################

add_executable(
  ${TARGET}
  hal-atmega328p-uart0.cpp
)

target_link_libraries(
  ${TARGET}
  spectre-atmega328p
)


set_target_properties(
  ${TARGET}

  PROPERTIES
    COMPILE_FLAGS "-mmcu=atmega328p -DF_CPU=${AVR_MCU_SPEED} -Os -Wall -pedantic -pedantic-errors -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions"
    LINK_FLAGS    "-mmcu=atmega328p"
)

##########################################################################
