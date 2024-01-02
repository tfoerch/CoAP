/*
 * LocalCCIdAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCIdAst.hpp"

namespace lmp
{
  namespace obj
  {
    const ObjectClass HeaderCTypeTraits<ccid::ClassType, ccid::ClassType::LocalCCId>::obj_class =
      HeaderObjClassTypeTraits<ccid::ClassType>::obj_class;
    const ccid::ClassType HeaderCTypeTraits<ccid::ClassType, ccid::ClassType::LocalCCId>::ctype =
      ccid::ClassType::LocalCCId;
    const lmp::WORD HeaderCTypeTraits<ccid::ClassType, ccid::ClassType::LocalCCId>::length =
        c_objHeaderLength + 4;
  }
}
