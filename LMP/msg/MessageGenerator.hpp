#ifndef LMP_MSG_MESSAGE_GENERATOR_HPP_
#define LMP_MSG_MESSAGE_GENERATOR_HPP_
/*
 * MessageGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageAst.hpp"
#include "ConfigGenerator.hpp"
#include "ConfigAckGenerator.hpp"
#include "ConfigNackGenerator.hpp"
#include "HelloGenerator.hpp"
#include "UnknownMessageGenerator.hpp"
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct message_grammar : karma::grammar<OutputIterator, ast::Message()>
      {
        message_grammar();

        lmp::msg::generator::config_msg_grammar<OutputIterator>       config_msg;
        lmp::msg::generator::config_ack_msg_grammar<OutputIterator>   config_ack_msg;
        lmp::msg::generator::config_nack_msg_grammar<OutputIterator>  config_nack_msg;
        lmp::msg::generator::hello_msg_grammar<OutputIterator>        hello_msg;
        lmp::msg::generator::unknown_message_grammar<OutputIterator>  unknown_msg;
        karma::rule<OutputIterator, ast::Message()>                   message_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_MESSAGE_GENERATOR_HPP_ */
