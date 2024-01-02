/*
 * ConfigAst.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigAst.hpp"

namespace lmp
{
  namespace msg
  {
    namespace ast
    {
      lmp::WORD getLength(
        const Config&  config)
      {
        return
          ( lmp::msg::c_headerLength +
            lmp::obj::ast::getLength(config.m_localCCId) +
            lmp::obj::ast::getLength(config.m_messageId) +
            lmp::obj::ast::getLength(config.m_localNodeId) +
            lmp::obj::ast::getLength(config.m_configObjects) );
      }
      bool operator==(
        const Config&  first,
        const Config&  second)
      {
        return
//          ( first.m_localCCId == second.m_localCCId &&
//            first.m_messageId == second.m_messageId &&
//            first.m_localNodeId == second.m_localNodeId &&
//            first.m_configObjects == second.m_configObjects );
            true;
      }
      std::ostream& operator<<(
        std::ostream&  os,
        const Config&  config)
      {
//        std::cout << config.m_localCCId
//                  << ", " << config.m_messageId
//                  << ", " << config.m_localNodeId
//                  << ", " << config.m_configObjects;
        return os;
      }
    }
  } // namespace msg
} // namespace lmp
