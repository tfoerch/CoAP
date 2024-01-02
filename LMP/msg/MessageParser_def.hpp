#ifndef LMP_MSG_MESSAGE_PARSER_DEF_HPP_
#define LMP_MSG_MESSAGE_PARSER_DEF_HPP_
/*
 * MessageParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageParser.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

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
      message_grammar<Iterator>::message_grammar()
      : message_grammar<Iterator>::base_type(message_rule, "message")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::eps;
        using qi::_a;
        using qi::_b;
        using qi::_1;
        using phoenix::at_c;
        using namespace qi::labels;

        message_rule =
            common_header_flags [ _a = _1 ]
            >> ( ( byte_(static_cast<typename std::underlying_type<MsgType>::type>(MsgType::Config))
                   >> config_msg(_a) ) |
                 ( byte_(static_cast<std::underlying_type<MsgType>::type>(MsgType::ConfigAck))
                   >> config_ack_msg(_a) ) |
                 ( byte_(static_cast<std::underlying_type<MsgType>::type>(MsgType::ConfigNack))
                   >>  config_nack_msg(_a) ) |
                 ( byte_(static_cast<std::underlying_type<MsgType>::type>(MsgType::Hello))
                   >>  hello_msg(_a) ) |
                 unknown_msg(_a) ) [ _val = _1 ]
            ;

        message_rule.name("message");
      }
    } // namespace parser
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_MESSAGE_PARSER_DEF_HPP_ */
