##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

project(snowfox)

##########################################################################

include_directories(include)

##########################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

##########################################################################
# CONFIGURATION ##########################################################
##########################################################################

set(SNOWFOX_APPLICATON_TARGET "")
set(SNOWFOX_APPLICATON_SRCS "")
include(config.cmake)

##########################################################################
# SRCS ###################################################################
##########################################################################

set(SNOWFOX_LIBRARY_BLOX_SRCS "")
include(.cmake/blox-srcs.cmake)

set(SNOWFOX_LIBRARY_COMSTACK_SRCS "")
include(.cmake/comstack-srcs.cmake)

set(SNOWFOX_LIBRARY_CPU_SRCS "")
include(.cmake/cpu-srcs.cmake)

set(SNOWFOX_LIBRARY_HAL_SRCS "")
include(.cmake/hal-srcs.cmake)

set(SNOWFOX_LIBRARY_DRIVER_SRCS "")
include(.cmake/driver-srcs.cmake)

set(SNOWFOX_LIBRARY_OS_SRCS "")
include(.cmake/os-srcs.cmake)

set(SNOWFOX_LIBRARY_TRACE_SRCS "")
include(.cmake/trace-srcs.cmake)

set(SNOWFOX_LIBRARY_UTIL_SRCS "")
include(.cmake/util-srcs.cmake)

set(SNOWFOX_LIBRARY_SRCS
  ${SNOWFOX_LIBRARY_BLOX_SRCS}
  ${SNOWFOX_LIBRARY_COMSTACK_SRCS}
  ${SNOWFOX_LIBRARY_CPU_SRCS}
  ${SNOWFOX_LIBRARY_HAL_SRCS}
  ${SNOWFOX_LIBRARY_DRIVER_SRCS}
  ${SNOWFOX_LIBRARY_OS_SRCS}
  ${SNOWFOX_LIBRARY_TRACE_SRCS}
  ${SNOWFOX_LIBRARY_UTIL_SRCS}
)

##########################################################################
# LIBRARY ################################################################
##########################################################################

set(SNOWFOX_CMAKE_ASM_FLAGS        "")
set(SNOWFOX_CMAKE_C_FLAGS          "")
set(SNOWFOX_CMAKE_CXX_FLAGS        "")
set(SNOWFOX_CMAKE_EXE_LINKER_FLAGS "")

##########################################################################

if(${MCU_ARCH} STREQUAL "host")
  include(.cmake/host-gcc.cmake)
endif()

if(${MCU_ARCH} STREQUAL "avr")
  include(.cmake/avr-gcc.cmake)
endif()

if(${MCU_ARCH} STREQUAL "riscv64")
  include(.cmake/riscv64-gcc.cmake)
endif()

include(.cmake/all-gcc.cmake)

##########################################################################

set(CMAKE_ASM_FLAGS        ${CMAKE_ASM_FLAGS}        ${SNOWFOX_CMAKE_ASM_FLAGS})
set(CMAKE_C_FLAGS          ${CMAKE_C_FLAGS}          ${SNOWFOX_CMAKE_C_FLAGS}  )
set(CMAKE_CXX_FLAGS        ${CMAKE_CXX_FLAGS}        ${SNOWFOX_CMAKE_CXX_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${SNOWFOX_CMAKE_EXE_LINKER_FLAGS})

##########################################################################

if(${MCU_ARCH} STREQUAL "host")
  set(SNOWFOX_LIBRARY_TARGET ${PROJECT_NAME}-host)
else()
  set(SNOWFOX_LIBRARY_TARGET ${PROJECT_NAME}-${MCU_TYPE})
endif()

##########################################################################

add_library(
  ${SNOWFOX_LIBRARY_TARGET} 
  STATIC
  ${SNOWFOX_LIBRARY_SRCS}
)

add_executable(
  ${SNOWFOX_APPLICATON_TARGET}
  src/main.cpp
  ${SNOWFOX_APPLICATON_SRCS}
)

target_link_libraries(
  ${SNOWFOX_APPLICATON_TARGET}
  ${SNOWFOX_LIBRARY_TARGET}
)

##########################################################################
# TEST ###################################################################
##########################################################################

if(${MCU_ARCH} STREQUAL "host")
 add_subdirectory(test)
endif()

##########################################################################
