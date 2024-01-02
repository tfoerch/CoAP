#ifndef LMP_OBJ_HELLO_CONFIG_AST_HPP_
#define LMP_OBJ_HELLO_CONFIG_AST_HPP_
/*
 * HelloConfigAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"
#include "obj/ObjectClassAst.hpp"
#include "obj/ConfigClassAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#endif /* USE_SPIRIT_X3_PARSER */


namespace lmp
{
  namespace obj
  {
    template <>
    struct HeaderCTypeTraits<config::ClassType, config::ClassType::HelloConfig>
    {
      typedef typename config::ClassType                ctype_type;
      static const ObjectClass                          obj_class;
      static const ctype_type                           ctype;
      static const lmp::WORD                            length;
    };
    namespace config
    {
      namespace ast
      {
#ifdef USE_SPIRIT_X3_PARSER
        namespace x3 = boost::spirit::x3;
#endif /* USE_SPIRIT_X3_PARSER */
        struct HelloConfig
#ifdef USE_SPIRIT_X3_PARSER
            : x3::position_tagged
#endif /* USE_SPIRIT_X3_PARSER */
        {
          typedef
            lmp::obj::ast::ObjectHeader<HeaderCTypeTraits<config::ClassType,
                                                          config::ClassType::HelloConfig>>  HelloConfigHeaderType;

          HelloConfigHeaderType  m_header;
          lmp::WORD              m_helloIntv;
          lmp::WORD              m_helloDeadIntv;
        };
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<config::ast::HelloConfig>(
        const config::ast::HelloConfig&  objCType);
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CONFIG_AST_HPP_ */
