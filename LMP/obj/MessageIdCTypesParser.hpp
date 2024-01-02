#ifndef LMP_OBJ_MESSAGE_ID_CTYPES_PARSER_HPP_
#define LMP_OBJ_MESSAGE_ID_CTYPES_PARSER_HPP_
/*
 * MessageIdCTypesParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdCTypesAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#else
#include "obj/MessageIdParser.hpp"
#include "obj/MessageIdAckParser.hpp"
#include "obj/ObjectClassUnknownCTypeParser.hpp"
#include <boost/spirit/include/qi.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace msgid
    {
      namespace parser
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct message_id_ctypes_grammar : qi::grammar<Iterator, ast::MessageIdCTypes()>
        {
          message_id_ctypes_grammar();

          lmp::obj::parser::message_id_grammar<Iterator>                                          message_id;
          lmp::obj::parser::message_id_ack_grammar<Iterator>                                      message_id_ack;
          lmp::obj::parser::object_class_unknown_ctype_grammar<Iterator,
                                                               lmp::obj::ObjectClass::MessageID>  unknown_msgid_ctype;
          qi::rule<Iterator, ast::MessageIdCTypes()>                                              message_id_ctypes_rule;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_CTYPES_PARSER_HPP_ */
