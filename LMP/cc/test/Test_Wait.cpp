/*
 * Test_Wait.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include <Test_Wait.hpp>
#include <CheckExpiryTimerFtor.hpp>

namespace lmp
{
  namespace test
  {
    namespace util
    {
      bool wait(
    	const lmp::base::CheckFtorIF&     checkFtor,
    	boost::asio::io_context&          io_context,
        const std::chrono::milliseconds&  expiry_time)
      {
        lmp::base::CheckExpiryTimerFtor  expiryTimer(io_context, expiry_time);
        while (!checkFtor() && !expiryTimer())
        {
          io_context.run_one();
        }
        return checkFtor();
      }
    } // namespace util
  } // namespace test
} // namespace lmp
