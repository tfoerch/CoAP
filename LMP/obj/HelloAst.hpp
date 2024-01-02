#ifndef LMP_OBJ_HELLO_AST_HPP_
#define LMP_OBJ_HELLO_AST_HPP_
/*
 * HelloAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"
#include "obj/ObjectClassAst.hpp"
#include "obj/HelloClassAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#endif /* USE_SPIRIT_X3_PARSER */


namespace lmp
{
  namespace obj
  {
    template <>
    struct HeaderCTypeTraits<hello::ClassType, hello::ClassType::Hello>
    {
      typedef typename hello::ClassType                ctype_type;
      static const ObjectClass                         obj_class;
      static const ctype_type                          ctype;
      static const lmp::WORD                           length;
    };
    namespace hello
    {
      namespace ast
      {
#ifdef USE_SPIRIT_X3_PARSER
        namespace x3 = boost::spirit::x3;
#endif /* USE_SPIRIT_X3_PARSER */
        struct Hello
#ifdef USE_SPIRIT_X3_PARSER
            : x3::position_tagged
#endif /* USE_SPIRIT_X3_PARSER */
        {
          typedef
            lmp::obj::ast::ObjectHeader<HeaderCTypeTraits<hello::ClassType,
                                                          hello::ClassType::Hello>>  HelloHeaderType;

          HelloHeaderType  m_header;
          lmp::DWORD       m_txSeqNum;
          lmp::DWORD       m_rcvSeqNum;
        };
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<hello::ast::Hello>(
        const hello::ast::Hello&  objCType);
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_AST_HPP_ */
