/*
 * Test_NoTimeoutScheduledCheckFtor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Test_NoTimeoutScheduledCheckFtor.hpp"
#include "Test_EventCallbackCalledCheckFtor.hpp"
#include "base/RetransmitTimer.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

namespace lmp
{
  namespace cc
  {
    namespace test
    {
      NoTimeoutScheduledCheckFtor::NoTimeoutScheduledCheckFtor(
        const base::RetransmitTimer&         retransmitTimer,
        const EventCallbackCalledCheckFtor&  eventCallbackCalledCheckFtor)
      : m_retransmitTimer(retransmitTimer),
        m_eventCallbackCalledCheckFtor(eventCallbackCalledCheckFtor)
      {}
      NoTimeoutScheduledCheckFtor::NoTimeoutScheduledCheckFtor(
        const NoTimeoutScheduledCheckFtor&  other)
      : m_retransmitTimer(other.m_retransmitTimer),
        m_eventCallbackCalledCheckFtor(other.m_eventCallbackCalledCheckFtor)
      {}
      bool NoTimeoutScheduledCheckFtor::do_check() const
      {
        return
          ( !m_eventCallbackCalledCheckFtor.getTimeouts().empty() &&
            ( m_retransmitTimer.getRetryCounter() == 0 ||
              m_retransmitTimer.isReltryLimitReached() ) );
      }
      base::CheckFtorIF* NoTimeoutScheduledCheckFtor::do_clone() const
      {
        return new NoTimeoutScheduledCheckFtor(*this);
      }
    }
  } // namespace cc
} // namespace lmp
