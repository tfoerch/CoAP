#ifndef LMP_MSG_CONFIGACK_AST_HPP_
#define LMP_MSG_CONFIGACK_AST_HPP_
/*
 * ConfigAckAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageType.hpp"
#include "msg/CommonHeaderAst.hpp"
#include "obj/LocalCCIdAst.hpp"
#include "obj/LocalNodeIdAst.hpp"
#include "obj/RemoteCCIdAst.hpp"
#include "obj/MessageIdAckAst.hpp"
#include "obj/RemoteNodeIdAst.hpp"

namespace lmp
{
  namespace msg
  {
    template <>
    struct MessageTypeTraits<MsgType::ConfigAck>
    {
      typedef MsgType                 message_type;
      static const message_type       msg_type_value; // = MsgType::ConfigAck;
    };
    namespace ast
    {
      struct ConfigAck
      {
        lmp::msg::ast::CommonHeaderFlags         m_header;
        lmp::obj::ccid::ast::LocalCCId           m_localCCId;
        lmp::obj::nodeid::ast::LocalNodeId       m_localNodeId;
        lmp::obj::ccid::ast::RemoteCCId          m_remoteCCId;
        lmp::obj::msgid::ast::MessageIdAck       m_messageId;
        lmp::obj::nodeid::ast::RemoteNodeId      m_remoteNodeId;
      };
      std::ostream& operator<<(
        std::ostream&         os,
        const ConfigAck&      configAck);
      bool operator==(
        const ConfigAck&   first,
        const ConfigAck&   second);
      lmp::WORD getLength(
        const ConfigAck&      configAck);
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGACK_AST_HPP_ */
