#ifndef LMP_OBJ_HELLO_CONFIG_PARSER_HPP_
#define LMP_OBJ_HELLO_CONFIG_PARSER_HPP_
/*
 * HelloConfigParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigAst.hpp"

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

      struct hello_config_class;
      typedef
        x3::rule<hello_config_class, config::ast::HelloConfig>  hello_config_type;
      BOOST_SPIRIT_DECLARE(hello_config_type);
#else
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct hello_config_grammar : qi::grammar<Iterator, config::ast::HelloConfig()>
      {
        hello_config_grammar();
        lmp::obj::parser::object_header_fix_length_grammar<Iterator,
                                                           config::ClassType,
                                                           config::ClassType::HelloConfig>  object_header;
        qi::rule<Iterator, config::ast::HelloConfig()>                                      hello_config_rule;
      };

#endif /* USE_SPIRIT_X3_PARSER */
   }
#ifdef USE_SPIRIT_X3_PARSER
    parser::hello_config_type const& hello_config();
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CONFIG_PARSER_HPP_ */
