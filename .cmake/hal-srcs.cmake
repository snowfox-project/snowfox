##########################################################################
# HAL ####################################################################
##########################################################################

##########################################################################
# AVR ####################################################################
##########################################################################

if(${MCU_ARCH} STREQUAL "avr" OR ${MCU_ARCH} STREQUAL "host")

  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_PATH src/hal/avr)

  ########################################################################
  # common/AT90CAN32_64_128 ##############################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/ExternalInterruptController.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/InterruptController.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER0.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER1.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER2.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/AT90CAN32_64_128/TIMER3.cpp
  )

  ########################################################################
  # common/ATMEGA164P_324P_644P_1284P ####################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA164P_324P_644P_1284P/ExternalInterruptController.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA164P_324P_644P_1284P/InterruptController.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA164P_324P_644P_1284P/TIMER0.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA164P_324P_644P_1284P/TIMER2.cpp
  )

  ########################################################################
  # common/ATMEGA16U4_32U4 ###############################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA16U4_32U4_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA16U4_32U4/ExternalInterruptController.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA16U4_32U4/InterruptController.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA16U4_32U4/TIMER0.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA16U4_32U4/TIMER1.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA16U4_32U4/TIMER3.cpp
  )

  ########################################################################
  # common/ATMEGA3209_4809 ###############################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA3209_4809_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA3209_4809/InterruptController.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA3209_4809/TIMERAx.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA3209_4809/TIMERBx.cpp
  )

  ########################################################################
  # common/ATMEGA640_1280_2560 ###########################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/ExternalInterruptController.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/InterruptController.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER0.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER1.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER2.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER3.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER4.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATMEGA640_1280_2560/TIMER5.cpp
  )

  ########################################################################
  # common/ATxxxx ########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATxxxx_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/util/ExternalInterruptUtil.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/util/UartUtil.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/Delay.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/CriticalSection.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalInOutPort.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalInPin.cpp    
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalInPort.cpp   
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalOutPin.cpp   
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/DigitalOutPort.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/EEPROM.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/Flash.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/I2cMaster_onI2cTransferCompleteCallback.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/I2cMaster.cpp       
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/I2cMasterLowLevel.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/SpiMaster_onSerialTransferCompleteCallback.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/SpiMaster.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/Stack.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/UART0.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/UART1.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/UART2.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/common/ATxxxx/UART3.cpp
  )
  
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATxxxx_SRCS})

  ########################################################################
  # AT90CAN128 ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_AT90CAN128_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "at90can128" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_AT90CAN128_SRCS})  
  endif()

  ########################################################################
  # AT90CAN32  ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_AT90CAN32_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "at90can32" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_AT90CAN32_SRCS})  
  endif()

  ########################################################################
  # AT90CAN64  ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_AT90CAN64_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_AT90CAN32_64_128_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "at90can64" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_AT90CAN64_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA1280 ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA1280_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega1280" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA1280_SRCS})
  endif()
  
  ########################################################################
  # ATMEGA1284P ##########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA1284P_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega1284p" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA1284P_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA164P ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA164P_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )

  if(${MCU_TYPE} STREQUAL "atmega164p" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA164P_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA16U4 ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA16U4_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA16U4_32U4_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega16u4" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA16U4_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA2560 ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA2560_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega2560" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA2560_SRCS})
  endif()

  ########################################################################
  # ATMEGA3209 ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA3209_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA3209_4809_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega3209" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA3209_SRCS})
  endif()

  ########################################################################
  # ATMEGA324P ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA324P_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega324p" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA324P_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA328P ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA328P_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/AnalogDigitalConverter.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/ExternalInterruptController.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/InterruptController.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER0.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER1.cpp
    ${SNOWFOX_LIBRARY_HAL_AVR_PATH}/ATMEGA328P/TIMER2.cpp
  )
  
  if(${MCU_TYPE} STREQUAL "atmega328p" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA328P_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA32U4 ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA32U4_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA16U4_32U4_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega32u4" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA32U4_SRCS})  
  endif()
  
  ########################################################################
  # ATMEGA3209 ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA4809_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA3209_4809_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega4809" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA4809_SRCS})
  endif()

  ########################################################################
  # ATMEGA640 ############################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA640_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA640_1280_2560_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega640" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA640_SRCS})
  endif()

  ########################################################################
  # ATMEGA644P ###########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_AVR_ATMEGA644P_SRCS
    ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega644p" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA644P_SRCS})  
  endif()

##########################################################################

endif()

##########################################################################
# AVR ####################################################################
##########################################################################

if(${MCU_ARCH} STREQUAL "riscv64" OR ${MCU_ARCH} STREQUAL "host")

  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_RISCV_PATH src/hal/riscv64)

  ########################################################################

  ########################################################################
  # SIFIVE FE310 #########################################################
  ########################################################################

  set(SNOWFOX_LIBRARY_HAL_RISCV64_FE310_SRCS
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/util/ClockUtil.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/util/InterruptUtil.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/util/UartUtil.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/CriticalSection.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/Clock.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/Delay.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/DigitalInPin.cpp  
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/DigitalOutPin.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/Spi1Master.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/Spi2Master.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/SpiMasterBase.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/UART0.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/UART1.cpp
    ${SNOWFOX_LIBRARY_HAL_RISCV_PATH}/FE310/UARTx.cpp
  )

  if(${MCU_TYPE} STREQUAL "fe310" OR {MCU_TYPE} STREQUAL "host")
    set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_RISCV64_FE310_SRCS})  
  endif()

  ########################################################################

endif()

##########################################################################

if(${MCU_ARCH} STREQUAL "host")
  
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATxxxx_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_AT90CAN128_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_AT90CAN32_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_AT90CAN64_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA1280_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA1284P_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA164P_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA16U4_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA2560_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA3209_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA324P_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA328P_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA32U4_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA4809_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA640_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_AVR_ATMEGA644P_SRCS})
  set(SNOWFOX_LIBRARY_HAL_SRCS ${SNOWFOX_LIBRARY_HAL_SRCS} ${SNOWFOX_LIBRARY_HAL_RISCV64_FE310_SRCS})

endif()

##########################################################################
