##########################################################################

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

##########################################################################

set(SNOWFOX_CMAKE_CXX_FLAGS "${SNOWFOX_CMAKE_CXX_FLAGS} --target=avr -nostdlibinc -isystem /opt/avr/avr-libc/avr/include -mmcu=${MCU_TYPE} -fno-exceptions")
 
##########################################################################

set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-Wl,--relax,--gc-sections")

##########################################################################
