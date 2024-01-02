/*
 * MessageIdAckAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAckAst.hpp"

namespace lmp
{
  namespace obj
  {
    const ObjectClass HeaderCTypeTraits<msgid::ClassType, msgid::ClassType::MessageIdAck>::obj_class =
      HeaderObjClassTypeTraits<msgid::ClassType>::obj_class;
    const msgid::ClassType HeaderCTypeTraits<msgid::ClassType, msgid::ClassType::MessageIdAck>::ctype =
      msgid::ClassType::MessageIdAck;
    const lmp::WORD HeaderCTypeTraits<msgid::ClassType, msgid::ClassType::MessageIdAck>::length =
        c_objHeaderLength + 4;
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<msgid::ast::MessageIdAck>(
        const msgid::ast::MessageIdAck&  objCType)
      {
        return 4;
      }
    }
  }
}
