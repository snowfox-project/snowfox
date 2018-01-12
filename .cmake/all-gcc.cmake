##########################################################################

add_definitions(-DMCU_ARCH_${MCU_ARCH})
add_definitions(-DMCU_TYPE_${MCU_TYPE})
add_definitions(-DF_CPU=${MCU_SPEED})
add_definitions(-std=c++11)
 
##########################################################################
