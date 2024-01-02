#ifndef NoTimeoutScheduledCheckFtor_HPP_
#define NoTimeoutScheduledCheckFtor_HPP_
/*
 * Test_NoTimeoutScheduledCheckFtor.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD
#include "base/CheckFtorIF.hpp"

namespace lmp
{
  namespace base
  {
    class RetransmitTimer;
  }
  namespace cc
  {
    namespace test
    {
      class EventCallbackCalledCheckFtor;
      class NoTimeoutScheduledCheckFtor : public lmp::base::CheckFtorIF
      {
      public:
        NoTimeoutScheduledCheckFtor(
          const base::RetransmitTimer&         retransmitTimer,
          const EventCallbackCalledCheckFtor&  eventCallbackCalledCheckFtor);
        NoTimeoutScheduledCheckFtor(
          const NoTimeoutScheduledCheckFtor&  other);
      private:
        virtual bool do_check() const;
        virtual CheckFtorIF* do_clone() const;
        const base::RetransmitTimer&  m_retransmitTimer;
        const EventCallbackCalledCheckFtor&  m_eventCallbackCalledCheckFtor;
      };
    };
  } // namespace cc
} // namespace lmp

#endif /* NoTimeoutScheduledCheckFtor_HPP_ */
