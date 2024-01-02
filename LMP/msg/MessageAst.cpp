/*
 * MessageAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageAst.hpp"

namespace
{
  struct MsgTypes_GetLengthVisitor : boost::static_visitor<lmp::WORD>
  {
    lmp::WORD operator()(const lmp::msg::ast::Config& config) const
    {
      return lmp::msg::ast::getLength(config);
    }
    lmp::WORD operator()(const lmp::msg::ast::ConfigAck& configAck) const
    {
      return lmp::msg::ast::getLength(configAck);
    }
    lmp::WORD operator()(const lmp::msg::ast::ConfigNack& configNack) const
    {
      return lmp::msg::ast::getLength(configNack);
    }
    lmp::WORD operator()(const lmp::msg::ast::Hello& hello) const
    {
      return lmp::msg::ast::getLength(hello);
    }
    lmp::WORD operator()(const lmp::msg::ast::UnknownMessage& unknownMessage) const
    {
      return lmp::msg::ast::getLength(unknownMessage);
    }
  };
  struct msg_variants_printer : boost::static_visitor<std::ostream&>
  {
    msg_variants_printer(std::ostream& os)
    : m_os(os)
	{}
    std::ostream& operator()(const lmp::msg::ast::Config& config) const
    {
	  m_os << config << std::endl;
	  return m_os;
    }
    std::ostream& operator()(const lmp::msg::ast::ConfigAck& configAck) const
    {
	  m_os << configAck << std::endl;
	  return m_os;
    }
    std::ostream& operator()(const lmp::msg::ast::ConfigNack& configNack) const
    {
	  m_os << configNack << std::endl;
	  return m_os;
    }
    std::ostream& operator()(const lmp::msg::ast::Hello& hello) const
    {
	  m_os << hello << std::endl;
	  return m_os;
    }
    std::ostream& operator()(const lmp::msg::ast::UnknownMessage& unknownMessage) const
    {
	  m_os << unknownMessage << std::endl;
	  return m_os;
    }
    std::ostream&   m_os;
  };
}

namespace lmp
{
  namespace msg
  {
    namespace ast
    {
      lmp::WORD getLength(
        const Message&  message)
      {
        return boost::apply_visitor(MsgTypes_GetLengthVisitor(), message);
      }
      std::ostream& operator<<(
        std::ostream&    os,
        const Message&   message)
      {
        boost::apply_visitor(msg_variants_printer(os), message);
        return os;
      }
    }
  } // namespace msg
} // namespace lmp
