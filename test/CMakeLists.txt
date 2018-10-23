##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

include_directories(include)
include_directories(external/catch/current/include)

##########################################################################

set(SPECTRE_TEST_HOST_TARGET test-host)

##########################################################################
# HAL ####################################################################
##########################################################################

set(SPECTRE_TEST_HAL_PATH src/hal)

##########################################################################
# AVR ####################################################################
##########################################################################

set(SPECTRE_TEST_HAL_AVR_PATH ${SPECTRE_TEST_HAL_PATH}/avr)

set(SPECTRE_TEST_HOST_HAL_AVR_AT90CAN128_SRCS
  ${SPECTRE_TEST_HAL_AVR_PATH}/AT90CAN128/test_InterruptController.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/AT90CAN128/test_TIMER0.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/AT90CAN128/test_TIMER1.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/AT90CAN128/test_TIMER2.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/AT90CAN128/test_TIMER3.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/AT90CAN128/test_UART0.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/AT90CAN128/test_UART1.cpp
)

##########################################################################

set(SPECTRE_TEST_HOST_HAL_AVR_ATMEGA328P_SRCS
  ${SPECTRE_TEST_HAL_AVR_PATH}/ATMEGA328P/test_InterruptController.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/ATMEGA328P/test_TIMER0.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/ATMEGA328P/test_TIMER1.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/ATMEGA328P/test_TIMER2.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/ATMEGA328P/test_UART0.cpp
)

##########################################################################

set(SPECTRE_TEST_HOST_HAL_AVR_ATxxxx_SRCS
  ${SPECTRE_TEST_HAL_AVR_PATH}/ATxxxx/test_DigitalInPin.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/ATxxxx/test_DigitalInPort.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/ATxxxx/test_DigitalOutPin.cpp
  ${SPECTRE_TEST_HAL_AVR_PATH}/ATxxxx/test_DigitalOutPort.cpp
)

##########################################################################

set(SPECTRE_TEST_HOST_HAL_AVR_SRCS
  ${SPECTRE_TEST_HOST_HAL_AVR_AT90CAN128_SRCS}
  ${SPECTRE_TEST_HOST_HAL_AVR_ATMEGA328P_SRCS}
  ${SPECTRE_TEST_HOST_HAL_AVR_ATxxxx_SRCS}
)

##########################################################################

set(SPECTRE_TEST_HOST_HAL_SRCS
  ${SPECTRE_TEST_HOST_HAL_AVR_SRCS}
)

##########################################################################
# UTIL ###################################################################
##########################################################################

set(SPECTRE_TEST_UTIL_PATH src/util)

##########################################################################

set(SPECTRE_TEST_HOST_UTIL_SRCS
  ${SPECTRE_TEST_UTIL_PATH}/container/test_List.cpp
  ${SPECTRE_TEST_UTIL_PATH}/container/test_Queue.cpp
  
  ${SPECTRE_TEST_UTIL_PATH}/type/test_StaticString.cpp
)

##########################################################################
# OS #####################################################################
##########################################################################

set(SPECTRE_TEST_OS_PATH src/os)

##########################################################################

set(SPECTRE_TEST_HOST_OS_SRCS
)

##########################################################################
# TEST ###################################################################
##########################################################################

add_executable(
  ${SPECTRE_TEST_HOST_TARGET}
  
  src/test_main.cpp
  
  ${SPECTRE_TEST_HOST_HAL_AVR_SRCS}
  ${SPECTRE_TEST_HOST_UTIL_SRCS}
  ${SPECTRE_TEST_HOST_OS_SRCS}
)

target_link_libraries(
  ${SPECTRE_TEST_HOST_TARGET}
  
  spectre-host
  gcov
)

##########################################################################
