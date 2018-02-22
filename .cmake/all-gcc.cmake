##########################################################################

add_definitions(-DMCU_ARCH_${MCU_ARCH})
add_definitions(-DMCU_TYPE_${MCU_TYPE})
add_definitions(-DF_CPU=${MCU_SPEED})

##########################################################################

set(SPECTRE_ALL_GCC_CMAKE_C_FLAGS     "")
set(SPECTRE_ALL_GCC_CMAKE_CXX_FLAGS   "-std=c++11")
set(SPECTRE_ALL_GCC_CMAKE_C_CXX_FLAGS "")

##########################################################################

set(SPECTRE_CMAKE_C_FLAGS   "${SPECTRE_CMAKE_C_FLAGS}   ${SPECTRE_ALL_GCC_CMAKE_C_FLAGS}   ${SPECTRE_ALL_GCC_CMAKE_C_CXX_FLAGS}")
set(SPECTRE_CMAKE_CXX_FLAGS "${SPECTRE_CMAKE_CXX_FLAGS} ${SPECTRE_ALL_GCC_CMAKE_CXX_FLAGS} ${SPECTRE_ALL_GCC_CMAKE_C_CXX_FLAGS}")
 
##########################################################################
