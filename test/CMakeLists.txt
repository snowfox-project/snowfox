##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

include_directories(include)
include_directories(external/catch/current/include)

##########################################################################

set(SPECTRE_HOST_TEST_TARGET test-host)

set(SPECTRE_HOST_TEST_SRCS
  src/test-main.cpp
  
  src/hal/avr/ATxxxx/test_DigitalOutPin.cpp
)

##########################################################################

add_executable(
  ${SPECTRE_HOST_TEST_TARGET}
  ${SPECTRE_HOST_TEST_SRCS}
)

target_link_libraries(
  ${SPECTRE_HOST_TEST_TARGET}
  spectre-host
)

##########################################################################
