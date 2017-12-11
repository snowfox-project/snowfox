##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

project(spectre)

##########################################################################

include_directories(include)

##########################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)

##########################################################################

SET(CMAKE_C_COMPILER avr-gcc)
SET(CMAKE_CXX_COMPILER avr-g++)

SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-Wl,--relax,--gc-sections")

##########################################################################

set(AVR_MCU_SPEED 16000000UL)
set(AVR_MCU_TYPE atmega328p)

############################################################################

set(SPECTRE_LIBRARY_NAME ${PROJECT_NAME}-${AVR_MCU_TYPE})

##########################################################################

set(SPECTRE_LIBRARY_GENERIC_SRCS
  src/hal/avr/ATMEGA328P/I2CMaster.cpp
  src/hal/avr/ATMEGA328P/UART0.cpp
  
  src/hal/avr/ATxxxx/I2CMaster.cpp
  
  src/hal/avr/cxx/cxx.cpp
)

##########################################################################
  
add_library(
  ${SPECTRE_LIBRARY_NAME} 
  STATIC
  ${SPECTRE_LIBRARY_GENERIC_SRCS}
)

##########################################################################

set_target_properties(
  ${SPECTRE_LIBRARY_NAME}
  
  PROPERTIES
    COMPILE_FLAGS "-mmcu=${AVR_MCU_TYPE} -DF_CPU=${AVR_MCU_SPEED} -Os -Wall -pedantic -pedantic-errors -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -std=c++11"
    OUTPUT_NAME   "${SPECTRE_LIBRARY_NAME}"
)
  
##########################################################################

add_subdirectory(examples)

##########################################################################
