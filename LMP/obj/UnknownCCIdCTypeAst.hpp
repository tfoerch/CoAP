#ifndef LMP_OBJ_UNKNOWN_CC_ID_AST_HPP_
#define LMP_OBJ_UNKNOWN_CC_ID_AST_HPP_
/*
 * UnknownCCIdCTypeAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAst.hpp"

namespace lmp
{
  namespace obj
  {
    namespace ccid
    {
      namespace ast
      {
        typedef lmp::obj::ast::ObjectClassUnknownCType<ObjectClassTraits<ObjectClass::ControlChannelID>>  UnknownCCIdCType;
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_CC_ID_AST_HPP_ */
