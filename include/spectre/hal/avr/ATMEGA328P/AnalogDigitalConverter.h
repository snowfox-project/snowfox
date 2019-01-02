/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_ANALOGDIGITALCONVERTER_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_ANALOGDIGITALCONVERTER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/adc/AnalogDigitalConverter.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA328P
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class VRef : uint8_t
{
  AREF,
  AVCC,
  BANDGAP_1_1V
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AnalogDigitalConverter : public interface::AnalogDigitalConverter
{

public:

           AnalogDigitalConverter(volatile uint8_t * adcsra, volatile uint8_t * admux, volatile uint8_t * didr0, volatile uint16_t * adc);
  virtual ~AnalogDigitalConverter();


  /* Analog Digital Converter Control Interface */

  virtual void     setAnalogChannel     (uint8_t const adc_channel) override;
  virtual void     startConversion      (                         ) override;
  virtual bool     isConversionComplete (                         ) override;
  virtual uint32_t getConversionResult  (                         ) override;


  /* Analog Digital Converter Configuration Interface */

  virtual void setPrescaler       (uint32_t const prescaler) override;
  virtual void setReferenceVoltage(uint8_t  const v_ref    ) override;


  static uint8_t toVRefNum(VRef const vref);

private:

  volatile uint8_t  * _ADCSRA,
                    * _ADMUX,
                    * _DIDR0;
  volatile uint16_t * _ADC;

  void enableAdc ();
  void disableAdc();

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_ANALOGDIGITALCONVERTER_H_ */
