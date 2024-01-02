/*
 * MessageIdCTypesAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdCTypesAst.hpp"

namespace
{
  struct MessageIdCTypes_GetBodyLengthVisitor : boost::static_visitor<lmp::DWORD>
  {
    lmp::DWORD operator()(const lmp::obj::msgid::ast::MessageId& messageId) const
    {
      return lmp::obj::ast::getBodyLength(messageId);
    }
    lmp::DWORD operator()(const lmp::obj::msgid::ast::MessageIdAck& messageIdAck) const
    {
      return lmp::obj::ast::getBodyLength(messageIdAck);
    }
    lmp::DWORD operator()(const lmp::obj::msgid::ast::UnknownMessageIdCType& unknownMessageId) const
    {
      return lmp::obj::getBodyLength(unknownMessageId);
    }
  };
  struct MessageIdCTypes_Printer : boost::static_visitor<std::ostream&>
  {
    MessageIdCTypes_Printer(std::ostream& os)
    : m_os(os)
    {}
    std::ostream& operator()(const lmp::obj::msgid::ast::MessageId& messageId) const
    {
      m_os << messageId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::msgid::ast::MessageIdAck& messageIdAck) const
    {
      m_os << messageIdAck;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::msgid::ast::UnknownMessageIdCType& unknownMessageId) const
    {
      m_os << unknownMessageId;
      return m_os;
    }
    std::ostream&   m_os;
  };
}

namespace lmp
{
  namespace obj
  {
    namespace msgid
    {
      namespace ast
      {
        std::ostream& operator<<(
          std::ostream&                  os,
          const MessageIdCTypes&  msgidCType)
        {
          boost::apply_visitor(MessageIdCTypes_Printer(os), msgidCType);
          return os;
        }
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<msgid::ast::MessageIdCTypes>(
        const msgid::ast::MessageIdCTypes&  msgidCType)
      {
        return boost::apply_visitor(MessageIdCTypes_GetBodyLengthVisitor(), msgidCType);
      }
    }
  }
}
