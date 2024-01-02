#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_AST_ADAPTED_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_AST_ADAPTED_HPP_
/*
 * ObjectHeaderUnknownObjectClassAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownObjectClassAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::ast::ObjectHeaderUnknownObjectClass,
  (lmp::BYTE,                    m_object_class)
  (lmp::BYTE,                    m_class_type)
  (bool,                         m_negotiable)
)

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_AST_ADAPTED_HPP_ */
