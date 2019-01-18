/**
 * Snowfox is a modular RTOS with extensive IO support.
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

#include <tuple>
#include <vector>
#include <sstream>

#include <catch2/catch.hpp>

#include <snowfox/hal/avr/common/ATxxxx/util/UartUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATxxxx
{

namespace test
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef std::tuple<uint32_t, uint32_t, uint16_t> TestVectorEntry;
typedef std::vector<TestVectorEntry>             TestVector;

/**************************************************************************************
 * TEST HELPER PROTOTYPES
 **************************************************************************************/

TestVector createTestVector_16_MHz();

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

TestVector const TEST_VECT_16_MHz = createTestVector_16_MHz();

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("A UART Baudrate Register (UBBR) value is calculated from F_CPU and the desired baudrate", "[ATxxxx::UartUtil]")
{
  std::for_each(TEST_VECT_16_MHz.begin(),
                TEST_VECT_16_MHz.end  (),
                [](TestVectorEntry const entry)
                {
                  uint32_t const f_cpu    = std::get<0>(entry);
                  uint32_t const baudrate = std::get<1>(entry);
                  uint16_t const ubbr     = std::get<2>(entry);

                  std::stringstream when_ss, then_ss;
                  when_ss << "f_cpu = " << f_cpu << " and baudrate = " << baudrate;
                  then_ss << "calcUartBaudRate should return " << ubbr;

                  WHEN(when_ss.str())
                  {
                    THEN(then_ss.str())
                    {
                      REQUIRE(calcUartBaudRate(f_cpu, baudrate) == ubbr);
                    }
                  }
                });
}

/**************************************************************************************
 * TEST HELPER FUNCTIONS
 **************************************************************************************/

TestVector createTestVector_16_MHz()
{
  TestVector test_vector;

  /* 16 MHz / 2400 - 115200 Baud - U2XN is set */
  test_vector.push_back(std::make_tuple(16000000UL, 2400,   832));
  test_vector.push_back(std::make_tuple(16000000UL, 4800,   415)); /* Datasheet: 416 */
  test_vector.push_back(std::make_tuple(16000000UL, 9600,   207));
  test_vector.push_back(std::make_tuple(16000000UL, 14400,  137)); /* Datasheet: 138 */
  test_vector.push_back(std::make_tuple(16000000UL, 19200,  103));
  test_vector.push_back(std::make_tuple(16000000UL, 28800,   68));
  test_vector.push_back(std::make_tuple(16000000UL, 38400,   51));
  test_vector.push_back(std::make_tuple(16000000UL, 57600,   33)); /* Datasheet:  34 */
  test_vector.push_back(std::make_tuple(16000000UL, 76800,   25));
  test_vector.push_back(std::make_tuple(16000000UL, 115200,  16));

  return test_vector;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* ATxxxx */

} /* hal */

} /* snowfox */
