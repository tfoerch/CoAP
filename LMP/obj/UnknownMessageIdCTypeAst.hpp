#ifndef LMP_OBJ_UNKNOWN_MESSAGE_ID_AST_HPP_
#define LMP_OBJ_UNKNOWN_MESSAGE_ID_AST_HPP_
/*
 * UnknownMessageIdCTypeAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAst.hpp"

namespace lmp
{
  namespace obj
  {
    namespace msgid
    {
      namespace ast
      {
        typedef lmp::obj::ast::ObjectClassUnknownCType<ObjectClassTraits<ObjectClass::MessageID>>  UnknownMessageIdCType;
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_MESSAGE_ID_AST_HPP_ */
