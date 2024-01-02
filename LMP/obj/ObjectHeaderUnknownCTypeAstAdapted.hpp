#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_AST_ADAPTED_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_AST_ADAPTED_HPP_
/*
 * ObjectHeaderUnknownCTypeAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownCTypeAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_TPL_STRUCT(
  (ObjClassTraits),
  (lmp::obj::ast::ObjectHeaderUnknownCType)(ObjClassTraits),
  (lmp::BYTE,                    m_class_type)
  (bool,                         m_negotiable)
)

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_AST_ADAPTED_HPP_ */
