/*
 * Test_EventCallbackCalledCheckFtor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Test_EventCallbackCalledCheckFtor.hpp"
#include "neighbor/NeighborAdjacencyObserverIF.hpp"

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
      EventCallbackCalledCheckFtor::EventCallbackCalledCheckFtor(
        lmp::DWORD                        numberOfCalls)
      : m_numberOfCalls(numberOfCalls),
        m_timeouts()
      {}
      EventCallbackCalledCheckFtor::EventCallbackCalledCheckFtor(
        const EventCallbackCalledCheckFtor&  other)
      : m_numberOfCalls(other.m_numberOfCalls),
        m_timeouts(other.m_timeouts)
      {}
      bool EventCallbackCalledCheckFtor::eventOccurred(
        bool retryLimitReached)
      {
        TimeoutEvent  timeoutEvent =
          { std::chrono::steady_clock::now(), retryLimitReached };
        boost::unique_lock<boost::shared_mutex> guard(m_flags_mutex);
        std::cout << "EventCallbackCalledCheckFtor::eventOccurred(retryLimitReached = "
                  << retryLimitReached << ")" << std::endl;
        m_timeouts.push_back(timeoutEvent);
        return !retryLimitReached;
      }
      const EventCallbackCalledCheckFtor::TimeoutEventSequence&
      EventCallbackCalledCheckFtor::getTimeouts() const
      {
        return m_timeouts;
      }
      void EventCallbackCalledCheckFtor::reset()
      {
        boost::unique_lock<boost::shared_mutex> guard(m_flags_mutex);
        m_timeouts.clear();
      }
      bool EventCallbackCalledCheckFtor::do_check() const
      {
        boost::shared_lock<boost::shared_mutex> guard(m_flags_mutex);
        std::chrono::system_clock::time_point  now  = std::chrono::system_clock::now();
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
        std::time_t now_c = s.count();
        std::size_t fractional_seconds = ms.count() % 1000;
        std::cout << std::put_time(std::localtime(&now_c), "%T.") << fractional_seconds << " EventCallbackCalledCheckFtor::do_check() called" << std::endl;
        return (m_timeouts.size() == m_numberOfCalls);
      }
      base::CheckFtorIF* EventCallbackCalledCheckFtor::do_clone() const
      {
        return new EventCallbackCalledCheckFtor(*this);
      }
    }
  } // namespace cc
} // namespace lmp
