/*
 * ConfigParser.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigParser_def.hpp"
//#include "MessageType_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

//const lmp::msg::MsgType lmp::msg::MessageTypeTraits<lmp::msg::MsgType::Config>::msg_type_value = lmp::msg::MsgType::Config;
typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parser::config_msg_grammar<BufIterType>;
//template struct lmp::msg::parse::message_type_grammar<BufIterType, lmp::msg::MsgType::Config>;

//namespace lmp
//{
//  namespace msg
//  {
//    namespace config
//    {
//      lmp::WORD GetLengthFtor::operator()(
//        const ast::Config&  configMsg) const
//      {
//        return
//          ( lmp::obj::getLength(configMsg.m_localCCId) +
//            lmp::obj::getLength(configMsg.m_messageId) +
//            lmp::obj::getLength(configMsg.m_localNodeId) +
//            lmp::obj::config::getLength(configMsg.m_configObjects) );
//      }
//      bool IsEqualFtor::operator()(
//        const ast::Config&  first,
//        const ast::Config&  second) const
//      {
//        return
//          ( first.m_localCCId == second.m_localCCId &&
//            first.m_messageId == second.m_messageId &&
//            first.m_localNodeId == second.m_localNodeId &&
//            first.m_configObjects == second.m_configObjects );
//      }
//      std::ostream& operator<<(
//        std::ostream&      os,
//        const ast::Config&  configMsg)
//      {
//        std::cout << configMsg.m_localCCId
//                  << ", " << configMsg.m_messageId
//                  << ", " << configMsg.m_localNodeId
//                  << ", " << configMsg.m_configObjects;
//        return os;
//      }
//    }
//  } // namespace msg
//} // namespace lmp
