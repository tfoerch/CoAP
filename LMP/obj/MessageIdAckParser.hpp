#ifndef LMP_OBJ_MESSAGE_ID_ACK_PARSER_HPP_
#define LMP_OBJ_MESSAGE_ID_ACK_PARSER_HPP_
/*
 * MessageIdAckParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAckAst.hpp"

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

      struct message_id_ack_class;
      typedef
        x3::rule<message_id_ack_class, msgid::ast::MessageIdAck>  message_id_ack_type;
      BOOST_SPIRIT_DECLARE(message_id_ack_type);
#else
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct message_id_ack_grammar : qi::grammar<Iterator, msgid::ast::MessageIdAck()>
      {
        message_id_ack_grammar();
        lmp::obj::parser::object_header_fix_length_grammar<Iterator,
                                                           msgid::ClassType,
                                                           msgid::ClassType::MessageIdAck>  object_header;
        qi::rule<Iterator, msgid::ast::MessageIdAck()>                                      message_id_ack_rule;
      };

#endif /* USE_SPIRIT_X3_PARSER */
    }
#ifdef USE_SPIRIT_X3_PARSER
    parser::message_id_ack_type const& message_id_ack();
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_ACK_PARSER_HPP_ */
