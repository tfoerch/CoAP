#ifndef TEST_UTIL_WAIT_HPP_
#define TEST_UTIL_WAIT_HPP_
/*
 * Test_Wait.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include <chrono>

namespace boost
{
  namespace asio { class io_context; }
}
namespace lmp
{
  namespace base { class CheckFtorIF; }
  namespace test
  {
    namespace util
    {
      bool wait(
    	const lmp::base::CheckFtorIF&     checkFtor,
    	boost::asio::io_context&          io_context,
        const std::chrono::milliseconds&  expiry_time);
    } // namespace util
  } // namespace test
} // namespace lmp

#endif /* TEST_UTIL_WAIT_HPP_ */
