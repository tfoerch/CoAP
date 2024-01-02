/*
 * IntervalTimer.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "IntervalTimer.hpp"
#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

#include <iostream>

namespace lmp
{
  namespace base
  {
   IntervalTimer::IntervalTimer(
      boost::asio::io_context&          io_context,
      const std::chrono::milliseconds&  timeoutInterval,
      boost::function<bool (void)>      expiry_callback)
      : m_timer(io_context),
        m_timeoutInterval(timeoutInterval),
        m_expiry_callback(expiry_callback)
    {
    }
    void IntervalTimer::start()
    {
      boost::system::error_code  error;
      m_timer.expires_from_now(m_timeoutInterval, error);
      m_timer.async_wait(boost::bind(&IntervalTimer::handle_expired,
                                     this,
                                     boost::asio::placeholders::error));
    }
    void IntervalTimer::stop()
    {
      boost::system::error_code  error;
      m_timer.cancel(error);
    }
    void IntervalTimer::handle_expired(
      const boost::system::error_code&  error)
    {
      std::cout << "IntervalTimer::handle_expired called" << std::endl;
      if (!error)
      {
        bool reschedule =
          m_expiry_callback();
        if (reschedule)
        {
          boost::system::error_code  error_code;
          m_timer.expires_from_now(m_timeoutInterval, error_code);
          if (!error_code)
          {
            std::cout << "IntervalTimer::handle_expired reschedule in " << m_timeoutInterval.count() <<  " milliseconds" << std::endl;
          }
          else
          {
            std::cout << "IntervalTimer::handle_expired reschedule caused an error" << std::endl;
          }
          m_timer.async_wait(boost::bind(&IntervalTimer::handle_expired,
                                         this,
                                         boost::asio::placeholders::error));
        }
      }
      else
      {
        std::cout << "IntervalTimer::handle_expired call with error" << std::endl;
      }
    }
  } // namespace cc
} // namespace lmp
