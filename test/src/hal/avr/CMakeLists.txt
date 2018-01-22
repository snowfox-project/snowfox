##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(SPECTRE_TEST_HOST_HAL_AVR_TARGET test-host-hal-avr)

set(SPECTRE_TEST_HOST_HAL_AVR_SRCS
  test-main-hal-avr.cpp
  
  AT90CAN128/test_TIMER0.cpp
  AT90CAN128/test_TIMER1.cpp
  AT90CAN128/test_TIMER3.cpp
  
  ATMEGA328P/test_InterruptController.cpp
  ATMEGA328P/test_SPIMaster.cpp
  ATMEGA328P/test_TIMER0.cpp
  ATMEGA328P/test_TIMER1.cpp
  ATMEGA328P/test_TIMER2.cpp
  
  ATxxxx/test_DigitalInPin.cpp
  ATxxxx/test_DigitalInPort.cpp
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
  gcov
)

##########################################################################
