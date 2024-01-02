#ifndef LMP_OBJ_UNKNOWN_CONFIG_AST_HPP_
#define LMP_OBJ_UNKNOWN_CONFIG_AST_HPP_
/*
 * UnknownConfigCTypeAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAst.hpp"

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      namespace ast
      {
        typedef lmp::obj::ast::ObjectClassUnknownCType<ObjectClassTraits<ObjectClass::Config>>  UnknownConfigCType;
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_CONFIG_AST_HPP_ */
