#ifndef LMP_MSG_CONFIG_AST_ADAPTED_HPP_
#define LMP_MSG_CONFIG_AST_ADAPTED_HPP_
/*
 * ConfigAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "ConfigAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>



BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::ast::Config,
  (lmp::msg::ast::CommonHeaderFlags,             m_header)
  (lmp::obj::ccid::ast::LocalCCId,               m_localCCId)
  (lmp::obj::msgid::ast::MessageId,              m_messageId)
  (lmp::obj::nodeid::ast::LocalNodeId,           m_localNodeId)
  (lmp::obj::config::ast::ConfigObjectSequence,  m_configObjects)
)

#endif /* LMP_MSG_CONFIG_AST_ADAPTED_HPP_ */
