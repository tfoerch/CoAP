#ifndef LMP_OBJ_HELLO_CLASS_AST_HPP_
#define LMP_OBJ_HELLO_CLASS_AST_HPP_
/*
 * HelloClassAst.hpp
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
    namespace hello
    {
      enum class ClassType : lmp::BYTE
      {
        Hello = 1,
      };
    }
    template <>
    struct HeaderObjClassTypeTraits<hello::ClassType>
    {
      static const ObjectClass  obj_class = ObjectClass::Hello;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CLASS_AST_HPP_ */
