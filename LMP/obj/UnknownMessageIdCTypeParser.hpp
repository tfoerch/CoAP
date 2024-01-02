#ifndef LMP_OBJ_UNKNOWN_MESSAGE_ID_PARSER_HPP_
#define LMP_OBJ_UNKNOWN_MESSAGE_ID_PARSER_HPP_
/*
 * UnknownMessageIdCTypeParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownMessageIdCTypeAst.hpp"

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

      struct unknown_message_id_ctype_class;
      typedef
        x3::rule<unknown_message_id_ctype_class, msgid::ast::UnknownMessageIdCType>  unknown_message_id_ctype_type;
      BOOST_SPIRIT_DECLARE(unknown_message_id_ctype_type);
    }
    parser::unknown_message_id_ctype_type const& unknown_message_id_ctype();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_MESSAGE_ID_PARSER_HPP_ */
