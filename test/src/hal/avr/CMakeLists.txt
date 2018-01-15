##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(SPECTRE_TEST_HOST_HAL_AVR_TARGET test-host-hal-avr)

set(SPECTRE_TEST_HOST_HAL_AVR_SRCS
  test-main-hal-avr.cpp
  
  ATxxxx/test_DigitalOutPin.cpp
  ATxxxx/test_DigitalOutPort.cpp
)

##########################################################################

add_executable(
  ${SPECTRE_TEST_HOST_HAL_AVR_TARGET}
  ${SPECTRE_TEST_HOST_HAL_AVR_SRCS}
)

target_link_libraries(
  ${SPECTRE_TEST_HOST_HAL_AVR_TARGET}
  spectre-host
)

##########################################################################
