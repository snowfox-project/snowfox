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

#include <spectre/util/container/List.hpp>

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

SCENARIO("A List container is constructed", "[util::container::List]")
{
  List<uint8_t> list;

  THEN("list.begin() should return 0") { REQUIRE(list.begin() == 0); }
  THEN("list.end() should return 0"  ) { REQUIRE(list.end  () == 0); }
}

/**************************************************************************************/

SCENARIO("A ListNode is inserted via 'push_front'", "[util::container::List]")
{
  List<uint8_t> list;

  WHEN("the list is empty")
  {
    list.push_front(1);

    ListNode<uint8_t> * inserted_node = list.begin();

    REQUIRE(inserted_node->data() == 1);

    THEN("list.begin() should point to the inserted node"      ) { REQUIRE(list.begin()          == inserted_node); }
    THEN("list.end() should point to the inserted node"        ) { REQUIRE(list.end()            == inserted_node); }
    THEN("The inserted node's 'prev' pointer should point to 0") { REQUIRE(inserted_node->prev() == 0            ); }
    THEN("The inserted node's 'next' pointer should point to 0") { REQUIRE(inserted_node->next() == 0            ); }
  }

  WHEN("there is one element in the list already")
  {
    list.push_front(1);
    ListNode<uint8_t> * first_inserted_node = list.begin();
    list.push_front(2);
    ListNode<uint8_t> * last_inserted_node  = list.begin();

    REQUIRE(first_inserted_node->data() == 1);
    REQUIRE(last_inserted_node->data () == 2);

    THEN("list.begin() should point to the last inserted element"                         ) { REQUIRE(list.begin()                == last_inserted_node ); }
    THEN("list.end() should point to the first inserted element"                          ) { REQUIRE(list.end()                  == first_inserted_node); }
    THEN("The first inserted node's 'prev' pointer should point to the last inserted node") { REQUIRE(first_inserted_node->prev() == last_inserted_node ); }
    THEN("The first inserted node's 'next' pointer should point to 0"                     ) { REQUIRE(first_inserted_node->next() == 0                  ); }
    THEN("The last inserted node's 'prev' pointer should point to 0"                      ) { REQUIRE(last_inserted_node->prev()  == 0                  ); }
    THEN("The last inserted node's 'next' pointer should point to the first inserted node") { REQUIRE(last_inserted_node->next()  == first_inserted_node); }
  }
}

/**************************************************************************************/

SCENARIO("A ListNode is inserted via 'push_back'", "[util::container::List]")
{
  List<uint8_t> list;

  WHEN("the list is empty")
  {
    list.push_back(1);

    ListNode<uint8_t> * inserted_node = list.begin();

    REQUIRE(inserted_node->data() == 1);

    THEN("list.begin() should point to the inserted node"      ) { REQUIRE(list.begin()              == inserted_node); }
    THEN("list.end() should point to the inserted node"        ) { REQUIRE(list.end()                == inserted_node); }
    THEN("The inserted node's 'prev' pointer should point to 0") { REQUIRE(inserted_node->prev() == 0                ); }
    THEN("The inserted node's 'next' pointer should point to 0") { REQUIRE(inserted_node->next() == 0                ); }
  }

  WHEN("there is one element in the list already")
  {
    list.push_back(1);
    ListNode<uint8_t> * first_inserted_node = list.end();
    list.push_back(2);
    ListNode<uint8_t> * last_inserted_node  = list.end();

    REQUIRE(first_inserted_node->data() == 1);
    REQUIRE(last_inserted_node->data () == 2);

    THEN("list.begin() should point to the first inserted element"                        ) { REQUIRE(list.begin()                == first_inserted_node ); }
    THEN("list.end() should point to the last inserted element"                           ) { REQUIRE(list.end()                  == last_inserted_node  ); }
    THEN("The first inserted node's 'prev' pointer should point to 0"                     ) { REQUIRE(first_inserted_node->prev() == 0                   ); }
    THEN("The first inserted node's 'next' pointer should point to the last inserted node") { REQUIRE(first_inserted_node->next() == last_inserted_node  ); }
    THEN("The last inserted node's 'prev' pointer should point to the first inserted node") { REQUIRE(last_inserted_node->prev()  == first_inserted_node ); }
    THEN("The last inserted node's 'next' pointer should point to 0"                      ) { REQUIRE(last_inserted_node->next()  == 0                   ); }
  }
}

/**************************************************************************************/

SCENARIO("A ListNode is removed via 'erase'", "[util::container::List]")
{
  List<uint8_t> list;

  WHEN("the list contains one element")
  {
    list.push_back(1);

    ListNode<uint8_t> * node = list.begin();

    list.erase(node);

    THEN("list.begin() should point to 0") { REQUIRE(list.begin() == 0); }
    THEN("list.end() should point to 0"  ) { REQUIRE(list.end()   == 0); }
  }
}

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

} /* test */

} /* container */

} /* util */

} /* spectre */
