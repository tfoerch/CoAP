/*
 * ControlChannelIdCTypesAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdCTypesAst.hpp"

namespace
{
  struct ControlChannelIdCTypes_GetBodyLengthVisitor : boost::static_visitor<lmp::DWORD>
  {
    lmp::DWORD operator()(const lmp::obj::ccid::ast::LocalCCId& localControlChannelId) const
    {
      return lmp::obj::ast::getBodyLength(localControlChannelId);
    }
    lmp::DWORD operator()(const lmp::obj::ccid::ast::RemoteCCId& remoteControlChannelId) const
    {
      return lmp::obj::ast::getBodyLength(remoteControlChannelId);
    }
    lmp::DWORD operator()(const lmp::obj::ccid::ast::UnknownCCIdCType& unknownControlChannelId) const
    {
      return lmp::obj::getBodyLength(unknownControlChannelId);
    }
  };
  struct ControlChannelIdCTypes_Printer : boost::static_visitor<std::ostream&>
  {
    ControlChannelIdCTypes_Printer(std::ostream& os)
    : m_os(os)
    {}
    std::ostream& operator()(const lmp::obj::ccid::ast::LocalCCId& localControlChannelId) const
    {
      m_os << localControlChannelId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::ccid::ast::RemoteCCId& remoteControlChannelId) const
    {
      m_os << remoteControlChannelId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::ccid::ast::UnknownCCIdCType& unknownControlChannelId) const
    {
      m_os << unknownControlChannelId;
      return m_os;
    }
    std::ostream&   m_os;
  };
}

namespace lmp
{
  namespace obj
  {
    namespace ccid
    {
      namespace ast
      {
        std::ostream& operator<<(
          std::ostream&                  os,
          const ControlChannelIdCTypes&  ccidCType)
        {
          boost::apply_visitor(ControlChannelIdCTypes_Printer(os), ccidCType);
          return os;
        }
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<ccid::ast::ControlChannelIdCTypes>(
        const ccid::ast::ControlChannelIdCTypes&  ccidCType)
      {
        return boost::apply_visitor(ControlChannelIdCTypes_GetBodyLengthVisitor(), ccidCType);
      }
    }
  }
}
