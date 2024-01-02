#ifndef LMP_MSG_CONFIG_AST_HPP_
#define LMP_MSG_CONFIG_AST_HPP_
/*
 * ConfigAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageType.hpp"
#include "msg/CommonHeaderAst.hpp"
#include "obj/LocalCCIdAst.hpp"
#include "obj/MessageIdAst.hpp"
#include "obj/LocalNodeIdAst.hpp"
#include "obj/ConfigObjectSequenceAst.hpp"

namespace lmp
{
  namespace msg
  {
    template <>
    struct MessageTypeTraits<MsgType::Config>
    {
      typedef MsgType                 message_type;
      static const message_type       msg_type_value; // = MsgType::Config;
    };
    namespace ast
    {
      struct Config
      {
        lmp::msg::ast::CommonHeaderFlags             m_header;
        lmp::obj::ccid::ast::LocalCCId               m_localCCId;
        lmp::obj::msgid::ast::MessageId              m_messageId;
        lmp::obj::nodeid::ast::LocalNodeId           m_localNodeId;
        lmp::obj::config::ast::ConfigObjectSequence  m_configObjects;
      };
      std::ostream& operator<<(
        std::ostream&      os,
        const Config&      config);
      bool operator==(
        const Config&      first,
        const Config&      second);
      lmp::WORD getLength(
        const Config&      config);
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_AST_HPP_ */
