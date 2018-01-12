##########################################################################

SET(CMAKE_C_COMPILER avr-gcc)
SET(CMAKE_CXX_COMPILER avr-g++)

##########################################################################

add_definitions(-mmcu=${MCU_TYPE})
add_definitions(-Os)
add_definitions(-Wall)
add_definitions(-pedantic)
add_definitions(-pedantic-errors)
add_definitions(-funsigned-char)
add_definitions(-funsigned-bitfields)
add_definitions(-fshort-enums)
add_definitions(-ffunction-sections)
add_definitions(-fdata-sections)
add_definitions(-fno-exceptions)

##########################################################################

SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-Wl,--relax,--gc-sections")

##########################################################################
