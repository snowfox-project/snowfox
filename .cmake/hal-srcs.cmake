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
# common/AT90CAN32_64_128 ################################################
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
# common/ATMEGA16U4_32U4 #################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_32U4_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA16U4_32U4/TIMER0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA16U4_32U4/TIMER1.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA16U4_32U4/TIMER3.cpp
)

##########################################################################
# common/ATMEGA640_1280_2560 #############################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/InterruptController.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER1.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER2.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER3.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER4.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER5.cpp
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
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/EINT0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/EINT1.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/EINT2.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/EINT3.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/EINT4.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/EINT5.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/EINT6.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/EINT7.cpp  
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/Flash.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/I2CMasterBase.cpp       
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/SpiMaster.cpp
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
# ATMEGA640 ##############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS}
)

##########################################################################
# ATMEGA1280 #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA1280_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS}
)

##########################################################################
# ATMEGA2560 #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA2560_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS}
)

##########################################################################
# ATMEGA328P #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/AnalogDigitalConverter.cpp        
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/I2CMaster.cpp          
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/InterruptController.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER0.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER1.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER2.cpp
  ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/UART0.cpp              
)

##########################################################################
# ATMEGA16U4 #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_32U4_SRCS}
)

##########################################################################
# ATMEGA32U4 #############################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA32U4_SRCS
  ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_32U4_SRCS}
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

  if(${MCU_TYPE} STREQUAL "atmega640")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_SRCS})
  endif()

  if(${MCU_TYPE} STREQUAL "atmega1280")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA1280_SRCS})
  endif()
  
  if(${MCU_TYPE} STREQUAL "atmega2560")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA2560_SRCS})
  endif()
  
  if(${MCU_TYPE} STREQUAL "atmega328p")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS})  
  endif()

  if(${MCU_TYPE} STREQUAL "atmega16u4")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_SRCS})  
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
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA1280_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA2560_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA32U4_SRCS})

endif()

##########################################################################
