/*
 * MessageIdAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAst.hpp"

namespace lmp
{
  namespace obj
  {
    const ObjectClass HeaderCTypeTraits<msgid::ClassType, msgid::ClassType::MessageId>::obj_class =
      HeaderObjClassTypeTraits<msgid::ClassType>::obj_class;
    const msgid::ClassType HeaderCTypeTraits<msgid::ClassType, msgid::ClassType::MessageId>::ctype =
      msgid::ClassType::MessageId;
    const lmp::WORD HeaderCTypeTraits<msgid::ClassType, msgid::ClassType::MessageId>::length =
        c_objHeaderLength + 4;
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<msgid::ast::MessageId>(
        const msgid::ast::MessageId&  objCType)
      {
        return 4;
      }
    }
  }
}
