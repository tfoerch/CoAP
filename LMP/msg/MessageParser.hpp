#ifndef LMP_MSG_MESSAGE_PARSER_HPP_
#define LMP_MSG_MESSAGE_PARSER_HPP_
/*
 * MessageParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageAst.hpp"
#include "CommonHeaderParser.hpp"
#include "ConfigParser.hpp"
#include "ConfigAckParser.hpp"
#include "ConfigNackParser.hpp"
#include "HelloParser.hpp"
#include "UnknownMessageParser.hpp"

#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    namespace parser
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      struct message_grammar : qi::grammar<Iterator,
                                           ast::Message(),
                                           qi::locals<ast::CommonHeaderFlags>>
      {
        message_grammar();

        lmp::msg::parser::common_header_flags_grammar<Iterator>    common_header_flags;
        lmp::msg::parser::config_msg_grammar<Iterator>             config_msg;
        lmp::msg::parser::config_ack_msg_grammar<Iterator>         config_ack_msg;
        lmp::msg::parser::config_nack_msg_grammar<Iterator>        config_nack_msg;
        lmp::msg::parser::hello_msg_grammar<Iterator>              hello_msg;
        lmp::msg::parser::unknown_message_grammar<Iterator>        unknown_msg;
        qi::rule<Iterator,
                 ast::Message(),
                 qi::locals<ast::CommonHeaderFlags>>               message_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_MESSAGE_PARSER_HPP_ */
