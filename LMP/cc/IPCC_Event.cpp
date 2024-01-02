/*
 * IPCC_Event.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "IPCC_Event.hpp"
#include "base/ProtocolTypes.hpp"             // for DWORD

namespace lmp
{
  namespace cc
  {
    namespace appl
    {
      std::ostream& operator<<(
        std::ostream&  os,
        Event::EvType  evType)
      {
        switch(evType)
        {
          case Event::EvBringUp:
            os << "EvBringUp";
            break;
          case Event::EvCCDn:
            os << "EvCCDn";
            break;
          case Event::EvConfDone:
            os << "EvConfDone";
            break;
          case Event::EvConfErr:
            os << "EvConfErr";
            break;
          case Event::EvNewConfOK:
            os << "EvNewConfOK";
            break;
          case Event::EvNewConfErr:
            os << "EvNewConfErr";
            break;
          case Event::EvContenWin:
            os << "EvContenWin";
            break;
          case Event::EvContenLost:
            os << "EvContenLost";
            break;
          case Event::EvAdminDown:
            os << "EvAdminDown";
            break;
          case Event::EvNbrGoesDn:
            os << "EvNbrGoesDn";
            break;
          case Event::EvHelloRcvd:
            os << "EvHelloRcvd";
            break;
          case Event::EvHoldTimer:
            os << "EvHoldTimer";
            break;
          case Event::EvSeqNumErr:
            os << "EvSeqNumErr";
            break;
          case Event::EvReconfig:
            os << "EvReconfig";
            break;
          case Event::EvConfRet:
            os << "EvConfRet";
            break;
          case Event::EvHelloRet:
            os << "EvHelloRet";
            break;
          case Event::EvDownTimer:
            os << "EvDownTimer";
            break;
          default:
            os << "undefined (value = " << static_cast<lmp::DWORD>(evType) << ")";
            break;
        }
        return os;
      }
    }
  } // namespace cc
} // namespace lmp
