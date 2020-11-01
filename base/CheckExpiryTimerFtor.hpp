#ifndef COAP_BASE_CHECK_SERVICE_EVENT_TIMER_HPP_
#define COAP_BASE_CHECK_SERVICE_EVENT_TIMER_HPP_
/*
 * CheckExpiryTimerFtor.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <CheckFtorIF.hpp>
#include <experimental/timer>
//#include <experimental/netfwd>

namespace net = std::experimental::net;
namespace chrono = std::chrono;

namespace coap
{
  namespace base
  {
    class CheckExpiryTimerFtor : public CheckFtorIF
    {
    public:
      CheckExpiryTimerFtor(
    	net::io_context&             io_context,
    	const chrono::milliseconds&  expiry_time);
      CheckExpiryTimerFtor(
        const CheckExpiryTimerFtor& /* other */) = delete;
      ~CheckExpiryTimerFtor() = default; // ~basic_waitable_timer() cancels a pending wait
    private:
      virtual bool do_check() const;
      void handle_expired(
    	const std::error_code /*error*/);
      net::steady_timer        m_timer;
      bool                     m_hasExpired;
    };
  } // namespace base
} // namespace coap

#endif /* COAP_BASE_CHECK_SERVICE_EVENT_TIMER_HPP_ */
