/*
 * PCA9547_IO_I2C.h
 *
 *  Created on: Jan 8, 2018
 *      Author: alex
 */

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_PCA9547_INTERFACE_PCA9547_IO_I2C_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_PCA9547_INTERFACE_PCA9547_IO_I2C_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/ioexpander/PCA9547/interface/PCA9547_Io.h>

#include <snowfox/hal/interface/i2c/I2cMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::ioexpander::PCA9547
{

/**************************************************************************************
 * CLASS DECLARATION PCA9547
 **************************************************************************************/

class PCA9547_IoI2c final : public interface::PCA9547_Io
{

public:

           PCA9547_IoI2c(uint8_t const i2c_address, hal::interface::I2cMaster & i2c_master);
  virtual ~PCA9547_IoI2c();


  virtual bool readControlRegister   (uint8_t        * data) override;
  virtual bool writeControlRegister  (uint8_t const    data) override;


private:

  uint8_t                     _i2c_address;
  hal::interface::I2cMaster & _i2c_master;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::ioexpander::PCA9547 */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_PCA9547_INTERFACE_PCA9547_IO_I2C_H_ */
