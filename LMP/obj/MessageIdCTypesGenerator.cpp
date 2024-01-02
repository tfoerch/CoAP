/*
 * MessageIdCTypesGenerator.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdCTypesGenerator_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::msgid::generator::message_id_ctypes_grammar<BufOutIterType>;

//namespace
//{
//  struct MessageIdCTypes_GetLengthVisitor : boost::static_visitor<lmp::DWORD>
//  {
//    lmp::DWORD operator()(const lmp::obj::msgid::LocalCCIdData& localCCId) const
//    {
//      return lmp::obj::getLength(localCCId);
//    }
//    lmp::DWORD operator()(const lmp::obj::msgid::RemoteCCIdData& remoteCCId) const
//    {
//      return lmp::obj::getLength(remoteCCId);
//    }
//    lmp::DWORD operator()(const lmp::obj::msgid::UnknownCCIdCTypeData& unknownCCId) const
//    {
//      return lmp::obj::getLength(unknownCCId);
//    }
//  };
//  struct MessageIdCTypes_Printer : boost::static_visitor<std::ostream&>
//  {
//    MessageIdCTypes_Printer(std::ostream& os)
//    : m_os(os)
//    {}
//    std::ostream& operator()(const lmp::obj::msgid::LocalCCIdData& localCCId) const
//    {
//      m_os << localCCId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::msgid::RemoteCCIdData& remoteCCId) const
//    {
//      m_os << remoteCCId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::msgid::UnknownCCIdCTypeData& unknownCCId) const
//    {
//      m_os << unknownCCId;
//      return m_os;
//    }
//    std::ostream&   m_os;
//  };
//}

//lmp::DWORD lmp::obj::msgid::getLength(
//  const lmp::obj::msgid::ast::MessageIdCTypes&  controlChannelIdCTypes)
//{
//  return boost::apply_visitor(MessageIdCTypes_GetLengthVisitor(), controlChannelIdCTypes);
//}
//
//std::ostream& lmp::obj::msgid::operator<<(
//  std::ostream&                                  os,
//  const lmp::obj::msgid::ast::MessageIdCTypes&  controlChannelIdCTypes)
//{
//  boost::apply_visitor(MessageIdCTypes_Printer(os), controlChannelIdCTypes);
//  return os;
//}
