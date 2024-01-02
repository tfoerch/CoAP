#ifndef LMP_OBJ_HELLO_PARSER_HPP_
#define LMP_OBJ_HELLO_PARSER_HPP_
/*
 * HelloParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#else
#include "obj/ObjectHeaderParser.hpp"
#include <boost/spirit/include/qi.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
#ifdef USE_SPIRIT_X3_PARSER
      namespace x3 = boost::spirit::x3;

      struct hello_class;
      typedef
        x3::rule<hello_class, hello::ast::Hello>  hello_type;
      BOOST_SPIRIT_DECLARE(hello_type);
#else
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct hello_grammar : qi::grammar<Iterator, hello::ast::Hello()>
      {
        hello_grammar();
        lmp::obj::parser::object_header_fix_length_grammar<Iterator,
                                                           hello::ClassType,
                                                           hello::ClassType::Hello>  object_header;
        qi::rule<Iterator, hello::ast::Hello()>                                      hello_rule;
      };

#endif /* USE_SPIRIT_X3_PARSER */
    }
#ifdef USE_SPIRIT_X3_PARSER
    parser::hello_type const& hello_parser();
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_PARSER_HPP_ */
