##########################################################################

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

##########################################################################

set(SNOWFOX_AVR_GCC_CMAKE_C_FLAGS     "")
set(SNOWFOX_AVR_GCC_CMAKE_CXX_FLAGS   "")
set(SNOWFOX_AVR_GCC_CMAKE_C_CXX_FLAGS "-mmcu=${MCU_TYPE} -Os -Wall -pedantic -pedantic-errors -funsigned-char -funsigned-bitfields -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions")

##########################################################################

set(SNOWFOX_CMAKE_C_FLAGS   "${SNOWFOX_CMAKE_C_FLAGS}   ${SNOWFOX_AVR_GCC_CMAKE_C_FLAGS}   ${SNOWFOX_AVR_GCC_CMAKE_C_CXX_FLAGS}")
set(SNOWFOX_CMAKE_CXX_FLAGS "${SNOWFOX_CMAKE_CXX_FLAGS} ${SNOWFOX_AVR_GCC_CMAKE_CXX_FLAGS} ${SNOWFOX_AVR_GCC_CMAKE_C_CXX_FLAGS}")
 
##########################################################################

set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-Wl,--relax,--gc-sections")

##########################################################################
