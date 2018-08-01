##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET driver-rfm9x-spi-atmega1284p-debug-moteino-mega-usb)

##########################################################################

set(SPECTRE_ROOT_PATH "../../../../..")
include(config.cmake)
include(../../../../.cmake/example.cmake)

##########################################################################

add_executable(
  ${TARGET}

  driver-rfm9x-spi-atmega1284p-debug-moteino-mega-usb.cpp
)

target_link_libraries(
  ${TARGET}
  spectre-atmega1284p
)

set_target_properties(
  ${TARGET}

  PROPERTIES
    LINK_FLAGS "-mmcu=${MCU_TYPE}"
)

##########################################################################
