/*
 * PCA9547_IO_I2C.h
 *
 *  Created on: Jan 8, 2018
 *      Author: alex
 */

#ifndef INCLUDE_SPECTRE_DRIVER_IOEXPANDER_PCA9547_INTERFACE_PCA9547_IO_I2C_H_
#define INCLUDE_SPECTRE_DRIVER_IOEXPANDER_PCA9547_INTERFACE_PCA9547_IO_I2C_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/ioexpander/PCA9547/interface/PCA9547_Io.h>

#include <spectre/hal/interface/i2c/I2CMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace ioexpander
{

namespace PCA9547
{

/**************************************************************************************
 * CLASS DECLARATION PCA9547
 **************************************************************************************/

class PCA9547_IoI2c : public interface::PCA9547_Io
{

public:

           PCA9547_IoI2c(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~PCA9547_IoI2c();


  virtual bool readControlRegister   (uint8_t        * data) override;
  virtual bool writeControlRegister  (uint8_t const    data) override;


private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCA9547 */

} /* ioexpander */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_IOEXPANDER_PCA9547_INTERFACE_PCA9547_IO_I2C_H_ */
