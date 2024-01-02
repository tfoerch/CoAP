#ifndef LMP_OBJ_MESSAGE_ID_CTYPES_PARSER_DEF_HPP_
#define LMP_OBJ_MESSAGE_ID_CTYPES_PARSER_DEF_HPP_
/*
 * MessageIdCTypesParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdCTypesParser.hpp"
#include "obj/MessageIdParser_def.hpp"
#include "obj/MessageIdAckParser_def.hpp"
#ifdef USE_SPIRIT_X3_PARSER
#include "obj/UnknownMessageIdCTypeParser_def.hpp"
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3.hpp>
#else
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace msgid
    {
      namespace parser
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        message_id_ctypes_grammar<Iterator>::message_id_ctypes_grammar()
        : message_id_ctypes_grammar::base_type(message_id_ctypes_rule,
                                               "message_id_ctypes")
        {
          using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          message_id_ctypes_rule %=
              message_id |
              message_id_ack |
              unknown_msgid_ctype
              ;

          message_id_ctypes_rule.name("message_id_ctypes");
        }
      } // namespace parse
    } // namespace msgid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_CTYPES_PARSER_DEF_HPP_ */
