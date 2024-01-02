/*
 * HelloConfigAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigAst.hpp"

namespace lmp
{
  namespace obj
  {
    const ObjectClass HeaderCTypeTraits<config::ClassType, config::ClassType::HelloConfig>::obj_class =
      HeaderObjClassTypeTraits<config::ClassType>::obj_class;
    const config::ClassType HeaderCTypeTraits<config::ClassType, config::ClassType::HelloConfig>::ctype =
      config::ClassType::HelloConfig;
    const lmp::WORD HeaderCTypeTraits<config::ClassType, config::ClassType::HelloConfig>::length =
        c_objHeaderLength + 4;
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<config::ast::HelloConfig>(
        const config::ast::HelloConfig&  objCType)
      {
        return 4;
      }
    }
  }
}
