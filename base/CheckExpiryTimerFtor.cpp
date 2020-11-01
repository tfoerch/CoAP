/*
 * CheckExpiryTimerFtor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "CheckExpiryTimerFtor.hpp"
#include <functional>

namespace coap
{
  namespace base
  {
    CheckExpiryTimerFtor::CheckExpiryTimerFtor(
      net::io_context&             io_context,
      const chrono::milliseconds&  expiry_time)
      : m_timer(io_context, expiry_time),
        m_hasExpired(false)
    {
      m_timer.async_wait(std::bind(&CheckExpiryTimerFtor::handle_expired,
                                   this,
                                   std::placeholders::_1));
    }

//    CheckExpiryTimerFtor::CheckExpiryTimerFtor(
//      const CheckExpiryTimerFtor&      other)
//    : m_timer(const_cast<net::steady_timer&>(other.m_timer).get_executor().context(),
//              other.m_timer.expiry()),
//              m_hasExpired(other.m_hasExpired)
//    {
//      if (!m_hasExpired)
//      {
//        m_timer.async_wait(std::bind(&CheckExpiryTimerFtor::handle_expired,
//                                     this,
//                                     std::placeholders::_1));
//      }
//    }
//    CheckExpiryTimerFtor::~CheckExpiryTimerFtor()
//    {
//      m_timer.cancel();
//    }
    bool CheckExpiryTimerFtor::do_check() const
    {
      return m_hasExpired;
    }

    void CheckExpiryTimerFtor::handle_expired(
      const std::error_code /*error*/)
    {
      m_hasExpired = true;
    }
  } // namespace cc
} // namespace coap
