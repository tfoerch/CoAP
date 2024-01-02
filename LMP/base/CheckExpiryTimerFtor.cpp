/*
 * CheckExpiryTimerFtor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "CheckExpiryTimerFtor.hpp"
#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

namespace lmp
{
  namespace base
  {
    CheckExpiryTimerFtor::CheckExpiryTimerFtor(
      boost::asio::io_context&          io_context,
      const std::chrono::milliseconds&  expiry_time)
      : m_timer(io_context, expiry_time),
        m_hasExpired(false)
    {
      m_timer.async_wait(boost::bind(&CheckExpiryTimerFtor::handle_expired,
                                     this,
                                     boost::asio::placeholders::error));
    }

    CheckExpiryTimerFtor::CheckExpiryTimerFtor(
      const CheckExpiryTimerFtor&      other)
    : m_timer(const_cast<boost::asio::steady_timer&>(other.m_timer).get_executor(),
              other.m_timer.expires_at()),
              m_hasExpired(other.m_hasExpired)
    {
      if (!m_hasExpired)
      {
        m_timer.async_wait(boost::bind(&CheckExpiryTimerFtor::handle_expired,
    	                               this,
    	                               boost::asio::placeholders::error));

      }
    }
    CheckExpiryTimerFtor::~CheckExpiryTimerFtor()
    {
      m_timer.cancel();
    }
    bool CheckExpiryTimerFtor::do_check() const
    {
      return m_hasExpired;
    }

    CheckFtorIF* CheckExpiryTimerFtor::do_clone() const
    {
      return new CheckExpiryTimerFtor(*this);
    }

    void CheckExpiryTimerFtor::handle_expired(
      const boost::system::error_code& /*error*/)
    {
      m_hasExpired = true;
    }
  } // namespace cc
} // namespace lmp
