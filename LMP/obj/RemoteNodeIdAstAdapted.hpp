#ifndef LMP_OBJ_REMOTE_NODE_ID_AST_ADAPTED_HPP_
#define LMP_OBJ_REMOTE_NODE_ID_AST_ADAPTED_HPP_
/*
 * RemoteNodeIdAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteNodeIdAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::nodeid::ast::RemoteNodeId,
  (lmp::obj::nodeid::ast::RemoteNodeId::RemoteNodeIdHeaderType,  m_header)
  (lmp::DWORD,                                                   m_nodeId)
)

#endif /* LMP_OBJ_REMOTE_NODE_ID_AST_ADAPTED_HPP_ */
