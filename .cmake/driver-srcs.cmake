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

if(${DRIVER_SENSOR_AS5600} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/sensor/AS5600.cpp)
endif()

if(${DRIVER_SENSOR_BMG160} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/sensor/BMG160.cpp)
endif()

if(${DRIVER_SENSOR_INA220} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/sensor/INA220.cpp)
endif()

if(${DRIVER_SENSOR_L3GD20} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/sensor/L3GD20.cpp)
endif()

if(${DRIVER_SENSOR_LIS2DSH} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/sensor/LIS2DSH.cpp)
endif()

if(${DRIVER_SENSOR_LIS3MDL} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/sensor/LIS3MDL.cpp)
endif()

##########################################################################

