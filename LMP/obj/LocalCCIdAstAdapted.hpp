#ifndef LMP_OBJ_LOCAL_CC_ID_AST_ADAPTED_HPP_
#define LMP_OBJ_LOCAL_CC_ID_AST_ADAPTED_HPP_
/*
 * LocalCCIdAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCIdAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::ccid::ast::LocalCCId,
  (lmp::obj::ccid::ast::LocalCCId::LocalCCIdHeaderType,  m_header)
  (lmp::DWORD,                                           m_ccId)
)

#endif /* LMP_OBJ_LOCAL_CC_ID_AST_ADAPTED_HPP_ */
