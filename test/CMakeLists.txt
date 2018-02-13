##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

include_directories(include)
include_directories(external/catch/current/include)

##########################################################################

add_subdirectory(src/hal/avr)
add_subdirectory(src/memory)

##########################################################################
