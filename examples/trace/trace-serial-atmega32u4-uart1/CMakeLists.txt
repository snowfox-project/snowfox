##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET trace-serial-atmega32u4-uart1)

##########################################################################

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

##########################################################################

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

##########################################################################

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-mmcu=atmega32u4 -DF_CPU=16000000UL -std=c++11 -Os -Wall -pedantic -pedantic-errors -funsigned-char -funsigned-bitfields -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-Wl,--relax,--gc-sections")

##########################################################################

add_executable(
  ${TARGET}
  trace-serial-atmega32u4-uart1.cpp
)

target_link_libraries(
  ${TARGET}
  spectre-atmega32u4
)

set_target_properties(
  ${TARGET}

  PROPERTIES
    LINK_FLAGS "-mmcu=atmega32u4"
)

##########################################################################
