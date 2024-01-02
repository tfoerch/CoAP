/*
 * ConfigNackAst.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigNackAst.hpp"

namespace lmp
{
  namespace msg
  {
    namespace ast
    {
      lmp::WORD getLength(
        const ConfigNack&  configNack)
      {
        return
          ( lmp::msg::c_headerLength +
            lmp::obj::ast::getLength(configNack.m_localCCId) +
            lmp::obj::ast::getLength(configNack.m_localNodeId) +
            lmp::obj::ast::getLength(configNack.m_remoteCCId) +
            lmp::obj::ast::getLength(configNack.m_messageId) +
            lmp::obj::ast::getLength(configNack.m_remoteNodeId) +
            lmp::obj::ast::getLength(configNack.m_helloConfig) );
      }
      bool operator==(
        const ConfigNack&  first,
        const ConfigNack&  second)
      {
        return
//          ( first.m_localCCId == second.m_localCCId &&
//            first.m_localNodeId == second.m_localNodeId &&
//            first.m_remoteCCId == second.m_remoteCCId &&
//            first.m_messageId == second.m_messageId &&
//            first.m_remoteNodeId == second.m_remoteNodeId &&
//            first.m_helloConfig == second.m_helloConfig );
            true;
      }
      std::ostream& operator<<(
        std::ostream&      os,
        const ConfigNack&  configNack)
      {
//        std::cout << configNack.m_localCCId
//                  << ", " << configNack.m_localNodeId
//                  << ", " << configNack.m_remoteCCId
//                  << ", " << configNack.m_messageId
//                  << ", " << configNack.m_remoteNodeId
//                  << ", " << configNack.m_helloConfig;
        return os;
      }
    }
  } // namespace msg
} // namespace lmp
