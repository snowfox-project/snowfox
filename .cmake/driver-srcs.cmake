##########################################################################
# DRIVER #################################################################
##########################################################################

if(${DRIVER_HAPTIC_DRV2605} STREQUAL "yes")
  
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} src/driver/haptic/DRV2605.cpp)
  
endif()

##########################################################################
