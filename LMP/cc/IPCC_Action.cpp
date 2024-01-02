/*
 * IPCC_Action.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "IPCC_Action.hpp"
#include "base/ProtocolTypes.hpp"             // for DWORD

namespace lmp
{
  namespace cc
  {
    namespace appl
    {
      std::ostream& operator<<(
        std::ostream&       os,
        Action::ActionType  actionType)
      {
        switch(actionType)
        {
          case Action::ActionSendConfig:
            os << "SendConfig";
            break;
          case Action::ActionStopSendConfig:
            os << "StopSendConfig";
            break;
          case Action::ActionResendConfig:
            os << "ResendConfig";
            break;
          case Action::ActionSendConfigAck:
            os << "SendConfigAck";
            break;
          case Action::ActionSendConfigNack:
            os << "SendConfigNack";
            break;
          case Action::ActionSendHello:
            os << "SendHello";
            break;
          case Action::ActionStopSendHello:
            os << "StopSendHello";
            break;
          case Action::ActionSetCCDownFlag:
            os << "SetCCDownFlag";
            break;
          case Action::ActionClearCCDownFlag:
            os << "ClearCCDownFlag";
            break;
          case Action::ActionNoAction:
            os << "NoAction";
            break;
          default:
            os << "undefined (value = " << static_cast<lmp::DWORD>(actionType) << ")";
            break;
        }
        return os;
      }
    }
  } // namespace cc
} // namespace lmp
