/*
 * ConfigNackParser.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigNackParser_def.hpp"
//#include "MessageType_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

//const lmp::msg::MsgType lmp::msg::MessageTypeTraits<lmp::msg::MsgType::ConfigNack>::msg_type_value = lmp::msg::MsgType::ConfigNack;
typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parser::config_nack_msg_grammar<BufIterType>;
//template struct lmp::msg::parse::message_type_grammar<BufIterType, lmp::msg::MsgType::ConfigNack>;

//namespace lmp
//{
//  namespace msg
//  {
//    namespace config_nack
//    {
//      lmp::WORD GetLengthFtor::operator()(
//        const ConfigNackBody&  configNackBody) const
//      {
//        return
//          ( lmp::obj::getLength(configNackBody.m_localCCId) +
//            lmp::obj::getLength(configNackBody.m_localNodeId) +
//            lmp::obj::getLength(configNackBody.m_remoteCCId) +
//            lmp::obj::getLength(configNackBody.m_messageId) +
//            lmp::obj::getLength(configNackBody.m_remoteNodeId) +
//            lmp::obj::getLength(configNackBody.m_helloConfig) );
//      }
//      bool IsEqualFtor::operator()(
//        const ConfigNackBody&  first,
//        const ConfigNackBody&  second) const
//      {
//        return
//          ( first.m_localCCId == second.m_localCCId &&
//            first.m_localNodeId == second.m_localNodeId &&
//            first.m_remoteCCId == second.m_remoteCCId &&
//            first.m_messageId == second.m_messageId &&
//            first.m_remoteNodeId == second.m_remoteNodeId &&
//            first.m_helloConfig == second.m_helloConfig );
//      }
//      std::ostream& operator<<(
//        std::ostream&      os,
//        const ConfigNackBody&  configNackBody)
//      {
//        std::cout << configNackBody.m_localCCId
//                  << ", " << configNackBody.m_localNodeId
//                  << ", " << configNackBody.m_remoteCCId
//                  << ", " << configNackBody.m_messageId
//                  << ", " << configNackBody.m_remoteNodeId
//                  << ", " << configNackBody.m_helloConfig;
//        return os;
//      }
//    }
//  } // namespace msg
//} // namespace lmp
