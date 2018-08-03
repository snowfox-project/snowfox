##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET driver-rfm9x-spi-atmega328p-debug-dragino-lora-shield-v1.4)

##########################################################################

set(SPECTRE_ROOT_PATH "../../../../..")
include(config.cmake)
include(../../../../.cmake/example.cmake)

##########################################################################

add_executable(
  ${TARGET}
  
  driver-rfm9x-spi-atmega328p-debug-dragino-lora-shield-v1.4.cpp
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
