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

set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_INTERFACE_SRCS})

##########################################################################
# AVR ####################################################################
##########################################################################

if(${MCU_ARCH} STREQUAL "avr" OR ${MCU_ARCH} STREQUAL "host")

  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_PATH src/hal/avr)

  ########################################################################
  # common/AT90CAN32_64_128 ##############################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/ExternalInterruptController.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/InterruptController.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER0.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER1.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER2.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER3.cpp
  )

  ########################################################################
  # common/ATMEGA164P_324P_644P_1284P ####################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA164P_324P_644P_1284P/ExternalInterruptController.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA164P_324P_644P_1284P/InterruptController.cpp
  )

  ########################################################################
  # common/ATMEGA16U4_32U4 ###############################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_32U4_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA16U4_32U4/TIMER0.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA16U4_32U4/TIMER1.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA16U4_32U4/TIMER3.cpp
  )

  ########################################################################
  # common/ATMEGA640_1280_2560 ###########################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/ExternalInterruptController.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/InterruptController.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER0.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER1.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER2.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER3.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER4.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER5.cpp
  )

  ########################################################################
  # common/ATxxxx ########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATxxxx_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/util/ExternalInterruptTriggerModeConfig.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/Delay.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/CriticalSection.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalInOutPort.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalInPin.cpp    
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalInPort.cpp   
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalOutPin.cpp   
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalOutPort.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/EEPROM.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/Flash.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/I2CMasterBase.cpp       
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/SpiMaster.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/Stack.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/UART0.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/UART1.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/UART2.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/UART3.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/UartUtil.cpp
  )
  
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATxxxx_SRCS})

  ########################################################################
  # AT90CAN128 ###########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_AT90CAN128_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "at90can128" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN128_SRCS})  
  endif()

  ########################################################################
  # AT90CAN32  ###########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "at90can32" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_SRCS})  
  endif()

  ########################################################################
  # AT90CAN64  ###########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_AT90CAN64_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "at90can64" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN64_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA1280 ###########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA1280_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega1280" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA1280_SRCS})
  endif()
  
  ########################################################################
  # ATMEGA1284P ##########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA1284P_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega1284p" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA1284P_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA164P ###########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA164P_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )

  if(${MCU_TYPE} STREQUAL "atmega164p" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA164P_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA16U4 ###########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_32U4_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega16u4" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA2560 ###########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA2560_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega2560" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA2560_SRCS})
  endif()

  ########################################################################
  # ATMEGA324P ###########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA324P_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega324p" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA324P_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA328P ###########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/AnalogDigitalConverter.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/ExternalInterruptController.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/I2CMaster.cpp          
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/InterruptController.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER0.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER1.cpp
    ${SPECTRE_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER2.cpp
  )
  
  if(${MCU_TYPE} STREQUAL "atmega328p" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA32U4 ###########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA32U4_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_32U4_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega32u4" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA32U4_SRCS})  
  endif()

  ########################################################################
  # ATMEGA640 ############################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega640" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_SRCS})
  endif()

  ########################################################################
  # ATMEGA644P ###########################################################
  ########################################################################

  set(SPECTRE_LIBRARY_HAL_AVR_ATMEGA644P_SRCS
    ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega644p" OR {MCU_TYPE} STREQUAL "host")
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA644P_SRCS})  
  endif()

##########################################################################

endif()

##########################################################################

if(${MCU_ARCH} STREQUAL "host")
  
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATxxxx_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN128_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN32_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_AT90CAN64_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA1280_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA1284P_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA164P_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA16U4_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA2560_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA324P_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA328P_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA32U4_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA640_SRCS})
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} ${SPECTRE_LIBRARY_HAL_AVR_ATMEGA644P_SRCS})

endif()

##########################################################################
