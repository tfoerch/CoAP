#ifndef LMP_OBJ_UNKNOWN_OBJECT_CLASS_AST_ADAPTED_HPP_
#define LMP_OBJ_UNKNOWN_OBJECT_CLASS_AST_ADAPTED_HPP_
/*
 * UnknownObjectClassAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownObjectClassAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::ast::UnknownObjectClass,
  (lmp::obj::ast::ObjectHeaderUnknownObjectClass,  m_header)
  (lmp::obj::ast::ByteSequence,                    m_data)
)

#endif /* LMP_OBJ_UNKNOWN_OBJECT_CLASS_AST_ADAPTED_HPP_ */
