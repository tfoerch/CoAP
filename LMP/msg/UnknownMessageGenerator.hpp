#ifndef LMP_MSG_UNKNOWN_MESSAGE_GENERATOR_HPP_
#define LMP_MSG_UNKNOWN_MESSAGE_GENERATOR_HPP_
/*
 * UnknownMessageGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "UnknownMessageAst.hpp"
#include "msg/CommonHeaderGenerator.hpp"
#include "obj/ObjectSequenceGenerator.hpp"
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct unknown_message_grammar : karma::grammar<OutputIterator, ast::UnknownMessage()>
      {
        unknown_message_grammar();

        boost::phoenix::function<lmp::msg::ast::GetLength<ast::UnknownMessage>>       phx_msgLength;
        lmp::msg::generator::common_header_unknown_msgType_grammar<OutputIterator>    common_header;
        lmp::obj::generator::object_sequence_grammar<OutputIterator>                  object_sequence;
        karma::rule<OutputIterator, ast::UnknownMessage()>                            unknown_message_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_UNKNOWN_MESSAGE_GENERATOR_HPP_ */
