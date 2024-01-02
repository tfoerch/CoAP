#ifndef LMP_OBJ_HELLO_CTYPES_PARSER_HPP_
#define LMP_OBJ_HELLO_CTYPES_PARSER_HPP_
/*
 * HelloCTypesParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloCTypesAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#else
#include "obj/HelloParser.hpp"
#include "obj/ObjectClassUnknownCTypeParser.hpp"
#include <boost/spirit/include/qi.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace hello
    {
      namespace parser
      {
#ifdef USE_SPIRIT_X3_PARSER
        namespace x3 = boost::spirit::x3;

        struct hello_ctypes_class;
        typedef
          x3::rule<hello_ctypes_class, hello::ast::HelloCTypes>  hello_ctypes_type;
        BOOST_SPIRIT_DECLARE(hello_ctypes_type);
#else

        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct hello_ctypes_grammar : qi::grammar<Iterator, hello::ast::HelloCTypes()>
        {
          hello_ctypes_grammar();

          lmp::obj::parser::hello_grammar<Iterator>                                 hello;
          lmp::obj::parser::object_class_unknown_ctype_grammar<Iterator,
                                                               ObjectClass::Hello>  unknown_hello_ctype;
          qi::rule<Iterator, hello::ast::HelloCTypes()>                             hello_ctypes_rule;
        };
#endif /* USE_SPIRIT_X3_PARSER */
      }
#ifdef USE_SPIRIT_X3_PARSER
      parser::hello_ctypes_type const& hello_ctypes();
#endif /* USE_SPIRIT_X3_PARSER */
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CTYPES_PARSER_HPP_ */
