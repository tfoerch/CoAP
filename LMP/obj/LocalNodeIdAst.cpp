/*
 * LocalNodeIdAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalNodeIdAst.hpp"

namespace lmp
{
  namespace obj
  {
    const ObjectClass HeaderCTypeTraits<nodeid::ClassType, nodeid::ClassType::LocalNodeId>::obj_class =
      HeaderObjClassTypeTraits<nodeid::ClassType>::obj_class;
    const nodeid::ClassType HeaderCTypeTraits<nodeid::ClassType, nodeid::ClassType::LocalNodeId>::ctype =
      nodeid::ClassType::LocalNodeId;
    const lmp::WORD HeaderCTypeTraits<nodeid::ClassType, nodeid::ClassType::LocalNodeId>::length =
        c_objHeaderLength + 4;
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<nodeid::ast::LocalNodeId>(
        const nodeid::ast::LocalNodeId&  objCType)
      {
        return 4;
      }
    }
  }
}
