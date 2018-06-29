##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(TARGET hal-atmega328p-digital-out-pin)

##########################################################################

set(SPECTRE_ROOT_PATH "../../../..")

##########################################################################

include_directories(${SPECTRE_ROOT_PATH}/include)
cmake_policy(SET CMP0015 NEW)
link_directories(${SPECTRE_ROOT_PATH}/build/lib)

##########################################################################
# SPECTRE LIBRARY CONFIGURATION ##########################################
##########################################################################

include(config.cmake)

##########################################################################
# EXAMPLE EXECUTABLE CONFIGURATION #######################################
##########################################################################

set(SPECTRE_CMAKE_C_FLAGS   "")
set(SPECTRE_CMAKE_CXX_FLAGS "")

##########################################################################

include(${SPECTRE_ROOT_PATH}/.cmake/avr-gcc.cmake)
include(${SPECTRE_ROOT_PATH}/.cmake/all-gcc.cmake)

##########################################################################

set(CMAKE_C_FLAGS   ${CMAKE_C_FLAGS}   ${SPECTRE_CMAKE_C_FLAGS}  )
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${SPECTRE_CMAKE_CXX_FLAGS})

##########################################################################
# EXECUTABLE #############################################################
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
    LINK_FLAGS "-mmcu=${MCU_TYPE}"
)

##########################################################################
