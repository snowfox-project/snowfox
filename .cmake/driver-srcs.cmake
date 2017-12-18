##########################################################################
# DRIVER #################################################################
##########################################################################

if(${DRIVER_HAPTIC_DRV2605} STREQUAL "yes")
  
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/haptic/DRV2605.cpp)
  
endif()

##########################################################################

if(${DRIVER_SENSOR_AD7151} STREQUAL "yes")
  
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/sensor/AD7151.cpp)
  
endif()

if(${DRIVER_SENSOR_LIS3MDL} STREQUAL "yes")
  
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/sensor/LIS3MDL.cpp)
  
endif()

##########################################################################

