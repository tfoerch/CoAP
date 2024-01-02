/*
 * NodeIdCTypesAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdCTypesAst.hpp"

namespace
{
  struct NodeIdCTypes_GetBodyLengthVisitor : boost::static_visitor<lmp::DWORD>
  {
    lmp::DWORD operator()(const lmp::obj::nodeid::ast::LocalNodeId& localNodeId) const
    {
      return lmp::obj::ast::getBodyLength(localNodeId);
    }
    lmp::DWORD operator()(const lmp::obj::nodeid::ast::RemoteNodeId& remoteNodeId) const
    {
      return lmp::obj::ast::getBodyLength(remoteNodeId);
    }
    lmp::DWORD operator()(const lmp::obj::nodeid::ast::UnknownNodeIdCType& unknownNodeId) const
    {
      return lmp::obj::getBodyLength(unknownNodeId);
    }
  };
  struct NodeIdCTypes_Printer : boost::static_visitor<std::ostream&>
  {
    NodeIdCTypes_Printer(std::ostream& os)
    : m_os(os)
    {}
    std::ostream& operator()(const lmp::obj::nodeid::ast::LocalNodeId& localNodeId) const
    {
      m_os << localNodeId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::nodeid::ast::RemoteNodeId& remoteNodeId) const
    {
      m_os << remoteNodeId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::nodeid::ast::UnknownNodeIdCType& unknownNodeId) const
    {
      m_os << unknownNodeId;
      return m_os;
    }
    std::ostream&   m_os;
  };
}

namespace lmp
{
  namespace obj
  {
    namespace nodeid
    {
      namespace ast
      {
        std::ostream& operator<<(
          std::ostream&        os,
          const NodeIdCTypes&  nodeidCType)
        {
          boost::apply_visitor(NodeIdCTypes_Printer(os), nodeidCType);
          return os;
        }
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<nodeid::ast::NodeIdCTypes>(
        const nodeid::ast::NodeIdCTypes&  nodeidCType)
      {
        return boost::apply_visitor(NodeIdCTypes_GetBodyLengthVisitor(), nodeidCType);
      }
    }
  }
}
