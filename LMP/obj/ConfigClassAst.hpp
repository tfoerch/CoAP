#ifndef LMP_OBJ_CONFIG_CLASS_AST_HPP_
#define LMP_OBJ_CONFIG_CLASS_AST_HPP_
/*
 * NodeIdClassAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include "obj/ObjectClassAst.hpp"
#include "obj/ObjectHeaderAst.hpp"
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      enum class ClassType : lmp::BYTE
      {
        HelloConfig = 1
      };
    }
    template <>
    struct HeaderObjClassTypeTraits<config::ClassType>
    {
      static const ObjectClass  obj_class = ObjectClass::Config;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_CLASS_AST_HPP_ */
