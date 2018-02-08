##########################################################################
# HAL ####################################################################
##########################################################################

##########################################################################
# INTERFACE ##############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_INTERFACE_PATH src/hal/interface)

set(SPECTRE_LIBRARY_HAL_INTERFACE_SRCS
  ${SPECTRE_LIBRARY_HAL_INTERFACE_PATH}/can/CanFrame.cpp
  ${SPECTRE_LIBRARY_HAL_INTERFACE_PATH}/locking/LockGuard.cpp
)

##########################################################################
# AVR ####################################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_PATH src/hal/avr)

##########################################################################
# ATxxxx #################################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATxxxx_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATxxxx/Delay.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATxxxx/CriticalSection.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATxxxx/DigitalInOutPort.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATxxxx/DigitalInPin.cpp    
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATxxxx/DigitalInPort.cpp   
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATxxxx/DigitalOutPin.cpp   
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATxxxx/DigitalOutPort.cpp  
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATxxxx/I2CMasterBase.cpp       
)

##########################################################################
# ATMEGA328P #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/I2CMaster.cpp          
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/InterruptController.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/SPIMaster.cpp          
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER1.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER2.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/UART0.cpp              
)

##########################################################################
# AT90CAN128 #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_AT90CAN128_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/AT90CAN128/InterruptController.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/AT90CAN128/TIMER0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/AT90CAN128/TIMER1.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/AT90CAN128/TIMER2.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/AT90CAN128/TIMER3.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/AT90CAN128/UART0.cpp
)

##########################################################################

set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_INTERFACE_SRCS})

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATxxxx_SRCS})

  if(${MCU_TYPE} STREQUAL "atmega328p")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS})  
  endif()
  
  if(${MCU_TYPE} STREQUAL "at90can128")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN128_SRCS})  
  endif()
endif()

##########################################################################

if(${MCU_ARCH} STREQUAL "host")
  
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATxxxx_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS})  
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN128_SRCS})  

endif()

##########################################################################

