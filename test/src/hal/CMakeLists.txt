##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(SPECTRE_HOST_TEST_TARGET test-host)

set(SPECTRE_HOST_TEST_SRCS
  src/hal/avr/test-main-hal-avr.cpp
  
  src/hal/avr/ATxxxx/test_DigitalOutPin.cpp
  src/hal/avr/ATxxxx/test_DigitalOutPort.cpp
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
