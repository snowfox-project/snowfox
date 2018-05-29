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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <catch.hpp>

#include <spectre/memory/container/List.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace memory
{

namespace container
{

namespace test
{

/**************************************************************************************/

SCENARIO("A List container is constructed", "[memory::container::List]")
{
  List<uint8_t> list;

  THEN("list.begin() should return 0") { REQUIRE(list.begin() == 0); }
  THEN("list.end() should return 0"  ) { REQUIRE(list.end  () == 0); }
}

/**************************************************************************************/

SCENARIO("A ListNode is inserted via 'push_front'", "[memory::container::List]")
{
  List<uint8_t> list;

  WHEN("the list is empty")
  {
    list.push_front(1);

    ListNode<uint8_t> * ptr_inserted_node = list.begin();

    REQUIRE(ptr_inserted_node->data() == 1);

    THEN("list.begin() should point to the inserted node"      ) { REQUIRE(list.begin()              == ptr_inserted_node); }
    THEN("list.end() should point to the inserted node"        ) { REQUIRE(list.end()                == ptr_inserted_node); }
    THEN("The inserted node's 'prev' pointer should point to 0") { REQUIRE(ptr_inserted_node->prev() == 0                ); }
    THEN("The inserted node's 'next' pointer should point to 0") { REQUIRE(ptr_inserted_node->next() == 0                ); }
  }

  WHEN("there is one element in the list already")
  {
    list.push_front(1);
    ListNode<uint8_t> * ptr_first_inserted_node = list.begin();
    list.push_front(2);
    ListNode<uint8_t> * ptr_last_inserted_node  = list.begin();

    REQUIRE(ptr_first_inserted_node->data() == 1);
    REQUIRE(ptr_last_inserted_node->data () == 2);

    THEN("list.begin() should point to the last inserted element"                         ) { REQUIRE(list.begin()                    == ptr_last_inserted_node ); }
    THEN("list.end() should point to the first inserted element"                          ) { REQUIRE(list.end()                      == ptr_first_inserted_node); }
    THEN("The first inserted node's 'prev' pointer should point to the last inserted node") { REQUIRE(ptr_first_inserted_node->prev() == ptr_last_inserted_node ); }
    THEN("The first inserted node's 'next' pointer should point to 0"                     ) { REQUIRE(ptr_first_inserted_node->next() == 0                      ); }
    THEN("The last inserted node's 'prev' pointer should point to 0"                      ) { REQUIRE(ptr_last_inserted_node->prev()  == 0                      ); }
    THEN("The last inserted node's 'next' pointer should point to the first inserted node") { REQUIRE(ptr_last_inserted_node->next()  == ptr_first_inserted_node); }
  }
}

/**************************************************************************************/

SCENARIO("A ListNode is inserted via 'push_back'", "[memory::container::List]")
{
  List<uint8_t> list;

  WHEN("the list is empty")
  {
    list.push_back(1);

    ListNode<uint8_t> * ptr_inserted_node = list.begin();

    REQUIRE(ptr_inserted_node->data() == 1);

    THEN("list.begin() should point to the inserted node"      ) { REQUIRE(list.begin()              == ptr_inserted_node); }
    THEN("list.end() should point to the inserted node"        ) { REQUIRE(list.end()                == ptr_inserted_node); }
    THEN("The inserted node's 'prev' pointer should point to 0") { REQUIRE(ptr_inserted_node->prev() == 0                ); }
    THEN("The inserted node's 'next' pointer should point to 0") { REQUIRE(ptr_inserted_node->next() == 0                ); }
  }

  WHEN("there is one element in the list already")
  {
    list.push_back(1);
    ListNode<uint8_t> * ptr_first_inserted_node = list.end();
    list.push_back(2);
    ListNode<uint8_t> * ptr_last_inserted_node  = list.end();

    REQUIRE(ptr_first_inserted_node->data() == 1);
    REQUIRE(ptr_last_inserted_node->data () == 2);

    THEN("list.begin() should point to the first inserted element"                        ) { REQUIRE(list.begin()                    == ptr_first_inserted_node ); }
    THEN("list.end() should point to the last inserted element"                           ) { REQUIRE(list.end()                      == ptr_last_inserted_node  ); }
    THEN("The first inserted node's 'prev' pointer should point to 0"                     ) { REQUIRE(ptr_first_inserted_node->prev() == 0                       ); }
    THEN("The first inserted node's 'next' pointer should point to the last inserted node") { REQUIRE(ptr_first_inserted_node->next() == ptr_last_inserted_node  ); }
    THEN("The last inserted node's 'prev' pointer should point to the first inserted node") { REQUIRE(ptr_last_inserted_node->prev()  == ptr_first_inserted_node ); }
    THEN("The last inserted node's 'next' pointer should point to 0"                      ) { REQUIRE(ptr_last_inserted_node->next()  == 0                       ); }
  }
}

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

} /* test */

} /* container */

} /* memory */

} /* spectre */
