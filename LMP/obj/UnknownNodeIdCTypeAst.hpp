#ifndef LMP_OBJ_UNKNOWN_NODE_ID_AST_HPP_
#define LMP_OBJ_UNKNOWN_NODE_ID_AST_HPP_
/*
 * UnknownNodeIdCTypeAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAst.hpp"

namespace lmp
{
  namespace obj
  {
    namespace nodeid
    {
      namespace ast
      {
        typedef lmp::obj::ast::ObjectClassUnknownCType<ObjectClassTraits<ObjectClass::NodeID>>  UnknownNodeIdCType;
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_NODE_ID_AST_HPP_ */
