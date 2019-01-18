##########################################################################
# BLOX ###################################################################
##########################################################################

##########################################################################
# DRIVER #################################################################
##########################################################################

##########################################################################
# HAPTIC #################################################################
##########################################################################

set(SNOWFOX_LIBRARY_BLOX_DRIVER_HAPTIC_PATH src/blox/driver/haptic)

##########################################################################

set(SNOWFOX_LIBRARY_BLOX_DRIVER_HAPTIC_SRCS 
  ${SNOWFOX_LIBRARY_BLOX_DRIVER_HAPTIC_PATH}/DRV2605.cpp
)

##########################################################################

set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_DRIVER_HAPTIC_SRCS})

##########################################################################
# LORA ###################################################################
##########################################################################

set(SNOWFOX_LIBRARY_BLOX_DRIVER_LORA_PATH src/blox/driver/lora)

##########################################################################

set(SNOWFOX_LIBRARY_BLOX_DRIVER_LORA_SRCS 
  ${SNOWFOX_LIBRARY_BLOX_DRIVER_LORA_PATH}/RFM9x.cpp
)

##########################################################################

set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_DRIVER_LORA_SRCS})

##########################################################################
# SERIAL #################################################################
##########################################################################

set(SNOWFOX_LIBRARY_BLOX_DRIVER_SERIAL_PATH src/blox/driver/serial)

set(SNOWFOX_LIBRARY_BLOX_DRIVER_SERIAL_SRCS 
  ${SNOWFOX_LIBRARY_BLOX_DRIVER_SERIAL_PATH}/SerialUart.cpp
)

##########################################################################

set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_DRIVER_SERIAL_SRCS})

##########################################################################
# HAL ####################################################################
##########################################################################

##########################################################################
# AVR ####################################################################
##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

##########################################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_PATH src/blox/hal/avr)

  ########################################################################
  # common/AT90CAN32_64_128 ##############################################
  ########################################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_AT90CAN32_64_128_SRCS
    # ... 
  )
  
  ########################################################################
  # common/ATMEGA164P_324P_644P_1284P ####################################
  ########################################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS
    # ...
  )

  ########################################################################
  # common/ATMEGA16U4_32U4 ###############################################
  ########################################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA16U4_32U4_SRCS
    # ...
  )
  
  ########################################################################
  # common/ATMEGA640_1280_2560 ###########################################
  ########################################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA640_1280_2560_SRCS
    # ...
  )
  
  # AT90CAN128 ###########################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_AT90CAN128_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_AT90CAN32_64_128_SRCS}
  )

  if(${MCU_TYPE} STREQUAL "at90can128")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_AT90CAN128_SRCS})  
  endif()
  
  # AT90CAN32 ############################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_AT90CAN32_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_AT90CAN32_64_128_SRCS}
  )

  if(${MCU_TYPE} STREQUAL "at90can32")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_AT90CAN32_SRCS})  
  endif()
  
  # AT90CAN64 ############################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_AT90CAN64_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_AT90CAN32_64_128_SRCS}
  )

  if(${MCU_TYPE} STREQUAL "at90can64")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_AT90CAN64_SRCS})  
  endif()
  
  # ATMEGA1280 ###########################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA1280_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA640_1280_2560_SRCS}
  )

  if(${MCU_TYPE} STREQUAL "atmega1280")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA1280_SRCS})  
  endif()

  # ATMEGA1284P ##########################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA1284P_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )

  if(${MCU_TYPE} STREQUAL "atmega1284p")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA1284P_SRCS})  
  endif()

  # ATMEGA164P ###########################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA164P_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega164p")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA164P_SRCS})  
  endif()
  
  # ATMEGA16U4 ###########################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA16U4_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA16U4_32U4_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega16u4")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA16U4_SRCS})  
  endif()
  
  # ATMEGA2560 ###########################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA2560_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA640_1280_2560_SRCS}
  )

  if(${MCU_TYPE} STREQUAL "atmega2560")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA2560_SRCS})  
  endif()
  
  # ATMEGA324P ###########################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA324P_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega324p")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA324P_SRCS})  
  endif()

  # ATMEGA328P ###########################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA328P_SRCS
    # ...
  )
  
  if(${MCU_TYPE} STREQUAL "atmega328p")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA328P_SRCS})  
  endif()
  
  # ATMEGA32U4 ###########################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA32U4_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA16U4_32U4_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega32u4")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA32U4_SRCS})  
  endif()
  
  # ATMEGA640 ############################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA640_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA640_1280_2560_SRCS}
  )

  if(${MCU_TYPE} STREQUAL "atmega640")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA640_SRCS})  
  endif()
  
  # ATMEGA644P ###########################################################

  set(SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA644P_SRCS 
    ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA164P_324P_644P_1284P_SRCS}
  )
  
  if(${MCU_TYPE} STREQUAL "atmega644p")
    set(SNOWFOX_LIBRARY_BLOX_SRCS ${SNOWFOX_LIBRARY_BLOX_SRCS} ${SNOWFOX_LIBRARY_BLOX_HAL_AVR_ATMEGA644P_SRCS})  
  endif()
  
##########################################################################

endif()

##########################################################################
