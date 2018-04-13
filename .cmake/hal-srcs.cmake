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
# common/AT90CANxxxx #####################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/InterruptController.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER1.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER2.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER3.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/UART0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/UART1.cpp
)

##########################################################################
# common/ATxxxx ##########################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATxxxx_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/Delay.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/CriticalSection.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalInOutPort.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalInPin.cpp    
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalInPort.cpp   
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalOutPin.cpp   
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalOutPort.cpp  
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/I2CMasterBase.cpp       
)

##########################################################################
# AT90CAN32  #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS}
)

##########################################################################
# AT90CAN64  #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_AT90CAN64_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS}
)

##########################################################################
# AT90CAN128 #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_AT90CAN128_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS}
)

##########################################################################
# ATMEGA2560 #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA2560_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA2560/TIMER0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA2560/TIMER1.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA2560/TIMER2.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA2560/TIMER3.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA2560/TIMER4.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA2560/TIMER5.cpp
)

##########################################################################
# ATMEGA328P #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/AnalogDigitalConverter.cpp        
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/EINT0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/EINT1.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/I2CMaster.cpp          
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/InterruptController.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/SPIMaster.cpp          
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER1.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER2.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/UART0.cpp              
)

##########################################################################
# ATMEGA32U4 #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA32U4_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA32U4/TIMER0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA32U4/TIMER1.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA32U4/TIMER3.cpp
)

##########################################################################

set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_INTERFACE_SRCS})

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATxxxx_SRCS})

  if(${MCU_TYPE} STREQUAL "at90can32")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_SRCS})  
  endif()

  if(${MCU_TYPE} STREQUAL "at90can64")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN64_SRCS})  
  endif()

  if(${MCU_TYPE} STREQUAL "at90can128")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN128_SRCS})  
  endif()
  
  if(${MCU_TYPE} STREQUAL "atmega2560")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA2560_SRCS})
  endif()
  
  if(${MCU_TYPE} STREQUAL "atmega328p")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS})  
  endif()

  if(${MCU_TYPE} STREQUAL "atmega32u4")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA32U4_SRCS})  
  endif()

endif()

##########################################################################

if(${MCU_ARCH} STREQUAL "host")
  
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATxxxx_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN64_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN128_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA2560_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA32U4_SRCS})

endif()

##########################################################################

