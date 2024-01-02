/*
 * ConfigAckAst.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigAckAst.hpp"

namespace lmp
{
  namespace msg
  {
    namespace ast
    {
      lmp::WORD getLength(
        const ConfigAck&  configAck)
      {
        return
          ( lmp::msg::c_headerLength +
            lmp::obj::ast::getLength(configAck.m_localCCId) +
            lmp::obj::ast::getLength(configAck.m_localNodeId) +
            lmp::obj::ast::getLength(configAck.m_remoteCCId) +
            lmp::obj::ast::getLength(configAck.m_messageId) +
            lmp::obj::ast::getLength(configAck.m_remoteNodeId) );
      }
      bool operator==(
        const ConfigAck&  first,
        const ConfigAck&  second)
      {
        return
//          ( first.m_localCCId == second.m_localCCId &&
//            first.m_localNodeId == second.m_localNodeId &&
//            first.m_remoteCCId == second.m_remoteCCId &&
//            first.m_messageId == second.m_messageId &&
//            first.m_remoteNodeId == second.m_remoteNodeId );
            true;
      }
      std::ostream& operator<<(
        std::ostream&     os,
        const ConfigAck&  configAck)
      {
//        std::cout << configAck.m_localCCId
//                  << ", " << configAck.m_localNodeId
//                  << ", " << configAck.m_remoteCCId
//                  << ", " << configAck.m_messageId
//                  << ", " << configAck.m_remoteNodeId;
        return os;
      }
    }
  } // namespace msg
} // namespace lmp
