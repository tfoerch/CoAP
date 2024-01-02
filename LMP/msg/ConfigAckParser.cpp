/*
 * ConfigAckParser.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigAckParser_def.hpp"
//#include "MessageType_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

//const lmp::msg::MsgType lmp::msg::MessageTypeTraits<lmp::msg::MsgType::ConfigAck>::msg_type_value = lmp::msg::MsgType::ConfigAck;
typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parser::config_ack_msg_grammar<BufIterType>;
//template struct lmp::msg::parse::message_type_grammar<BufIterType, lmp::msg::MsgType::ConfigAck>;

//namespace lmp
//{
//  namespace msg
//  {
//    namespace config_ack
//    {
//      lmp::WORD GetLengthFtor::operator()(
//        const ConfigAckBody&  configAckBody) const
//      {
//        return
//          ( lmp::obj::getLength(configAckBody.m_localCCId) +
//            lmp::obj::getLength(configAckBody.m_localNodeId) +
//            lmp::obj::getLength(configAckBody.m_remoteCCId) +
//            lmp::obj::getLength(configAckBody.m_messageId) +
//            lmp::obj::getLength(configAckBody.m_remoteNodeId) );
//      }
//      bool IsEqualFtor::operator()(
//        const ConfigAckBody&  first,
//        const ConfigAckBody&  second) const
//      {
//        return
//          ( first.m_localCCId == second.m_localCCId &&
//            first.m_localNodeId == second.m_localNodeId &&
//            first.m_remoteCCId == second.m_remoteCCId &&
//            first.m_messageId == second.m_messageId &&
//            first.m_remoteNodeId == second.m_remoteNodeId );
//      }
//      std::ostream& operator<<(
//        std::ostream&      os,
//        const ConfigAckBody&  configAckBody)
//      {
//        std::cout << configAckBody.m_localCCId
//                  << ", " << configAckBody.m_localNodeId
//                  << ", " << configAckBody.m_remoteCCId
//                  << ", " << configAckBody.m_messageId
//                  << ", " << configAckBody.m_remoteNodeId;
//        return os;
//      }
//    }
//  } // namespace msg
//} // namespace lmp
