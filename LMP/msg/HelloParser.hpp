#ifndef LMP_MSG_HELLO_PARSER_HPP_
#define LMP_MSG_HELLO_PARSER_HPP_
/*
 * HelloParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "HelloAst.hpp"
#include "msg/CommonHeaderParser.hpp"
#include "obj/HelloParser.hpp"
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    namespace parser
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct hello_msg_grammar : qi::grammar<Iterator,
                                             ast::Hello(ast::CommonHeaderFlags),
                                             qi::locals<lmp::WORD>>
      {
        hello_msg_grammar();

        lmp::msg::parser::common_header_length_grammar<Iterator>  common_header_length;
        lmp::obj::parser::hello_grammar<Iterator>                 hello;
        qi::rule<Iterator,
                 ast::Hello(ast::CommonHeaderFlags),
                 qi::locals<lmp::WORD>>                           hello_msg_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_HELLO_PARSER_HPP_ */
