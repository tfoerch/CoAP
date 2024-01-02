#ifndef LMP_OBJ_LOCAL_NODE_ID_AST_ADAPTED_HPP_
#define LMP_OBJ_LOCAL_NODE_ID_AST_ADAPTED_HPP_
/*
 * LocalNodeIdAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalNodeIdAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::nodeid::ast::LocalNodeId,
  (lmp::obj::nodeid::ast::LocalNodeId::LocalNodeIdHeaderType,  m_header)
  (lmp::DWORD,                                                 m_nodeId)
)

#endif /* LMP_OBJ_LOCAL_NODE_ID_AST_ADAPTED_HPP_ */
