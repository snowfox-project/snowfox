##########################################################################

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

##########################################################################

set(SPECTRE_AVR_GCC_CMAKE_C_FLAGS     "")
set(SPECTRE_AVR_GCC_CMAKE_CXX_FLAGS   "")
set(SPECTRE_AVR_GCC_CMAKE_C_CXX_FLAGS "-mmcu=${MCU_TYPE} -Os -Wall -pedantic -pedantic-errors -funsigned-char -funsigned-bitfields -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions")

##########################################################################

set(SPECTRE_CMAKE_C_FLAGS   "${SPECTRE_CMAKE_C_FLAGS}   ${SPECTRE_AVR_GCC_CMAKE_C_FLAGS}   ${SPECTRE_AVR_GCC_CMAKE_C_CXX_FLAGS}")
set(SPECTRE_CMAKE_CXX_FLAGS "${SPECTRE_CMAKE_CXX_FLAGS} ${SPECTRE_AVR_GCC_CMAKE_CXX_FLAGS} ${SPECTRE_AVR_GCC_CMAKE_C_CXX_FLAGS}")
 
##########################################################################

set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-Wl,--relax,--gc-sections")

##########################################################################
