/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#include <spectre/util/container/Queue.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace util
{

namespace container
{

namespace test
{

/**************************************************************************************/

SCENARIO("A queue is constructed with a size of 0 (queue of capacity of 0 elements -> makes no sense)", "[util::container::Queue]")
{
  Queue<uint8_t> queue(0);

  THEN("'size' should return 0")
  {
    REQUIRE(queue.size() == 0);
  }
  THEN("'capacity' should return 0")
  {
    REQUIRE(queue.capacity() == 0);
  }
  THEN("'isFull' should return true")
  {
    REQUIRE(queue.isFull() == true);
  }
  THEN("'isEmpty' should return true")
  {
    REQUIRE(queue.isEmpty() == true);
  }

  WHEN("trying to insert a new element via 'push'")
  {
    THEN("'push' should return false")
    {
      REQUIRE(queue.push(0xCA) == false);
    }
  }

  WHEN("trying to remove a element via 'pop'")
  {
    THEN("'pop' should return false")
    {
      uint8_t data = 0;
      REQUIRE(queue.pop(&data) == false);
    }
  }
}

/**************************************************************************************/

SCENARIO("A queue is constructed with a size of > 0 and no elements are inserted (empty queue)", "[util::container::Queue]")
{
  Queue<uint8_t> queue(5);

  THEN("'size' should return 0")
  {
    REQUIRE(queue.size() == 0);
  }
  THEN("'capacity' should return the constructed size")
  {
    REQUIRE(queue.capacity() == 5);
  }
  THEN("'isFull' should return false")
  {
    REQUIRE(queue.isFull() == false);
  }
  THEN("'isEmpty' should return true")
  {
    REQUIRE(queue.isEmpty() == true);
  }

  WHEN("trying to insert a new element via 'push'")
  {
    THEN("'push' should return true")
    {
      REQUIRE(queue.push(0xCA) == true);
    }
  }

  WHEN("trying to remove a element via 'pop'")
  {
    THEN("'pop' should return false")
    {
      uint8_t data = 0;
      REQUIRE(queue.pop(&data) == false);
    }
  }
}

/**************************************************************************************/

SCENARIO("A queue is constructed with a size of > 0 and it is filled completely with elements (full queue)", "[util::container::Queue]")
{
  Queue<uint8_t> queue(5);

  REQUIRE(queue.push(0xCA) == true);
  REQUIRE(queue.push(0xFE) == true);
  REQUIRE(queue.push(0xCA) == true);
  REQUIRE(queue.push(0xFE) == true);
  REQUIRE(queue.push(0xCA) == true);

  THEN("'size' should return the number of elements inserted")
  {
    REQUIRE(queue.size() == 5);
  }
  THEN("'capacity' should return the constructed size")
  {
    REQUIRE(queue.capacity() == 5);
  }
  THEN("'isFull' should return true")
  {
    REQUIRE(queue.isFull() == true);
  }
  THEN("'isEmpty' should return false")
  {
    REQUIRE(queue.isEmpty() == false);
  }

  WHEN("trying to insert a new element via 'push'")
  {
    THEN("'push' should return false")
    {
      REQUIRE(queue.push(0xCA) == false);
    }
  }

  WHEN("trying to remove a element via 'pop'")
  {
    THEN("'pop' should return true")
    {
      uint8_t data = 0;
      REQUIRE(queue.pop(&data) == true);
    }
  }
}

/**************************************************************************************/

SCENARIO("A queue is constructed with a size of > 0 and elements are inserted and removed (normal scenario)", "[util::container::Queue]")
{
  Queue<uint8_t> queue(5);

  WHEN("some elements are inserted via 'push'")
  {
    REQUIRE(queue.push(0x00) == true);
    REQUIRE(queue.push(0x01) == true);
    REQUIRE(queue.push(0x02) == true);

    THEN("they can be retrieved ('pop') in the exact order with which they where 'push'ed into the system")
    {
      uint8_t data = 0;
      REQUIRE(queue.pop(&data) == true); REQUIRE(data == 0x00);
      REQUIRE(queue.pop(&data) == true); REQUIRE(data == 0x01);
      REQUIRE(queue.pop(&data) == true); REQUIRE(data == 0x02);
    }
  }

  WHEN("some elements are inserted via 'push'")
  {
    REQUIRE(queue.push(0x00) == true); THEN("'size' always returns the number of elements stored in the queue") REQUIRE(queue.size() == 1);
    REQUIRE(queue.push(0x01) == true); THEN("'size' always returns the number of elements stored in the queue") REQUIRE(queue.size() == 2);
    REQUIRE(queue.push(0x02) == true); THEN("'size' always returns the number of elements stored in the queue") REQUIRE(queue.size() == 3);

    WHEN("they are retrieved afterwards via 'pop'")
    {
      uint8_t data = 0;
      REQUIRE(queue.pop(&data) == true); REQUIRE(data == 0x00); THEN("'size' always returns the number of elements stored in the queue") REQUIRE(queue.size() == 2);
      REQUIRE(queue.pop(&data) == true); REQUIRE(data == 0x01); THEN("'size' always returns the number of elements stored in the queue") REQUIRE(queue.size() == 1);
      REQUIRE(queue.pop(&data) == true); REQUIRE(data == 0x02); THEN("'size' always returns the number of elements stored in the queue") REQUIRE(queue.size() == 0);
    }
  }
}

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

} /* test */

} /* container */

} /* util */

} /* spectre */
