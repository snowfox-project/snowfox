##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

project(spectre)

##########################################################################

include_directories(include)

##########################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)

##########################################################################
# CONFIGURATION ##########################################################
##########################################################################

include(config.cmake)

##########################################################################

if(${MCU_ARCH} STREQUAL "avr")
  include(.cmake/avr-gcc.cmake)
endif()

##########################################################################
# HAL ####################################################################
##########################################################################

set(SPECTRE_LIBRARY_HAL_SRCS "")

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
# DRIVER #################################################################
##########################################################################

set(SPECTRE_LIBRARY_DRIVER_SRCS "")

##########################################################################

if(${DRIVER_HAPTIC_DRV2605} STREQUAL "yes")
  
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/haptic/DRV2605.cpp)
  
endif()

##########################################################################
# LIBRARIES ##############################################################
##########################################################################

set(SPECTRE_LIBRARY_SRCS
  ${SPECTRE_LIBRARY_HAL_SRCS}
  ${SPECTRE_LIBRARY_DRIVER}
)

##########################################################################

set(SPECTRY_LIBRARY_NAME_MCU ${PROJECT_NAME}-${MCU_TYPE})

add_library(
  ${SPECTRY_LIBRARY_NAME_MCU} 
  STATIC
  ${SPECTRE_LIBRARY_SRCS}
)

set_target_properties(
  ${SPECTRY_LIBRARY_NAME_MCU}
  
  PROPERTIES
    COMPILE_FLAGS "-mmcu=${MCU_TYPE} -DF_CPU=${MCU_SPEED} -Os -Wall -pedantic -pedantic-errors -funsigned-char -funsigned-bitfields -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -std=c++11"
    OUTPUT_NAME   "${SPECTRE_LIBRARY_NAME}"
)

##########################################################################
# EXAMPLES ###############################################################
##########################################################################

add_subdirectory(examples)

##########################################################################
