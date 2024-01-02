#ifndef LMP_MSG_UNKNOWN_MESSAGE_GENERATOR_DEF_HPP_
#define LMP_MSG_UNKNOWN_MESSAGE_GENERATOR_DEF_HPP_
/*
 * UnknownMessageGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "UnknownMessageAstAdapted.hpp"
#include "msg/CommonHeaderAstAdapted.hpp" // needed for CommonHeaderUnknownMsgType
#include "UnknownMessageGenerator.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/karma_attr_cast.hpp>
#include <boost/phoenix/object/static_cast.hpp>

namespace lmp
{
  namespace msg
  {
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      unknown_message_grammar<OutputIterator>::unknown_message_grammar()
      : unknown_message_grammar::base_type(unknown_message_rule, "unknown_message")
      {
        using phoenix::at_c;
        using qi::byte_;
        using qi::big_word;
        using qi::attr;
        using namespace qi::labels;

        unknown_message_rule %=
            common_header(phx_msgLength(_val))
            << object_sequence
            ;

        unknown_message_rule.name("unknown_message");
      }
    } // namespace generator
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_UNKNOWN_MESSAGE_GENERATOR_DEF_HPP_ */
