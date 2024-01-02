#ifndef LMP_OBJ_UNKNOWN_HELLO_AST_HPP_
#define LMP_OBJ_UNKNOWN_HELLO_AST_HPP_
/*
 * UnknownHelloCTypeAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAst.hpp"

namespace lmp
{
  namespace obj
  {
    namespace hello
    {
      namespace ast
      {
        typedef lmp::obj::ast::ObjectClassUnknownCType<ObjectClassTraits<ObjectClass::Hello>>  UnknownHelloCType;
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_HELLO_AST_HPP_ */
