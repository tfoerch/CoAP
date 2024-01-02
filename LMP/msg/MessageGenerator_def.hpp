#ifndef LMP_MSG_MESSAGE_GENERATOR_DEF_HPP_
#define LMP_MSG_MESSAGE_GENERATOR_DEF_HPP_
/*
 * MessageGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageGenerator.hpp"
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
      message_grammar<OutputIterator>::message_grammar()
      : message_grammar::base_type(message_rule, "message")
      {
        using phoenix::at_c;
        using qi::attr;
        using namespace qi::labels;

        message_rule %=
            config_msg |
            config_ack_msg |
            config_nack_msg |
            hello_msg |
            unknown_msg
            ;

        message_rule.name("message");
      }
    } // namespace generate
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_MESSAGE_GENERATOR_DEF_HPP_ */
