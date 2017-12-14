##########################################################################
# HAL ####################################################################
##########################################################################

if(${MCU_ARCH} STREQUAL "avr")

  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} src/hal/avr/ATxxxx/DelayService.cpp )
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} src/hal/avr/ATxxxx/DigitalInPin.cpp )
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} src/hal/avr/ATxxxx/DigitalOutPin.cpp)
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} src/hal/avr/ATxxxx/I2CMaster.cpp    )
  set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} src/hal/avr/cxx/cxx.cpp             )
  
  if(${MCU_TYPE} STREQUAL "atmega328p")
  
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} src/hal/avr/ATMEGA328P/I2CMaster.cpp)
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} src/hal/avr/ATMEGA328P/InterruptController.cpp)
    set(SPECTRE_LIBRARY_HAL_SRCS ${SPECTRE_LIBRARY_HAL_SRCS} src/hal/avr/ATMEGA328P/UART0.cpp)
    
  endif()

endif()

##########################################################################

