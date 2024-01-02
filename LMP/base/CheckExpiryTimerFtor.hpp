#ifndef LMP_BASE_CHECK_SERVICE_EVENT_TIMER_HPP_
#define LMP_BASE_CHECK_SERVICE_EVENT_TIMER_HPP_
/*
 * CheckExpiryTimerFtor.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <CheckFtorIF.hpp>
#include <boost/asio/steady_timer.hpp>

#include <chrono>

namespace boost { namespace asio { class io_context; } }
namespace boost { namespace system { class error_code; } }

namespace lmp
{
  namespace base
  {
    class CheckExpiryTimerFtor : public CheckFtorIF
    {
    public:
      CheckExpiryTimerFtor(
    	boost::asio::io_context&          io_context,
    	const std::chrono::milliseconds&  expiry_time);
      CheckExpiryTimerFtor(
        const CheckExpiryTimerFtor&      other);
      virtual ~CheckExpiryTimerFtor();
    private:
      virtual bool do_check() const;
      virtual CheckFtorIF* do_clone() const;
      void handle_expired(
    	const boost::system::error_code& /*error*/);
      boost::asio::steady_timer        m_timer;
      bool                             m_hasExpired;
    };
  } // namespace base
} // namespace lmp

#endif /* LMP_BASE_CHECK_SERVICE_EVENT_TIMER_HPP_ */
