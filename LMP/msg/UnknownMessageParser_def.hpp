#ifndef LMP_MSG_UNKNOWN_MESSAGE_PARSER_DEF_HPP_
#define LMP_MSG_UNKNOWN_MESSAGE_PARSER_DEF_HPP_
/*
 * UnknownMessageParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "UnknownMessageAstAdapted.hpp"
#include "msg/CommonHeaderAstAdapted.hpp" // needed for CommonHeaderUnknownMsgType
#include "UnknownMessageParser.hpp"
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
      unknown_message_grammar<Iterator>::unknown_message_grammar()
      : unknown_message_grammar<Iterator>::base_type(unknown_message_rule, "unknown_message")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::_a;
        using qi::_1;
        using qi::attr;
        // using qi::debug;
        using phoenix::at_c;
        using namespace qi::labels;

        unknown_message_rule =
            byte_ [ at_c<0>(at_c<0>(_val)) = _1, at_c<1>(at_c<0>(_val)) = _r1 ]
            >> common_header_length [ _a = _1 ]
            >> object_sequence(_a - c_headerLength) [ at_c<1>(_val) = _1 ]
            ;

        unknown_message_rule.name("unknown_message");

        // debug(unknown_message_rule);
      }
    } // namespace parser
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_UNKNOWN_MESSAGE_PARSER_DEF_HPP_ */
