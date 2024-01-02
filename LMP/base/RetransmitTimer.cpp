/*
 * RetransmitTimer.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "RetransmitTimer.hpp"
#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

#include <iostream>

namespace lmp
{
  namespace base
  {
    //      Prior to initial transmission, initialize Rk = Ri and Rn = 0.
    //
    //      while (Rn++ < Rl) {
    //        transmit the message;
    //        wake up after Rk milliseconds;
    //        Rk = Rk * (1 + Delta);
    //      }
    //      /* acknowledged message or no reply from receiver and Rl
    //         reached */
    //      do any needed clean up;
    //      exit;
   RetransmitTimer::RetransmitTimer(
      boost::asio::io_context&          io_context,
      const std::chrono::milliseconds&  initialRetransmitInterval,
      lmp::DWORD                        retryLimit,
      lmp::DWORD                        incrementValueDelta,
      boost::function<bool (bool)>      expiry_callback)
      : m_timer(io_context),
        m_initialRetransmitInterval(initialRetransmitInterval),
        m_retryLimit(retryLimit),
        m_incrementValueDelta(incrementValueDelta),
        m_expiry_callback(expiry_callback),
        m_currentRetransmitIinterval(m_initialRetransmitInterval),
        m_retryCounter(0)
    {
    }
    void RetransmitTimer::start()
    {
      m_currentRetransmitIinterval = m_initialRetransmitInterval;
      m_retryCounter = 1;
      boost::system::error_code  error;
      m_timer.expires_from_now(m_initialRetransmitInterval, error);
      m_timer.async_wait(boost::bind(&RetransmitTimer::handle_expired,
                                     this,
                                     boost::asio::placeholders::error));
    }
    void RetransmitTimer::stop()
    {
      std::cout << "RetransmitTimer::stop called" << std::endl;
      boost::system::error_code  error;
      m_timer.cancel(error);
      m_currentRetransmitIinterval = m_initialRetransmitInterval;
      m_retryCounter = 0;
    }
    void RetransmitTimer::handle_expired(
      const boost::system::error_code&  error)
    {
      std::cout << "RetransmitTimer::handle_expired called" << std::endl;
      if (!error)
      {
        bool reschedule =
          m_expiry_callback(m_retryCounter >= m_retryLimit);
        if (reschedule &&
            m_retryCounter++ < m_retryLimit)
        {
          m_currentRetransmitIinterval *= (1 + m_incrementValueDelta);
          boost::system::error_code  error_code;
          m_timer.expires_from_now(m_currentRetransmitIinterval, error_code);
          if (!error_code)
          {
            std::cout << "RetransmitTimer::handle_expired reschedule in " << m_currentRetransmitIinterval.count() <<  " milliseconds" << std::endl;
          }
          else
          {
            std::cout << "RetransmitTimer::handle_expired reschedule caused an error" << std::endl;
          }
          m_timer.async_wait(boost::bind(&RetransmitTimer::handle_expired,
                                         this,
                                         boost::asio::placeholders::error));
        }
      }
      else
      {
        std::cout << "RetransmitTimer::handle_expired call with error" << std::endl;
      }
    }
  } // namespace cc
} // namespace lmp
