##########################################################################

include_directories(${SPECTRE_ROOT_PATH}/include)
cmake_policy(SET CMP0015 NEW)
link_directories(${SPECTRE_ROOT_PATH}/build/lib)

##########################################################################

set(SPECTRE_CMAKE_C_FLAGS   "")
set(SPECTRE_CMAKE_CXX_FLAGS "")

##########################################################################

include(${SPECTRE_ROOT_PATH}/.cmake/avr-gcc.cmake)
include(${SPECTRE_ROOT_PATH}/.cmake/all-gcc.cmake)

##########################################################################

set(CMAKE_C_FLAGS   ${CMAKE_C_FLAGS}   ${SPECTRE_CMAKE_C_FLAGS}  )
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${SPECTRE_CMAKE_CXX_FLAGS})

##########################################################################

