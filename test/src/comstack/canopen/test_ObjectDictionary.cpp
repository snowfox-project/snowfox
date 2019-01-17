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

#include <catch.hpp>

#include <snowfox/comstack/canopen/objdict/ObjectDictionary.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace comstack
{

namespace canopen
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("A ObjectDictionary object is constructed", "[comstack::canopen::ObjectDictionary]")
{
  ObjectDictionary obj_dict;

  /************************************************************************************/

  THEN("When requesting a UINT8 entry a empty entry object should be returned")
  {
    REQUIRE(obj_dict.get_UINT8 (0x0001, 0x01) == 0);
  }
  THEN("When requesting a UINT16 entry a empty entry object should be returned")
  {
    REQUIRE(obj_dict.get_UINT16(0x0001, 0x01) == 0);
  }
  THEN("When requesting a UINT32 entry a empty entry object should be returned")
  {
    REQUIRE(obj_dict.get_UINT32(0x0001, 0x01) == 0);
  }
  THEN("When requesting a STRING entry a empty entry object should be returned")
  {
    REQUIRE(obj_dict.get_STRING(0x0001, 0x01) == 0);
  }

  /************************************************************************************/

  WHEN("A UINT8 obj dict entry is added")
  {
    ObjectDictionaryEntry<uint8_t> * entry = new ObjectDictionaryEntry<uint8_t>(0x1001, 0x01, 0xFF, ObjectDictionaryAccess::ReadWrite, 0);

    obj_dict.add(entry);

    THEN("When requesting the added UINT8 entry the desired reference should be returned")
    {
      REQUIRE(obj_dict.get_UINT8(0x1001, 0x01) == entry);
    }
    THEN("When requesting a not added UINT8 entry a empty entry object should be returned")
    {
      REQUIRE(obj_dict.get_UINT8 (0x0001, 0x01) == 0);
    }

    delete entry; entry = 0;
  }

  /************************************************************************************/

  WHEN("A UINT16 obj dict entry is added")
  {
    ObjectDictionaryEntry<uint16_t> * entry = new ObjectDictionaryEntry<uint16_t>(0x1001, 0x01, 0xCAFE, ObjectDictionaryAccess::ReadWrite, 0);

    obj_dict.add(entry);

    THEN("When requesting the added UINT16 entry the desired reference should be returned")
    {
      REQUIRE(obj_dict.get_UINT16(0x1001, 0x01) == entry);
    }
    THEN("When requesting a not added UINT16 entry a empty entry object should be returned")
    {
      REQUIRE(obj_dict.get_UINT16(0x0001, 0x01) == 0);
    }

    delete entry; entry = 0;
  }

  /************************************************************************************/

  WHEN("A UINT32 obj dict entry is added")
  {
    ObjectDictionaryEntry<uint32_t> * entry = new ObjectDictionaryEntry<uint32_t>(0x1001, 0x01, 0xCAFFEE, ObjectDictionaryAccess::ReadWrite, 0);

    obj_dict.add(entry);

    THEN("When requesting the added UINT32 entry the desired reference should be returned")
    {
      REQUIRE(obj_dict.get_UINT32(0x1001, 0x01) == entry);
    }
    THEN("When requesting a not added UINT32 entry a empty entry object should be returned")
    {
      REQUIRE(obj_dict.get_UINT32(0x0001, 0x01) == 0);
    }

    delete entry; entry = 0;
  }

  /************************************************************************************/

  WHEN("A STRING obj dict entry is added")
  {
    ObjectDictionaryEntry<util::type::StaticString> * entry = new ObjectDictionaryEntry<util::type::StaticString>(0x1001, 0x01, "CAFFEE", ObjectDictionaryAccess::ReadWrite, 0);

    obj_dict.add(entry);

    THEN("When requesting the added STRING entry the desired reference should be returned")
    {
      REQUIRE(obj_dict.get_STRING(0x1001, 0x01) == entry);
    }
    THEN("When requesting a not added STRING entry a empty entry object should be returned")
    {
      REQUIRE(obj_dict.get_STRING(0x0001, 0x01) == 0);
    }

    delete entry; entry = 0;
  }

  /************************************************************************************/
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* canopen */

} /* comstack */

} /* snowfox */
