#ifndef LMP_OBJ_REMOTE_CC_ID_AST_ADAPTED_HPP_
#define LMP_OBJ_REMOTE_CC_ID_AST_ADAPTED_HPP_
/*
 * RemoteCCIdAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteCCIdAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::ccid::ast::RemoteCCId,
  (lmp::obj::ccid::ast::RemoteCCId::RemoteCCIdHeaderType,  m_header)
  (lmp::DWORD,                                             m_ccId)
)

#endif /* LMP_OBJ_REMOTE_CC_ID_AST_ADAPTED_HPP_ */
