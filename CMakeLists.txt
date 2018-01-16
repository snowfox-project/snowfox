##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

project(spectre)

##########################################################################

include_directories(include)

##########################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

##########################################################################
# CONFIGURATION ##########################################################
##########################################################################

include(config.cmake)

##########################################################################
# SRCS ###################################################################
##########################################################################

set(SPECTRE_LIBRARY_CXX_SRCS "")
include(.cmake/cxx-srcs.cmake)

set(SPECTRE_LIBRARY_HAL_SRCS "")
include(.cmake/hal-srcs.cmake)

set(SPECTRE_LIBRARY_DRIVER_SRCS "")
include(.cmake/driver-srcs.cmake)

set(SPECTRE_LIBRARY_SRCS
  ${SPECTRE_LIBRARY_CXX_SRCS}
  ${SPECTRE_LIBRARY_HAL_SRCS}
  ${SPECTRE_LIBRARY_DRIVER}
)

##########################################################################
# LIBRARY ################################################################
##########################################################################

if(${MCU_ARCH} STREQUAL "host")
  include(.cmake/host-gcc.cmake)
endif()

if(${MCU_ARCH} STREQUAL "avr")
  include(.cmake/avr-gcc.cmake)
endif()

include(.cmake/all-gcc.cmake)

##########################################################################

if(${MCU_ARCH} STREQUAL "host")
  set(SPECTRY_LIBRARY_NAME_MCU ${PROJECT_NAME}-host)
else()
  set(SPECTRY_LIBRARY_NAME_MCU ${PROJECT_NAME}-${MCU_TYPE})
endif()

##########################################################################

add_library(
  ${SPECTRY_LIBRARY_NAME_MCU} 
  STATIC
  ${SPECTRE_LIBRARY_SRCS}
)

##########################################################################
# EXAMPLES ###############################################################
##########################################################################

add_subdirectory(examples)

##########################################################################
# TEST ###################################################################
##########################################################################

if(${MCU_ARCH} STREQUAL "host")
  add_subdirectory(test)
endif()

##########################################################################
