#ifndef LMP_MSG_HELLO_GENERATOR_DEF_HPP_
#define LMP_MSG_HELLO_GENERATOR_DEF_HPP_
/*
 * HelloGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "HelloAstAdapted.hpp"
#include "HelloGenerator.hpp"
#include "msg/CommonHeaderGenerator_def.hpp" // no explicit template instantiation
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
      hello_msg_grammar<OutputIterator>::hello_msg_grammar()
      : hello_msg_grammar::base_type(hello_msg_rule, "hello_msg")
      {
        using phoenix::at_c;
        using qi::byte_;
        using qi::big_word;
        using namespace qi::labels;

        hello_msg_rule %=
            common_header(phx_msgLength(_val))
            << hello
            ;

        hello_msg_rule.name("hello_msg");
      }
    } // namespace generate
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_HELLO_GENERATOR_DEF_HPP_ */
