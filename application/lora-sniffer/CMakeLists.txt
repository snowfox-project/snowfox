##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET lora-sniffer)

##########################################################################

include_directories(include)

##########################################################################

add_executable(
  ${TARGET}
  
  src/main.cpp
  
  src/CommandParser.cpp
  src/SerialReader.cpp
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
