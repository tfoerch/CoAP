/*
 * HelloCTypesGenerator.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloCTypesGenerator_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::hello::generator::hello_ctypes_grammar<BufOutIterType>;

//namespace
//{
//  struct HelloCTypes_GetLengthVisitor : boost::static_visitor<lmp::DWORD>
//  {
//    lmp::DWORD operator()(const lmp::obj::hello::HelloData& localCCId) const
//    {
//      return lmp::obj::getLength(localCCId);
//    }
//    lmp::DWORD operator()(const lmp::obj::hello::RemoteCCIdData& remoteCCId) const
//    {
//      return lmp::obj::getLength(remoteCCId);
//    }
//    lmp::DWORD operator()(const lmp::obj::hello::UnknownCCIdCTypeData& unknownCCId) const
//    {
//      return lmp::obj::getLength(unknownCCId);
//    }
//  };
//  struct HelloCTypes_Printer : boost::static_visitor<std::ostream&>
//  {
//    HelloCTypes_Printer(std::ostream& os)
//    : m_os(os)
//    {}
//    std::ostream& operator()(const lmp::obj::hello::HelloData& localCCId) const
//    {
//      m_os << localCCId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::hello::RemoteCCIdData& remoteCCId) const
//    {
//      m_os << remoteCCId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::hello::UnknownCCIdCTypeData& unknownCCId) const
//    {
//      m_os << unknownCCId;
//      return m_os;
//    }
//    std::ostream&   m_os;
//  };
//}

//lmp::DWORD lmp::obj::hello::getLength(
//  const lmp::obj::hello::ast::HelloCTypes&  controlChannelIdCTypes)
//{
//  return boost::apply_visitor(HelloCTypes_GetLengthVisitor(), controlChannelIdCTypes);
//}
//
//std::ostream& lmp::obj::hello::operator<<(
//  std::ostream&                                  os,
//  const lmp::obj::hello::ast::HelloCTypes&  controlChannelIdCTypes)
//{
//  boost::apply_visitor(HelloCTypes_Printer(os), controlChannelIdCTypes);
//  return os;
//}
