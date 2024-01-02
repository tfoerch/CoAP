#ifndef LMP_MSG_CONFIGNACK_AST_HPP_
#define LMP_MSG_CONFIGNACK_AST_HPP_
/*
 * ConfigNackAst.hpp
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
#include "obj/HelloConfigAst.hpp"

namespace lmp
{
  namespace msg
  {
    template <>
    struct MessageTypeTraits<MsgType::ConfigNack>
    {
      typedef MsgType                 message_type;
      static const message_type       msg_type_value; // = MsgType::ConfigNack;
    };
    namespace ast
    {
      struct ConfigNack
      {
        lmp::msg::ast::CommonHeaderFlags         m_header;
        lmp::obj::ccid::ast::LocalCCId           m_localCCId;
        lmp::obj::nodeid::ast::LocalNodeId       m_localNodeId;
        lmp::obj::ccid::ast::RemoteCCId          m_remoteCCId;
        lmp::obj::msgid::ast::MessageIdAck       m_messageId;
        lmp::obj::nodeid::ast::RemoteNodeId      m_remoteNodeId;
        lmp::obj::config::ast::HelloConfig       m_helloConfig;
      };
      std::ostream& operator<<(
        std::ostream&          os,
        const ConfigNack&  configNack);
      bool operator==(
        const ConfigNack&   first,
        const ConfigNack&   second);
      lmp::WORD getLength(
        const ConfigNack&      configNack);
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGNACK_AST_HPP_ */
