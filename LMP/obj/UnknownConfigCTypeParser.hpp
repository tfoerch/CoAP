#ifndef LMP_OBJ_UNKNOWN_CONFIG_PARSER_HPP_
#define LMP_OBJ_UNKNOWN_CONFIG_PARSER_HPP_
/*
 * UnknownConfigCTypeParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownConfigCTypeAst.hpp"

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

      struct unknown_config_ctype_class;
      typedef
        x3::rule<unknown_config_ctype_class, config::ast::UnknownConfigCType>  unknown_config_ctype_type;
      BOOST_SPIRIT_DECLARE(unknown_config_ctype_type);
    }
    parser::unknown_config_ctype_type const& unknown_config_ctype();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_CONFIG_PARSER_HPP_ */
