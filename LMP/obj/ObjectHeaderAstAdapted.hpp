#ifndef LMP_OBJ_OBJECTCLASS_AST_ADAPTED_HPP_
#define LMP_OBJ_OBJECTCLASS_AST_ADAPTED_HPP_
/*
 * ObjectHeaderAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>


BOOST_FUSION_ADAPT_TPL_STRUCT(
  (HeaderCTypeTraits),
  (lmp::obj::ast::ObjectHeader)(HeaderCTypeTraits),
  (bool,  m_negotiable)
)

#endif /* LMP_OBJ_OBJECTCLASS_AST_ADAPTED_HPP_ */
