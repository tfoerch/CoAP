#ifndef LMP_OBJ_OBJECTS_AST_HPP_
#define LMP_OBJ_OBJECTS_AST_HPP_
/*
 * ObjectsAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdCTypesAst.hpp"
#include "obj/MessageIdCTypesAst.hpp"
#include "obj/NodeIdCTypesAst.hpp"
#include "obj/ConfigCTypesAst.hpp"
#include "obj/HelloCTypesAst.hpp"
#include "obj/UnknownObjectClassAst.hpp"
//
//#include <boost/variant.hpp>
//#include <boost/spirit/include/qi.hpp>
//#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace ast
    {
      typedef boost::variant<ccid::ast::ControlChannelIdCTypes,
                             msgid::ast::MessageIdCTypes,
                             nodeid::ast::NodeIdCTypes,
                             config::ast::ConfigCTypes,
                             hello::ast::HelloCTypes,
                             UnknownObjectClass>   Objects;
      std::ostream& operator<<(
        std::ostream&   os,
        const Objects&  objects);
      template <>
      lmp::DWORD getBodyLength<Objects>(
        const Objects&  objects);
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTS_AST_HPP_ */
