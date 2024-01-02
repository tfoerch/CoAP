#ifndef LIBS_IPCC_EVENT_HPP_
#define LIBS_IPCC_EVENT_HPP_
/*
 * IPCC_Event.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */

#include <iostream>

namespace lmp
{
  namespace cc
  {
    namespace appl
    {
      class Event
      {
      public:
        enum EvType
        {
          EvBringUp,
          EvCCDn,
          EvConfDone,
          EvConfErr,
          EvNewConfOK,
          EvNewConfErr,
          EvContenWin,
          EvContenLost,
          EvAdminDown,
          EvNbrGoesDn,
          EvHelloRcvd,
          EvHoldTimer,
          EvSeqNumErr,
          EvReconfig,
          EvConfRet,
          EvHelloRet,
          EvDownTimer
        };
        inline std::ostream& print(std::ostream& os) const
        { return do_print(os); }
        inline EvType getType() const { return do_getType(); }
        virtual ~Event(){}
      private:
        virtual std::ostream& do_print(std::ostream& os) const = 0;
        virtual EvType do_getType() const = 0;
      };
      inline std::ostream& operator<<(
        std::ostream&       os,
        const Event&        event)
      { return event.print(os); }
      std::ostream& operator<<(
        std::ostream&       os,
        Event::EvType       evType);

      template <Event::EvType  eventType>
      class EventTag : public Event
      {
      public:
        virtual ~EventTag(){}
        EventTag(){}
      private:
        virtual std::ostream& do_print(std::ostream& os) const
        { os << getType(); return os; }
        virtual Event::EvType do_getType() const { return eventType; };
      };
      typedef EventTag<Event::EvBringUp>       EvBringUp;
      typedef EventTag<Event::EvCCDn>          EvCCDn;
      typedef EventTag<Event::EvConfDone>      EvConfDone;
      typedef EventTag<Event::EvConfErr>       EvConfErr;
      typedef EventTag<Event::EvNewConfOK>     EvNewConfOK;
      typedef EventTag<Event::EvNewConfErr>    EvNewConfErr;
      typedef EventTag<Event::EvContenWin>     EvContenWin;
      typedef EventTag<Event::EvContenLost>    EvContenLost;
      typedef EventTag<Event::EvAdminDown>     EvAdminDown;
      typedef EventTag<Event::EvNbrGoesDn>     EvNbrGoesDn;
      typedef EventTag<Event::EvHelloRcvd>     EvHelloRcvd;
      typedef EventTag<Event::EvHoldTimer>     EvHoldTimer;
      typedef EventTag<Event::EvSeqNumErr>     EvSeqNumErr;
      typedef EventTag<Event::EvReconfig>      EvReconfig;
      typedef EventTag<Event::EvConfRet>       EvConfRet;
      typedef EventTag<Event::EvHelloRet>      EvHelloRet;
      typedef EventTag<Event::EvDownTimer>     EvDownTimer;
    } // namespace appl
  } // namespace cc
} // namespace lmp


#endif /* LIBS_IPCC_EVENT_HPP_ */
