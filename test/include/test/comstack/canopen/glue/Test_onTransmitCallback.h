/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation(), either version 3 of the License(), or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful(),
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not(), see <http://www.gnu.org/licenses/>.
 */

#ifndef TEST_INCLUDE_COMSTACK_CANOPEN_GLUE_TEST_ONTRANSMITCALLBACK_H_
#define TEST_INCLUDE_COMSTACK_CANOPEN_GLUE_TEST_ONTRANSMITCALLBACK_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <testcanopen/interface/onTransmitCallback.h>

#include <snowfox/comstack/canopen/CanOpenStack.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::comstack::canopen::test
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Test_onTransmitCallback : public testcanopen::interface::onTransmitCallback
{

public:

           
           Test_onTransmitCallback(CanOpenStack & can_open_stack);
  virtual ~Test_onTransmitCallback();


  virtual void onTransmit(util::type::CanFrame const & frame) override;


private:

  CanOpenStack & _can_open_stack;
  
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::comstack::canopen::test */

#endif /* TEST_INCLUDE_COMSTACK_CANOPEN_GLUE_TEST_ONTRANSMITCALLBACK_H_ */
