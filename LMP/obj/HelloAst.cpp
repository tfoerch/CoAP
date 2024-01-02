/*
 * HelloAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloAst.hpp"

namespace lmp
{
  namespace obj
  {
    const ObjectClass HeaderCTypeTraits<hello::ClassType, hello::ClassType::Hello>::obj_class =
      HeaderObjClassTypeTraits<hello::ClassType>::obj_class;
    const hello::ClassType HeaderCTypeTraits<hello::ClassType, hello::ClassType::Hello>::ctype =
      hello::ClassType::Hello;
    const lmp::WORD HeaderCTypeTraits<hello::ClassType, hello::ClassType::Hello>::length =
        c_objHeaderLength + 4 + 4;
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<hello::ast::Hello>(
        const hello::ast::Hello&  objCType)
      {
        return 4 + 4;
      }
    }
  }
}
