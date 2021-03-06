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

#ifndef TEST_INCLUDE_COMSTACK_CANOPEN_GLUE_STACK_ONTRANSMITCALLBACK_H_
#define TEST_INCLUDE_COMSTACK_CANOPEN_GLUE_STACK_ONTRANSMITCALLBACK_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/comstack/canopen/interface/CanOpen_onTransmitCallback.h>

#include <testcanopen/TestManager.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::comstack::canopen::test
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Stack_onTransmitCallback : public interface::CanOpen_onTransmitCallback
{

public:

           Stack_onTransmitCallback(testcanopen::TestManager & test_mgr);
  virtual ~Stack_onTransmitCallback();


  virtual void onTransmit(util::type::CanFrame const & frame) override;


private:

  testcanopen::TestManager & _test_mgr;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::comstack::canopen::test */

#endif /* TEST_INCLUDE_COMSTACK_CANOPEN_GLUE_STACK_ONTRANSMITCALLBACK_H_ */
