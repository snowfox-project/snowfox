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
# CONFIGURATION ##########################################################
##########################################################################

include(config.cmake)

##########################################################################
# SRCS ###################################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_SRCS "")
include(.cmake/hal-srcs.cmake)

set(SPECTRE_LIBRARY_DRIVER_SRCS "")
include(.cmake/driver-srcs.cmake)

set(SPECTRE_LIBRARY_SRCS
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

if(${MCU_ARCH} STREQUAL "avr")
  set_target_properties(
    ${SPECTRY_LIBRARY_NAME_MCU}
  
    PROPERTIES
      COMPILE_FLAGS "-mmcu=${MCU_TYPE} -DF_CPU=${MCU_SPEED} -DMCU_ARCH=${MCU_ARCH} -DMCU_TYPE=${MCU_TYPE} -Os -Wall -pedantic -pedantic-errors -funsigned-char -funsigned-bitfields -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -std=c++11"
      OUTPUT_NAME   "${SPECTRE_LIBRARY_NAME}"
  )
endif()

##########################################################################
# EXAMPLES ###############################################################
##########################################################################

add_subdirectory(examples)

##########################################################################
# TEST ###################################################################
##########################################################################

add_subdirectory(test)

##########################################################################
