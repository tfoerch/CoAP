/*
 * NodeIdCTypesGenerator.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdCTypesGenerator_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::nodeid::generator::node_id_ctypes_grammar<BufOutIterType>;

//namespace
//{
//  struct NodeIdCTypes_GetLengthVisitor : boost::static_visitor<lmp::DWORD>
//  {
//    lmp::DWORD operator()(const lmp::obj::nodeid::LocalNodeIdData& localNodeId) const
//    {
//      return lmp::obj::getLength(localNodeId);
//    }
//    lmp::DWORD operator()(const lmp::obj::nodeid::RemoteNodeIdData& remoteNodeId) const
//    {
//      return lmp::obj::getLength(remoteNodeId);
//    }
//    lmp::DWORD operator()(const lmp::obj::nodeid::UnknownNodeIdCTypeData& unknownNodeId) const
//    {
//      return lmp::obj::getLength(unknownNodeId);
//    }
//  };
//  struct NodeIdCTypes_Printer : boost::static_visitor<std::ostream&>
//  {
//    NodeIdCTypes_Printer(std::ostream& os)
//    : m_os(os)
//    {}
//    std::ostream& operator()(const lmp::obj::nodeid::LocalNodeIdData& localNodeId) const
//    {
//      m_os << localNodeId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::nodeid::RemoteNodeIdData& remoteNodeId) const
//    {
//      m_os << remoteNodeId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::nodeid::UnknownNodeIdCTypeData& unknownNodeId) const
//    {
//      m_os << unknownNodeId;
//      return m_os;
//    }
//    std::ostream&   m_os;
//  };
//}

//lmp::DWORD lmp::obj::nodeid::getLength(
//  const lmp::obj::nodeid::ast::NodeIdCTypes&  controlChannelIdCTypes)
//{
//  return boost::apply_visitor(NodeIdCTypes_GetLengthVisitor(), controlChannelIdCTypes);
//}
//
//std::ostream& lmp::obj::nodeid::operator<<(
//  std::ostream&                                  os,
//  const lmp::obj::nodeid::ast::NodeIdCTypes&  controlChannelIdCTypes)
//{
//  boost::apply_visitor(NodeIdCTypes_Printer(os), controlChannelIdCTypes);
//  return os;
//}
