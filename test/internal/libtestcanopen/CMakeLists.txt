##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(SNOWFOX_LIBTESTCANOPEN_TARGET testcanopen)

##########################################################################

include_directories(include)

##########################################################################

set(CMAKE_CXX_STANDARD 17)

##########################################################################

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

##########################################################################

set(SNOWFOX_LIBTESTCANOPEN_SRC_PATH src)

set(SNOWFOX_LIBTESTCANOPEN_SRCS
  ${SNOWFOX_LIBTESTCANOPEN_SRC_PATH}/events/ReceiveEvent.cpp
  ${SNOWFOX_LIBTESTCANOPEN_SRC_PATH}/events/TransmitEvent.cpp
  ${SNOWFOX_LIBTESTCANOPEN_SRC_PATH}/CanOpenTest.cpp
  ${SNOWFOX_LIBTESTCANOPEN_SRC_PATH}/TestManager.cpp
)

##########################################################################

add_library(
  ${SNOWFOX_LIBTESTCANOPEN_TARGET}
  STATIC
  ${SNOWFOX_LIBTESTCANOPEN_SRCS}
)

##########################################################################

target_include_directories(${SNOWFOX_LIBTESTCANOPEN_TARGET} PUBLIC include)

##########################################################################
