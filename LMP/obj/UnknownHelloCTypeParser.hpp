#ifndef LMP_OBJ_UNKNOWN_HELLO_PARSER_HPP_
#define LMP_OBJ_UNKNOWN_HELLO_PARSER_HPP_
/*
 * UnknownHelloCTypeParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownHelloCTypeAst.hpp"

#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
//#include <boost/spirit/home/x3.hpp>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;

      struct unknown_hello_ctype_class;
      typedef
        x3::rule<unknown_hello_ctype_class, hello::ast::UnknownHelloCType>  unknown_hello_ctype_type;
      BOOST_SPIRIT_DECLARE(unknown_hello_ctype_type);
    }
    parser::unknown_hello_ctype_type const& unknown_hello_ctype();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_HELLO_PARSER_HPP_ */
