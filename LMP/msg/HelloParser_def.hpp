#ifndef LMP_MSG_HELLO_PARSER_DEF_HPP_
#define LMP_MSG_HELLO_PARSER_DEF_HPP_
/*
 * HelloParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "HelloAstAdapted.hpp"
#include "HelloParser.hpp"
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
      hello_msg_grammar<Iterator>::hello_msg_grammar()
      : hello_msg_grammar<Iterator>::base_type(hello_msg_rule, "hello_msg")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::_a;
        using qi::_1;
        using qi::attr;
        using qi::omit;
        using phoenix::at_c;
        using namespace qi::labels;

        hello_msg_rule %=
            attr(_r1)
            >> omit[ common_header_length [ _a = _1 ] ]
            >> hello
            ;

        hello_msg_rule.name("hello_msg");
      }
    } // namespace parser
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_HELLO_PARSER_DEF_HPP_ */
