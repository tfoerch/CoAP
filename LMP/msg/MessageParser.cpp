/*
 * Message.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageParser_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parser::message_grammar<BufIterType>;

//namespace
//{
//  struct MsgTypes_GetLengthVisitor : boost::static_visitor<lmp::DWORD>
//  {
//    lmp::DWORD operator()(const lmp::msg::ConfigMsg& config) const
//    {
//      return lmp::msg::getLength(config);
//    }
//    lmp::DWORD operator()(const lmp::msg::ConfigAckMsg& configAck) const
//    {
//      return lmp::msg::getLength(configAck);
//    }
//    lmp::DWORD operator()(const lmp::msg::ConfigNackMsg& configNack) const
//    {
//      return lmp::msg::getLength(configNack);
//    }
//    lmp::DWORD operator()(const lmp::msg::HelloMsg& hello) const
//    {
//      return lmp::msg::getLength(hello);
//    }
//    lmp::DWORD operator()(const lmp::msg::UnknownMessage& unknownMessage) const
//    {
//      return lmp::msg::getLength(unknownMessage);
//    }
//  };
//  struct msg_variants_printer : boost::static_visitor<std::ostream&>
//  {
//    msg_variants_printer(std::ostream& os)
//    : m_os(os)
//	{}
//    std::ostream& operator()(const lmp::msg::ConfigMsg& config) const
//    {
//	  m_os << config << std::endl;
//	  return m_os;
//    }
//    std::ostream& operator()(const lmp::msg::ConfigAckMsg& configAck) const
//    {
//	  m_os << configAck << std::endl;
//	  return m_os;
//    }
//    std::ostream& operator()(const lmp::msg::ConfigNackMsg& configNack) const
//    {
//	  m_os << configNack << std::endl;
//	  return m_os;
//    }
//    std::ostream& operator()(const lmp::msg::HelloMsg& hello) const
//    {
//	  m_os << hello << std::endl;
//	  return m_os;
//    }
//    std::ostream& operator()(const lmp::msg::UnknownMessage& unknownMessage) const
//    {
//	  m_os << unknownMessage << std::endl;
//	  return m_os;
//    }
//    std::ostream&   m_os;
//  };
//}
//
//namespace lmp
//{
//  namespace msg
//  {
//    lmp::DWORD getLength(
//      const Message&  message)
//    {
//      return boost::apply_visitor(MsgTypes_GetLengthVisitor(), message);
//    }
//    std::ostream& operator<<(
//      std::ostream&    os,
//      const Message&   message)
//    {
//      boost::apply_visitor(msg_variants_printer(os), message);
//      return os;
//    }
//  } // namespace msg
//} // namespace lmp
