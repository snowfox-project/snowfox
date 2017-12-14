##########################################################################

SET(CMAKE_C_COMPILER avr-gcc)
SET(CMAKE_CXX_COMPILER avr-g++)

SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-Wl,--relax,--gc-sections")

##########################################################################
