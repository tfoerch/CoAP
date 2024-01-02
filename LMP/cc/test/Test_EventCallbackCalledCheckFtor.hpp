#ifndef EVENTCALLBACKCALLEDCheckFtor_HPP_
#define EVENTCALLBACKCALLEDCheckFtor_HPP_
/*
 * Test_EventCallbackCalledCheckFtor.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD
#include "base/CheckFtorIF.hpp"
#include <boost/thread.hpp>

#include <chrono>
#include <deque>

namespace lmp
{
  namespace cc
  {
    namespace test
    {
      class EventCallbackCalledCheckFtor : public lmp::base::CheckFtorIF
      {
      public:
        struct TimeoutEvent
        {
          std::chrono::steady_clock::time_point   timePoint;
          bool                                    retryLimitReached;
        };
        typedef std::deque<TimeoutEvent>   TimeoutEventSequence;
        explicit EventCallbackCalledCheckFtor(
          lmp::DWORD                        numberOfCalls);
        EventCallbackCalledCheckFtor(
          const EventCallbackCalledCheckFtor&  other);
        bool eventOccurred(
          bool retryLimitReached);
        const TimeoutEventSequence&  getTimeouts() const;
        void reset();
      private:
        virtual bool do_check() const;
        virtual CheckFtorIF* do_clone() const;
        mutable boost::shared_mutex     m_flags_mutex;
        lmp::DWORD                      m_numberOfCalls;
        TimeoutEventSequence            m_timeouts;
      };
    };
  } // namespace cc
} // namespace lmp

#endif /* EVENTCALLBACKCALLEDCheckFtor_HPP_ */
