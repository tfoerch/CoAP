/*
 * RemoteCCIdAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteCCIdAst.hpp"

namespace lmp
{
  namespace obj
  {
    const ObjectClass HeaderCTypeTraits<ccid::ClassType, ccid::ClassType::RemoteCCId>::obj_class =
      HeaderObjClassTypeTraits<ccid::ClassType>::obj_class;
    const ccid::ClassType HeaderCTypeTraits<ccid::ClassType, ccid::ClassType::RemoteCCId>::ctype =
      ccid::ClassType::RemoteCCId;
    const lmp::WORD HeaderCTypeTraits<ccid::ClassType, ccid::ClassType::RemoteCCId>::length =
        c_objHeaderLength + 4;
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<ccid::ast::RemoteCCId>(
        const ccid::ast::RemoteCCId&  objCType)
      {
        return 4;
      }
    }
  }
}
