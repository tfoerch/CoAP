/*
 * ObjectsAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectsAst.hpp"

namespace
{
  struct ObjTypes_GetBodyLengthVisitor : boost::static_visitor<lmp::DWORD>
  {
    lmp::DWORD operator()(const lmp::obj::ccid::ast::ControlChannelIdCTypes& controlChannelId) const
    {
      return lmp::obj::ast::getBodyLength(controlChannelId);
    }
    lmp::DWORD operator()(const lmp::obj::msgid::ast::MessageIdCTypes& messageId) const
    {
      return lmp::obj::ast::getBodyLength(messageId);
    }
    lmp::DWORD operator()(const lmp::obj::nodeid::ast::NodeIdCTypes& nodeId) const
    {
      return lmp::obj::ast::getBodyLength(nodeId);
    }
    lmp::DWORD operator()(const lmp::obj::config::ast::ConfigCTypes& config) const
    {
      return lmp::obj::ast::getBodyLength(config);
    }
    lmp::DWORD operator()(const lmp::obj::hello::ast::HelloCTypes& hello) const
    {
      return lmp::obj::ast::getBodyLength(hello);
    }
    lmp::DWORD operator()(const lmp::obj::ast::UnknownObjectClass& unknownObject) const
    {
      return lmp::obj::ast::getBodyLength(unknownObject);
    }
  };
  struct Objects_Printer : boost::static_visitor<std::ostream&>
  {
    Objects_Printer(std::ostream& os)
    : m_os(os)
    {}
    std::ostream& operator()(const lmp::obj::ccid::ast::ControlChannelIdCTypes& controlChannelId) const
    {
      m_os << controlChannelId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::msgid::ast::MessageIdCTypes& messageId) const
    {
      // m_os << messageId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::nodeid::ast::NodeIdCTypes& nodeId) const
    {
      //m_os << nodeId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::config::ast::ConfigCTypes& config) const
    {
      m_os << config;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::hello::ast::HelloCTypes& hello) const
    {
      //m_os << hello;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::ast::UnknownObjectClass& unknownObject) const
    {
      m_os << unknownObject;
      return m_os;
    }
    std::ostream&   m_os;
  };
}


namespace lmp
{
  namespace obj
  {
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<Objects>(
        const Objects&  objects)
      {
        return boost::apply_visitor(ObjTypes_GetBodyLengthVisitor(), objects);
      }

      std::ostream& operator<<(
        std::ostream&             os,
        const Objects&  objects)
      {
        boost::apply_visitor(Objects_Printer(os), objects);
        return os;
      }
    }
  } // namespace obj
} // namespace lmp
