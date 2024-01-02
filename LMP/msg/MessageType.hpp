#ifndef LMP_MSG_MESSAGE_TYPE_HPP_
#define LMP_MSG_MESSAGE_TYPE_HPP_
/*
 * MessageType.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include <iostream>

namespace lmp
{
  namespace msg
  {
    enum class MsgType : lmp::BYTE
    {
      Config = 1,
      ConfigAck,
      ConfigNack,
      Hello
    };
    std::ostream& operator<<(
      std::ostream&   os,
      const MsgType&  msgType);
    template <MsgType msgType>
    struct MessageTypeTraits
    {
      typedef MsgType            message_type;
      static const message_type  msg_type_value = msgType;
    };
    namespace ast
    {
      template <typename   MessageType>
      lmp::WORD getLength(
        const MessageType&  message);
      template <typename   MessageType>
      struct GetLength
      {
        template<typename> struct result { typedef lmp::WORD type; };
        lmp::WORD operator()(
          const MessageType&  message) const
        {
          return getLength(message);
        }
      };
    }
    const lmp::WORD  c_headerLength = 8;
    const lmp::BYTE  c_versionMask = 0xf0;
    const lmp::BYTE  c_supportedVersion = 1;
    const lmp::BYTE  c_controlChannelDownMask = 0x01;
    const lmp::BYTE  c_lmpRestartMask = 0x02;
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_MESSAGE_TYPE_HPP_ */
