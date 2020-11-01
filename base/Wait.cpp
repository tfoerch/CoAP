/*
 * Wait.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include <Wait.hpp>
#include <CheckExpiryTimerFtor.hpp>

namespace coap
{
  namespace base
  {
    namespace util
    {
      bool wait(
    	const CheckFtorIF&           checkFtor,
    	net::io_context&             io_context,
        const chrono::milliseconds&  expiry_time)
      {
        CheckExpiryTimerFtor  expiryTimer(io_context, expiry_time);
        while (!checkFtor() && !expiryTimer())
        {
          io_context.run_one();
        }
        return checkFtor();
      }
    } // namespace util
  } // namespace test
} // namespace coap
