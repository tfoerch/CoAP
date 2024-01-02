/*
 * ObjectsGenerator.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectsGenerator_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::generator::objects_grammar<BufOutIterType>;

//namespace
//{
//  struct ObjTypes_GetLengthVisitor : boost::static_visitor<lmp::DWORD>
//  {
//    lmp::DWORD operator()(const lmp::obj::ccid::ControlChannelIdCTypes& controlChannelId) const
//    {
//      return lmp::obj::ccid::getLength(controlChannelId);
//    }
//    lmp::DWORD operator()(const lmp::obj::msgid::MessageIdCTypes& messageId) const
//    {
//      return lmp::obj::msgid::getLength(messageId);
//    }
//    lmp::DWORD operator()(const lmp::obj::nodeid::NodeIdCTypes& nodeId) const
//    {
//      return lmp::obj::nodeid::getLength(nodeId);
//    }
//    lmp::DWORD operator()(const lmp::obj::config::ConfigCTypes& config) const
//    {
//      return lmp::obj::config::getLength(config);
//    }
//    lmp::DWORD operator()(const lmp::obj::hello::HelloCTypes& hello) const
//    {
//      return lmp::obj::hello::getLength(hello);
//    }
//    lmp::DWORD operator()(const lmp::obj::UnknownObjectClassData& unknownObject) const
//    {
//      return lmp::obj::getLength(unknownObject);
//    }
//  };
//  struct Objects_Printer : boost::static_visitor<std::ostream&>
//  {
//    Objects_Printer(std::ostream& os)
//    : m_os(os)
//    {}
//    std::ostream& operator()(const lmp::obj::ccid::ControlChannelIdCTypes& controlChannelId) const
//    {
//      m_os << controlChannelId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::msgid::MessageIdCTypes& messageId) const
//    {
//      m_os << messageId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::nodeid::NodeIdCTypes& nodeId) const
//    {
//      m_os << nodeId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::config::ConfigCTypes& config) const
//    {
//      m_os << config;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::hello::HelloCTypes& hello) const
//    {
//      m_os << hello;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::UnknownObjectClassData& unknownObject) const
//    {
//      m_os << unknownObject;
//      return m_os;
//    }
//    std::ostream&   m_os;
//  };
//}
//
//lmp::DWORD lmp::obj::getLength(
//  const lmp::obj::Objects&  objects)
//{
//  return boost::apply_visitor(ObjTypes_GetLengthVisitor(), objects);
//}
//
//std::ostream& lmp::obj::operator<<(
//  std::ostream&             os,
//  const lmp::obj::Objects&  objects)
//{
//  boost::apply_visitor(Objects_Printer(os), objects);
//  return os;
//}
