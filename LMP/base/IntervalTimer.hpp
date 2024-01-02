#ifndef LMP_BASE_INTERVAL_TIMER_HPP_
#define LMP_BASE_INTERVAL_TIMER_HPP_
/*
 * IntervalTimer.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD
#include <boost/function.hpp>
#include <boost/asio/steady_timer.hpp>

#include <chrono>

namespace lmp
{
  namespace base
  {
    class IntervalTimer
    {
    public:
      IntervalTimer(
    	boost::asio::io_context&          io_context,
    	const std::chrono::milliseconds&  timeoutInterval,
    	boost::function<bool (void)>      expiry_callback);
      void start();
      void stop();
    private:
      void handle_expired(
    	const boost::system::error_code&  error);
      boost::asio::steady_timer         m_timer;
      std::chrono::milliseconds         m_timeoutInterval;
      boost::function<bool (void)>      m_expiry_callback;
    };
  } // namespace base
} // namespace lmp

#endif /* LMP_BASE_INTERVAL_TIMER_HPP_ */
