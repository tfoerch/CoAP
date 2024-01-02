#ifndef LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_AST_ADAPTED_HPP_
#define LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_AST_ADAPTED_HPP_
/*
 * ObjectClassUnknownCTypeAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_TPL_STRUCT(
  (ObjClassTraits),
  (lmp::obj::ast::ObjectClassUnknownCType)(ObjClassTraits),
  (lmp::obj::ast::ObjectHeaderUnknownCType<ObjClassTraits>,  m_header)
  (lmp::obj::ast::ByteSequence,                              m_data)
)

#endif /* LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_AST_ADAPTED_HPP_ */
