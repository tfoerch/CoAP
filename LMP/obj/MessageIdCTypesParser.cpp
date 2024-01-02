/*
 * MessageIdCTypesParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdCTypesParser_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

namespace lmp
{
  namespace obj
  {
    namespace msgid
    {
      namespace parser
      {
        typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
        template struct lmp::obj::msgid::parser::message_id_ctypes_grammar<BufIterType>;
      }
    }
  }
}

//namespace
//{
//  struct MessageIdCTypes_GetLengthVisitor : boost::static_visitor<lmp::DWORD>
//  {
//    lmp::DWORD operator()(const lmp::obj::msgid::MessageIdData& messageId) const
//    {
//      return lmp::obj::getLength(messageId);
//    }
//    lmp::DWORD operator()(const lmp::obj::msgid::MessageIdAckData& messageAckId) const
//    {
//      return lmp::obj::getLength(messageAckId);
//    }
//    lmp::DWORD operator()(const lmp::obj::msgid::UnknownMessageIdCTypeData& unknownMessageId) const
//    {
//      return lmp::obj::getLength(unknownMessageId);
//    }
//  };
//  struct MessageIdCTypes_Printer : boost::static_visitor<std::ostream&>
//  {
//    MessageIdCTypes_Printer(std::ostream& os)
//    : m_os(os)
//    {}
//    std::ostream& operator()(const lmp::obj::msgid::MessageIdData& messageId) const
//    {
//      m_os << messageId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::msgid::MessageIdAckData& messageAckId) const
//    {
//      m_os << messageAckId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::msgid::UnknownMessageIdCTypeData& unknownMessageId) const
//    {
//      m_os << unknownMessageId;
//      return m_os;
//    }
//    std::ostream&   m_os;
//  };
//}
//
//lmp::DWORD lmp::obj::msgid::getLength(
//  const lmp::obj::msgid::MessageIdCTypes&  messageIdCTypes)
//{
//  return boost::apply_visitor(MessageIdCTypes_GetLengthVisitor(), messageIdCTypes);
//}
//
//std::ostream& lmp::obj::msgid::operator<<(
//  std::ostream&                                  os,
//  const lmp::obj::msgid::MessageIdCTypes&        messageIdCTypes)
//{
//  boost::apply_visitor(MessageIdCTypes_Printer(os), messageIdCTypes);
//  return os;
//}
