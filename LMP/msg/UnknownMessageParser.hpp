#ifndef LMP_MSG_UNKNOWN_MESSAGE_PARSER_HPP_
#define LMP_MSG_UNKNOWN_MESSAGE_PARSER_HPP_
/*
 * UnknownMessageParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "UnknownMessageAst.hpp"
#include "msg/CommonHeaderParser.hpp"
#include "obj/ObjectSequenceParser.hpp"
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    namespace parser
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct unknown_message_grammar : qi::grammar<Iterator,
                                                   ast::UnknownMessage(ast::CommonHeaderFlags),
                                                   qi::locals<lmp::WORD>>
      {
    	unknown_message_grammar();

        lmp::msg::parser::common_header_length_grammar<Iterator>   common_header_length;
        lmp::obj::parser::object_sequence_grammar<Iterator>        object_sequence;
    	qi::rule<Iterator,
    	         ast::UnknownMessage(ast::CommonHeaderFlags),
                 qi::locals<lmp::WORD>>                            unknown_message_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_UNKNOWN_MESSAGE_PARSER_HPP_ */
