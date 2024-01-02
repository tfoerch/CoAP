/*
 * IPCC_State.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "IPCC_State.hpp"
#include "base/ProtocolTypes.hpp"             // for DWORD

namespace lmp
{
  namespace cc
  {
    namespace appl
    {
      std::ostream& operator<<(
        std::ostream&  os,
        State::Type    stType)
      {
        switch(stType)
        {
          case State::Down:
            os << "Down";
            break;
          case State::ConfSnd:
            os << "ConfSnd";
            break;
          case State::ConfRcv:
            os << "ConfRcv";
            break;
          case State::Active:
            os << "Active";
            break;
          case State::Up:
            os << "Up";
            break;
          case State::GoingDown:
            os << "GoingDown";
            break;
          default:
            os << "undefined (value = " << static_cast<lmp::DWORD>(stType) << ")";
            break;
        }
        return os;
      }
    }
  } // namespace cc
} // namespace lmp
