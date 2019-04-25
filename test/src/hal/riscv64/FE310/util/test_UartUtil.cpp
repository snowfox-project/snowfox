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

#include <snowfox/hal/riscv64/FE310/util/UartUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace FE310
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

TestVector createTestVector();

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

TestVector const TEST_VECT = createTestVector();

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("A FE310::UART_DIV baudrate value is calculated from tlclk and the desired baudrate", "[FE310::UartUtil]")
{
  std::for_each(TEST_VECT.begin(),
                TEST_VECT.end  (),
                [](TestVectorEntry const entry)
                {
                  uint32_t const tlclk_Hz = std::get<0>(entry);
                  uint32_t const baudrate = std::get<1>(entry);
                  uint16_t const uart_div = std::get<2>(entry);

                  std::stringstream when_ss, then_ss;
                  when_ss << "tlclk_Hz = " << tlclk_Hz << " and baudrate = " << baudrate;
                  then_ss << "calcUartBaudRate should return " << tlclk_Hz;

                  WHEN(when_ss.str()) {
                    THEN(then_ss.str()) {
                      REQUIRE(calcUartBaudRate(tlclk_Hz, baudrate) == uart_div);
                    }
                  }
                });
}

/**************************************************************************************
 * TEST HELPER FUNCTIONS
 **************************************************************************************/

TestVector createTestVector()
{
  TestVector test_vector;

  /* Source: SiFive FE310-G002 Manual v19p04, Table 62 */
  test_vector.push_back(std::make_tuple(2000000UL,     31250,    64));
  test_vector.push_back(std::make_tuple(2000000UL,    115200,    17));

  test_vector.push_back(std::make_tuple(16000000UL,    31250,   512));
  test_vector.push_back(std::make_tuple(16000000UL,   115200,   138)); /* Datasheet: 139 */
  test_vector.push_back(std::make_tuple(16000000UL,   250000,    64));

  test_vector.push_back(std::make_tuple(200000000UL,   31250,  6400));
  test_vector.push_back(std::make_tuple(200000000UL,  115200,  1736));
  test_vector.push_back(std::make_tuple(200000000UL,  250000,   800));
  test_vector.push_back(std::make_tuple(200000000UL, 1843200,   108)); /* Datasheet: 109 */

  test_vector.push_back(std::make_tuple(384000000UL,   31250, 12288));
  test_vector.push_back(std::make_tuple(384000000UL,  115200,  3333));
  test_vector.push_back(std::make_tuple(384000000UL,  250000,  1536));
  test_vector.push_back(std::make_tuple(384000000UL, 1843200,   208));

  return test_vector;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* FE310 */

} /* hal */

} /* snowfox */
