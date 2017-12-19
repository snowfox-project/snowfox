/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include <spectre/debug/interface/Debug.h>
#include <spectre/hal/interface/i2c/I2CMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace TPA81
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  REG_COMMAND             = 0x00,
  REG_AMBIENT_TEMPERATURE = 0x01,
  REG_PIXEL_1             = 0x02,
  REG_PIXEL_2             = 0x03,
  REG_PIXEL_3             = 0x04,
  REG_PIXEL_4             = 0x05,
  REG_PIXEL_5             = 0x06,
  REG_PIXEL_6             = 0x07,
  REG_PIXEL_7             = 0x08,
  REG_PIXEL_8             = 0x09
} RegisterSelect;

typedef struct
{
  uint8_t pixel_1;
  uint8_t pixel_2;
  uint8_t pixel_3;
  uint8_t pixel_4;
  uint8_t pixel_5;
  uint8_t pixel_6;
  uint8_t pixel_7;
  uint8_t pixel_8;
} ThermophileData;

/**************************************************************************************
 * CLASS DECLARATION Interface
 **************************************************************************************/

class Interface
{

public:

           Interface() { }
  virtual ~Interface() { }

  virtual bool readSoftwareRevision   (uint8_t         * software_revision  ) = 0;
  virtual bool readAmbientTemperature (uint8_t         * ambient_temperature) = 0;
  virtual bool readThermophileArray   (ThermophileData * thermo_data        ) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION TPA81
 **************************************************************************************/

class TPA81 : public Interface
{

public:

           TPA81(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~TPA81();


  /* TPA81 Interface */

  virtual bool readSoftwareRevision   (uint8_t         * software_revision  ) override;
  virtual bool readAmbientTemperature (uint8_t         * ambient_temperature) override;
  virtual bool readThermophileArray   (ThermophileData * thermo_data        ) override;


          void debug_dumpAllRegs      (debug::interface::Debug & debug_interface);

private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

  bool readSingleRegister   (uint8_t const reg_addr, uint8_t        * data);
  bool writeSingleRegister  (uint8_t const reg_addr, uint8_t const    data);
  bool readMultipleRegister (uint8_t const reg_addr, uint8_t        * data, uint16_t const num_bytes);

  void debug_dumpSingleReg  (debug::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* TPA81 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_H_ */
