##########################################################################

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

##########################################################################

set(SNOWFOX_HOST_GCC_CMAKE_C_FLAGS     "")
set(SNOWFOX_HOST_GCC_CMAKE_CXX_FLAGS   "--coverage")
set(SNOWFOX_HOST_GCC_CMAKE_C_CXX_FLAGS "")

##########################################################################

set(SNOWFOX_CMAKE_C_FLAGS   "${SNOWFOX_CMAKE_C_FLAGS}   ${SNOWFOX_HOST_GCC_CMAKE_C_FLAGS}   ${SNOWFOX_HOST_GCC_CMAKE_C_CXX_FLAGS}")
set(SNOWFOX_CMAKE_CXX_FLAGS "${SNOWFOX_CMAKE_CXX_FLAGS} ${SNOWFOX_HOST_GCC_CMAKE_CXX_FLAGS} ${SNOWFOX_HOST_GCC_CMAKE_C_CXX_FLAGS}")
 
##########################################################################