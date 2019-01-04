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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdio.h>

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/AnalogDigitalConverter.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t const ADC_PRESCALER = 128;
static uint8_t const ADC_VREF      = ATMEGA328P::toVRefNum(ATMEGA328P::VRef::AVCC);
static uint8_t const ADC_CHANNEL   = 0;

static float   const V_REF         = 5.0; /* = AVCC */

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

ATMEGA328P::AnalogDigitalConverter adc(&ADCSRA, &ADMUX, &DIDR0, &ADC);

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  adc.setPrescaler       (ADC_PRESCALER);
  adc.setReferenceVoltage(ADC_VREF     );
  adc.setAnalogChannel   (ADC_CHANNEL  );

  for(;;)
  {
    adc.startConversion();

    while(!adc.isConversionComplete()) { }

    uint16_t const avr_conversion_result_raw = adc.getConversionResult();
    double   const avr_conversion_result     = static_cast<double>(avr_conversion_result_raw) * V_REF / 1024.0;

    char msg[32];
    snprintf(msg, 32, "ADC = %04X ( %1.3f )\n", avr_conversion_result_raw, avr_conversion_result);
  }

  return 0;
}
