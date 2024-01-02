/*
 * ConfigGenerator.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigGenerator_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

//const lmp::msg::MsgType lmp::msg::MessageTypeTraits<lmp::msg::MsgType::Config>::msg_type_value = lmp::msg::MsgType::Config;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::msg::generator::config_msg_grammar<BufOutIterType>;

//namespace lmp
//{
//  namespace msg
//  {
//    namespace config
//    {
//      lmp::WORD GetLengthFtor::operator()(
//        const ConfigBody&  configBody) const
//      {
//        return
//          ( lmp::obj::getLength(configBody.m_localCCId) +
//            lmp::obj::getLength(configBody.m_messageId) +
//            lmp::obj::getLength(configBody.m_localNodeId) +
//            lmp::obj::config::getLength(configBody.m_configObjects) );
//      }
//      bool IsEqualFtor::operator()(
//        const ConfigBody&  first,
//        const ConfigBody&  second) const
//      {
//        return
//          ( first.m_localCCId == second.m_localCCId &&
//            first.m_messageId == second.m_messageId &&
//            first.m_localNodeId == second.m_localNodeId &&
//            first.m_configObjects == second.m_configObjects );
//      }
//      std::ostream& operator<<(
//        std::ostream&      os,
//        const ConfigBody&  configBody)
//      {
//        std::cout << configBody.m_localCCId
//                  << ", " << configBody.m_messageId
//                  << ", " << configBody.m_localNodeId
//                  << ", " << configBody.m_configObjects;
//        return os;
//      }
//    }
//  } // namespace msg
//} // namespace lmp
