##########################################################################
# DRIVER #################################################################
##########################################################################

set(DRIVER_HAPTIC_SRC_PATH src/driver/haptic)

if(${DRIVER_HAPTIC_DRV2605} STREQUAL "yes")
  set(DRIVER_HAPTIC_DRV2605_SRCS
    ${DRIVER_HAPTIC_SRC_PATH}/DRV2605/DRV2605_IO_I2C.cpp
    ${DRIVER_HAPTIC_SRC_PATH}/DRV2605/DRV2605.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_HAPTIC_DRV2605_SRCS})
endif()

##########################################################################

if(${DRIVER_HAPTIC_PCA9547} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/ioexpander/PCA9547.cpp)
endif()

##########################################################################

if(${DRIVER_HAPTIC_AT45DBX} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/memory/AT45DBx.cpp)
endif()

if(${DRIVER_HAPTIC_PCF8570} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/memory/PCF8570.cpp)
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

if(${DRIVER_SENSOR_LIS3DSH} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/sensor/LIS3DSH.cpp)
endif()

if(${DRIVER_SENSOR_LIS3MDL} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/sensor/LIS3MDL.cpp)
endif()

if(${DRIVER_SENSOR_TPA81} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/sensor/TPA81.cpp)
endif()

##########################################################################

