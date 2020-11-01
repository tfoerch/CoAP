#ifndef COAP_BASE_WAIT_HPP_
#define COAP_BASE_WAIT_HPP_
/*
 * Wait.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include <chrono>
#include <experimental/io_context>

namespace net = std::experimental::net;
namespace chrono = std::chrono;

namespace coap
{
  namespace base
  {
    class CheckFtorIF;

    namespace util
    {
      bool wait(
    	const CheckFtorIF&           checkFtor,
    	net::io_context&             io_context,
        const chrono::milliseconds&  expiry_time);
    } // namespace util
  } // namespace base
} // namespace coap

#endif /* COAP_BASE_WAIT_HPP_ */
