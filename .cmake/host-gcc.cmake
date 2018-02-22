##########################################################################

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

##########################################################################

set(SPECTRE_HOST_GCC_CMAKE_C_FLAGS     "")
set(SPECTRE_HOST_GCC_CMAKE_CXX_FLAGS   "--coverage")
set(SPECTRE_HOST_GCC_CMAKE_C_CXX_FLAGS "")

##########################################################################

set(SPECTRE_CMAKE_C_FLAGS   "${SPECTRE_CMAKE_C_FLAGS}   ${SPECTRE_HOST_GCC_CMAKE_C_FLAGS}   ${SPECTRE_HOST_GCC_CMAKE_C_CXX_FLAGS}")
set(SPECTRE_CMAKE_CXX_FLAGS "${SPECTRE_CMAKE_CXX_FLAGS} ${SPECTRE_HOST_GCC_CMAKE_CXX_FLAGS} ${SPECTRE_HOST_GCC_CMAKE_C_CXX_FLAGS}")
 
##########################################################################