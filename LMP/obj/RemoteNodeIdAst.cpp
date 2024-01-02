/*
 * RemoteNodeIdAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteNodeIdAst.hpp"

namespace lmp
{
  namespace obj
  {
    const ObjectClass HeaderCTypeTraits<nodeid::ClassType, nodeid::ClassType::RemoteNodeId>::obj_class =
      HeaderObjClassTypeTraits<nodeid::ClassType>::obj_class;
    const nodeid::ClassType HeaderCTypeTraits<nodeid::ClassType, nodeid::ClassType::RemoteNodeId>::ctype =
      nodeid::ClassType::RemoteNodeId;
    const lmp::WORD HeaderCTypeTraits<nodeid::ClassType, nodeid::ClassType::RemoteNodeId>::length =
        c_objHeaderLength + 4;
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<nodeid::ast::RemoteNodeId>(
        const nodeid::ast::RemoteNodeId&  objCType)
      {
        return 4;
      }
    }
  }
}
