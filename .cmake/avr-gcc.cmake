##########################################################################

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

##########################################################################

set(SNOWFOX_CMAKE_CXX_FLAGS "${SNOWFOX_CMAKE_CXX_FLAGS} -mmcu=${MCU_TYPE} -fno-exceptions -Wno-deprecated-copy")
 
##########################################################################

set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-Wl,--relax,--gc-sections")

##########################################################################

add_subdirectory(external/avr-stl)
include_directories(external/avr-stl/include) # Should not be necessary but somehow is.

##########################################################################
