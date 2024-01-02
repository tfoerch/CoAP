#ifndef LMP_MSG_CONFIGACK_AST_ADAPTED_HPP_
#define LMP_MSG_CONFIGACK_AST_ADAPTED_HPP_
/*
 * ConfigAckAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "ConfigAckAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>


BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::ast::ConfigAck,
  (lmp::msg::ast::CommonHeaderFlags,        m_header)
  (lmp::obj::ccid::ast::LocalCCId,          m_localCCId)
  (lmp::obj::nodeid::ast::LocalNodeId,      m_localNodeId)
  (lmp::obj::ccid::ast::RemoteCCId,         m_remoteCCId)
  (lmp::obj::msgid::ast::MessageIdAck,      m_messageId)
  (lmp::obj::nodeid::ast::RemoteNodeId,     m_remoteNodeId)
)

#endif /* LMP_MSG_CONFIGACK_AST_ADAPTED_HPP_ */
