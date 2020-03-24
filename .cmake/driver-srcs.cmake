##########################################################################
# DRIVER #################################################################
##########################################################################

##########################################################################
# CAN ####################################################################
##########################################################################

# MCP2515 ################################################################

set(DRIVER_CAN_SRC_PATH src/driver/can)

if(${DRIVER_CAN_MCP2515} STREQUAL "yes")
  set(DRIVER_CAN_MCP2515_SRCS
    ${DRIVER_CAN_SRC_PATH}/MCP2515/events/MCP2515_EventCallback.cpp
    ${DRIVER_CAN_SRC_PATH}/MCP2515/events/MCP2515_onMessageError.cpp
  	${DRIVER_CAN_SRC_PATH}/MCP2515/events/MCP2515_onReceiveBufferFull.cpp
  	${DRIVER_CAN_SRC_PATH}/MCP2515/events/MCP2515_onTransmitBufferEmpty.cpp
  	${DRIVER_CAN_SRC_PATH}/MCP2515/events/MCP2515_onWakeup.cpp
  
    ${DRIVER_CAN_SRC_PATH}/MCP2515/interface/control/MCP2515_EventControl.cpp
  
    ${DRIVER_CAN_SRC_PATH}/MCP2515/MCP2515_CanConfiguration.cpp
    ${DRIVER_CAN_SRC_PATH}/MCP2515/MCP2515_CanControl.cpp
    ${DRIVER_CAN_SRC_PATH}/MCP2515/MCP2515_Configuration.cpp
    ${DRIVER_CAN_SRC_PATH}/MCP2515/MCP2515_Control.cpp
    ${DRIVER_CAN_SRC_PATH}/MCP2515/MCP2515_Debug.cpp
  	${DRIVER_CAN_SRC_PATH}/MCP2515/MCP2515_IoSpi.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_CAN_MCP2515_SRCS})
endif()

# CAN ####################################################################

if(${DRIVER_CAN_MCP2515} STREQUAL "yes")
  set(DRIVER_CAN_SRCS
    ${DRIVER_CAN_SRC_PATH}/Can.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_CAN_SRCS})
endif()

##########################################################################
# GLCD ###################################################################
##########################################################################

set(DRIVER_GLCD_SRC_PATH src/driver/glcd)

# RA6963 #################################################################

if(${DRIVER_GLCD_RA6963} STREQUAL "yes")
  set(DRIVER_GLCD_RA6963_SRCS
    ${DRIVER_GLCD_SRC_PATH}/RA6963/RA6963_Control.cpp
  	${DRIVER_GLCD_SRC_PATH}/RA6963/RA6963_Data.cpp
    ${DRIVER_GLCD_SRC_PATH}/RA6963/RA6963_IoGpio8Bit.cpp
    ${DRIVER_GLCD_SRC_PATH}/RA6963/RA6963.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_GLCD_RA6963_SRCS})
endif()

##########################################################################
# HAPTIC #################################################################
##########################################################################

set(DRIVER_HAPTIC_SRC_PATH src/driver/haptic)

# HAPTIC BASE ############################################################

set(DRIVER_HAPTIC_BASE_SRCS
  ${DRIVER_HAPTIC_SRC_PATH}/HapticActuatorDriver.cpp
)
set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_HAPTIC_BASE_SRCS})

# DRV2650 ################################################################

if(${DRIVER_HAPTIC_DRV2605} STREQUAL "yes")
  set(DRIVER_HAPTIC_DRV2605_SRCS
    ${DRIVER_HAPTIC_SRC_PATH}/DRV2605/DRV2605_Control.cpp
    ${DRIVER_HAPTIC_SRC_PATH}/DRV2605/DRV2605_Debug.cpp
    ${DRIVER_HAPTIC_SRC_PATH}/DRV2605/DRV2605_IoI2C.cpp
    ${DRIVER_HAPTIC_SRC_PATH}/DRV2605/DRV2605.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_HAPTIC_DRV2605_SRCS})
endif()

##########################################################################
# IOEXPANDER #############################################################
##########################################################################

set(DRIVER_IOEXPANDER_SRC_PATH src/driver/ioexpander)

# MAX6921 ###############################################################

if(${DRIVER_IOEXPANDER_MAX6921} STREQUAL "yes")
  set(DRIVER_IOEXPANDER_MAX6921_SRCS
    ${DRIVER_IOEXPANDER_SRC_PATH}/MAX6921/MAX6921_IoSpi.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/MAX6921/MAX6921_Control.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/MAX6921/MAX6921.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_IOEXPANDER_MAX6921_SRCS})
endif()

# MCP23017 ###############################################################

if(${DRIVER_IOEXPANDER_MCP23017} STREQUAL "yes")
  set(DRIVER_IOEXPANDER_MCP23017_SRCS
    ${DRIVER_IOEXPANDER_SRC_PATH}/MCP23017/interface/MCP23017_Io.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/MCP23017/interface/MCP23017_Types.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/MCP23017/MCP23017_Configuration.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/MCP23017/MCP23017_Control.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/MCP23017/MCP23017_Debug.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/MCP23017/MCP23017_IoI2c.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/MCP23017/MCP23017.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_IOEXPANDER_MCP23017_SRCS})
endif()

# PCA9547 ################################################################

if(${DRIVER_IOEXPANDER_PCA9547} STREQUAL "yes")
  set(DRIVER_IOEXPANDER_PCA9547_SRCS
    ${DRIVER_IOEXPANDER_SRC_PATH}/PCA9547/PCA9547_Control.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/PCA9547/PCA9547_Debug.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/PCA9547/PCA9547_IoI2c.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/PCA9547/PCA9547.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_IOEXPANDER_PCA9547_SRCS})
endif()

##########################################################################
# LORA ###################################################################
##########################################################################

set(DRIVER_LORA_SRC_PATH src/driver/lora)

# RFM9x ##################################################################

if(${DRIVER_LORA_RFM9x} STREQUAL "yes")
  set(DRIVER_LORA_RFM9x_SRCS
    ${DRIVER_LORA_SRC_PATH}/RFM9x/events/DIO0/RFM9x_Dio0EventCallback.cpp
    ${DRIVER_LORA_SRC_PATH}/RFM9x/events/DIO0/RFM9x_onCadDoneCallback.cpp
    ${DRIVER_LORA_SRC_PATH}/RFM9x/events/DIO0/RFM9x_onRxDoneCallback.cpp
    ${DRIVER_LORA_SRC_PATH}/RFM9x/events/DIO0/RFM9x_onTxDoneCallback.cpp
    
    ${DRIVER_LORA_SRC_PATH}/RFM9x/events/DIO1/RFM9x_Dio1EventCallback.cpp
    ${DRIVER_LORA_SRC_PATH}/RFM9x/events/DIO1/RFM9x_onCadDetectedCallback.cpp
    ${DRIVER_LORA_SRC_PATH}/RFM9x/events/DIO1/RFM9x_onFhssChangeChannelCallback.cpp
    ${DRIVER_LORA_SRC_PATH}/RFM9x/events/DIO1/RFM9x_onRxTimeoutCallback.cpp
    
    ${DRIVER_LORA_SRC_PATH}/RFM9x/interface/RFM9x_EventControl.cpp
    
    ${DRIVER_LORA_SRC_PATH}/RFM9x/RFM9x_Configuration.cpp
    ${DRIVER_LORA_SRC_PATH}/RFM9x/RFM9x_Control.cpp
    ${DRIVER_LORA_SRC_PATH}/RFM9x/RFM9x_Debug.cpp
    ${DRIVER_LORA_SRC_PATH}/RFM9x/RFM9x_IoSpi.cpp
    ${DRIVER_LORA_SRC_PATH}/RFM9x/RFM9x_Status.cpp
    ${DRIVER_LORA_SRC_PATH}/RFM9x/RFM9x.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_LORA_RFM9x_SRCS})
endif()

##########################################################################
# MEMORY #################################################################
##########################################################################

set(DRIVER_MEMORY_SRC_PATH src/driver/memory)

# MEMORY BASE ############################################################

set(DRIVER_MEMORY_BASE_SRCS
  ${DRIVER_MEMORY_SRC_PATH}/NorFlashDriver.cpp
)
set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_MEMORY_BASE_SRCS})

# AT45DBx ################################################################

if(${DRIVER_MEMORY_AT45DBX} STREQUAL "yes")
  set(DRIVER_MEMORY_AT45DBX_SRCS
    ${DRIVER_MEMORY_SRC_PATH}/AT45DBx/AT45DBx_Configuration.cpp
    ${DRIVER_MEMORY_SRC_PATH}/AT45DBx/AT45DBx_Control.cpp
    ${DRIVER_MEMORY_SRC_PATH}/AT45DBx/AT45DBx_IoSpi.cpp
    ${DRIVER_MEMORY_SRC_PATH}/AT45DBx/AT45DBx_Util.cpp
    ${DRIVER_MEMORY_SRC_PATH}/AT45DBx/AT45DBx.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_MEMORY_AT45DBX_SRCS})  
endif()

# N25Q256A ###############################################################

if(${DRIVER_MEMORY_N25Q256A} STREQUAL "yes")
  set(DRIVER_MEMORY_N25Q256A_SRCS
    ${DRIVER_MEMORY_SRC_PATH}/N25Q256A/interface/N25Q256A_Io.cpp
    ${DRIVER_MEMORY_SRC_PATH}/N25Q256A/N25Q256A_Configuration.cpp
    ${DRIVER_MEMORY_SRC_PATH}/N25Q256A/N25Q256A_Control.cpp
    ${DRIVER_MEMORY_SRC_PATH}/N25Q256A/N25Q256A_Debug.cpp
    ${DRIVER_MEMORY_SRC_PATH}/N25Q256A/N25Q256A_IoSpi.cpp
    ${DRIVER_MEMORY_SRC_PATH}/N25Q256A/N25Q256A_Status.cpp
    ${DRIVER_MEMORY_SRC_PATH}/N25Q256A/N25Q256A.cpp
    ${DRIVER_MEMORY_SRC_PATH}/NorFlashDriver.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_MEMORY_N25Q256A_SRCS})
endif()

# PCF8570 ################################################################

if(${DRIVER_MEMORY_PCF8570} STREQUAL "yes")
  set(DRIVER_MEMORY_PCF8570_SRCS
  ${DRIVER_MEMORY_SRC_PATH}/PCF8570/PCF8570_Control.cpp
	${DRIVER_MEMORY_SRC_PATH}/PCF8570/PCF8570_IoI2c.cpp
	${DRIVER_MEMORY_SRC_PATH}/PCF8570/PCF8570.cpp        
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_MEMORY_PCF8570_SRCS})
endif()

# UTIL ###################################################################

set(DRIVER_MEMORY_UTIL_SRCS
  ${DRIVER_MEMORY_SRC_PATH}/util/jedec/Jedec.cpp
  ${DRIVER_MEMORY_SRC_PATH}/util/jedec/JedecCode.cpp
)

set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_MEMORY_UTIL_SRCS})

##########################################################################
# SENSOR #################################################################
##########################################################################

set(DRIVER_SENSOR_SRC_PATH src/driver/sensor)

# AD7151 #################################################################

if(${DRIVER_SENSOR_AD7151} STREQUAL "yes")
  set(DRIVER_SENSOR_AD7151_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/AD7151/AD7151_Control.cpp
    ${DRIVER_SENSOR_SRC_PATH}/AD7151/AD7151_Debug.cpp
    ${DRIVER_SENSOR_SRC_PATH}/AD7151/AD7151_IoI2c.cpp
    ${DRIVER_SENSOR_SRC_PATH}/AD7151/AD7151.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_SENSOR_AD7151_SRCS})
endif()

# AS5600 #################################################################

if(${DRIVER_SENSOR_AS5600} STREQUAL "yes")
  set(DRIVER_SENSOR_AS5600_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/AS5600/AS5600_Control.cpp
    ${DRIVER_SENSOR_SRC_PATH}/AS5600/AS5600_Debug.cpp
    ${DRIVER_SENSOR_SRC_PATH}/AS5600/AS5600_IoI2c.cpp
    ${DRIVER_SENSOR_SRC_PATH}/AS5600/AS5600.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_SENSOR_AS5600_SRCS})
endif()

# BMG160 #################################################################

if(${DRIVER_SENSOR_BMG160} STREQUAL "yes")
  set(DRIVER_SENSOR_BMG160_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/BMG160/BMG160_Control.cpp
    ${DRIVER_SENSOR_SRC_PATH}/BMG160/BMG160_Debug.cpp
    ${DRIVER_SENSOR_SRC_PATH}/BMG160/BMG160_IoI2c.cpp
    ${DRIVER_SENSOR_SRC_PATH}/BMG160/BMG160.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_SENSOR_BMG160_SRCS})
endif()

# BMP388 #################################################################

if(${DRIVER_SENSOR_BMP388} STREQUAL "yes")
  set(DRIVER_SENSOR_BMP388_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/BMP388/interface/BMP388_Io.cpp
    ${DRIVER_SENSOR_SRC_PATH}/BMP388/BMP388_IoSpi.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_SENSOR_BMP388_SRCS})
endif()

# INA220 #################################################################

if(${DRIVER_SENSOR_INA220} STREQUAL "yes")
  set(DRIVER_SENSOR_INA220_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/INA220/INA220_Control.cpp
    ${DRIVER_SENSOR_SRC_PATH}/INA220/INA220_Debug.cpp
    ${DRIVER_SENSOR_SRC_PATH}/INA220/INA220_IoI2c.cpp
    ${DRIVER_SENSOR_SRC_PATH}/INA220/INA220.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_SENSOR_INA220_SRCS})
endif()

# L3GD20 #################################################################

if(${DRIVER_SENSOR_L3GD20} STREQUAL "yes")
  set(DRIVER_SENSOR_L3GD20_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/L3GD20/L3GD20_Control.cpp
    ${DRIVER_SENSOR_SRC_PATH}/L3GD20/L3GD20_Debug.cpp
    ${DRIVER_SENSOR_SRC_PATH}/L3GD20/L3GD20_IoI2c.cpp
    ${DRIVER_SENSOR_SRC_PATH}/L3GD20/L3GD20.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_SENSOR_L3GD20_SRCS})
endif()

# LIS2DSH ################################################################

if(${DRIVER_SENSOR_LIS2DSH} STREQUAL "yes")
  set(DRIVER_SENSOR_LIS2DSH_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/LIS2DSH/LIS2DSH_Control.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS2DSH/LIS2DSH_Debug.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS2DSH/LIS2DSH_IoI2c.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS2DSH/LIS2DSH.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_SENSOR_LIS2DSH_SRCS})
endif()

# LIS3DSH ################################################################

if(${DRIVER_SENSOR_LIS3DSH} STREQUAL "yes")
  set(DRIVER_SENSOR_LIS3DSH_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/LIS3DSH/LIS3DSH_Control.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS3DSH/LIS3DSH_Debug.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS3DSH/LIS3DSH_IoI2c.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS3DSH/LIS3DSH.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_SENSOR_LIS3DSH_SRCS})
endif()

# LIS3MDL ################################################################

if(${DRIVER_SENSOR_LIS3MDL} STREQUAL "yes")
  set(DRIVER_SENSOR_LIS3MDL_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/LIS3MDL/LIS3MDL_Control.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS3MDL/LIS3MDL_Debug.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS3MDL/LIS3MDL_IoI2c.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS3MDL/LIS3MDL.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_SENSOR_LIS3MDL_SRCS})
endif()

# LSM6DSM ################################################################

if(${DRIVER_SENSOR_LSM6DSM} STREQUAL "yes")
  set(DRIVER_SENSOR_LSM6DSM_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/LSM6DSM/LSM6DSM_Configuration.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LSM6DSM/LSM6DSM_Control.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LSM6DSM/LSM6DSM_Debug.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LSM6DSM/LSM6DSM_IoI2c.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LSM6DSM/LSM6DSM_IoSpi.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LSM6DSM/LSM6DSM.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_SENSOR_LSM6DSM_SRCS})
endif()

##########################################################################
# SERIAL #################################################################
##########################################################################

set(DRIVER_SERIAL_SRC_PATH src/driver/serial)

# UART ###################################################################

if(${DRIVER_SERIAL} STREQUAL "yes")
  set(DRIVER_SERIAL_SRCS
    ${DRIVER_SERIAL_SRC_PATH}/Serial.cpp
    ${DRIVER_SERIAL_SRC_PATH}/UART/events/UART_onRxDoneCallback.cpp
    ${DRIVER_SERIAL_SRC_PATH}/UART/events/UART_onTxDoneCallback.cpp
    ${DRIVER_SERIAL_SRC_PATH}/UART/UART_SerialConfiguration.cpp
    ${DRIVER_SERIAL_SRC_PATH}/UART/UART_SerialControl.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_SERIAL_SRCS})
endif()

##########################################################################
# STEPPER ################################################################
##########################################################################

set(DRIVER_STEPPER_SRC_PATH src/driver/stepper)

# TMC26x #################################################################

if(${DRIVER_STEPPER_TMC26x} STREQUAL "yes")
  set(DRIVER_STEPPER_TMC26x_SRCS
    ${DRIVER_STEPPER_SRC_PATH}/TMC26x/TMC26x.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_STEPPER_TMC26x_SRCS})
endif()

##########################################################################
# TLCD ###################################################################
##########################################################################

set(DRIVER_TLCD_SRC_PATH src/driver/tlcd)

# HD44780 ################################################################

if(${DRIVER_TLCD_HD44780} STREQUAL "yes")
  set(DRIVER_TLCD_HD44780_SRCS
    ${DRIVER_TLCD_SRC_PATH}/HD44780/HD44780_Control.cpp
    ${DRIVER_TLCD_SRC_PATH}/HD44780/HD44780_IoGpio8Bit.cpp
    ${DRIVER_TLCD_SRC_PATH}/HD44780/HD44780.cpp
  )
  set(SNOWFOX_LIBRARY_DRIVER_SRCS ${SNOWFOX_LIBRARY_DRIVER_SRCS} ${DRIVER_TLCD_HD44780_SRCS})
endif()

##########################################################################
