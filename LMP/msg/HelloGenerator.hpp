#ifndef LMP_MSG_HELLO_GENERATOR_HPP_
#define LMP_MSG_HELLO_GENERATOR_HPP_
/*
 * HelloGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "HelloAst.hpp"
#include "msg/CommonHeaderGenerator.hpp"
#include "obj/HelloGenerator.hpp"
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct hello_msg_grammar : karma::grammar<OutputIterator, ast::Hello()>
      {
        hello_msg_grammar();

        boost::phoenix::function<lmp::msg::ast::GetLength<ast::Hello>>              phx_msgLength;
        lmp::msg::generator::common_header_grammar<OutputIterator, MsgType::Hello>  common_header;
        lmp::obj::generator::hello_grammar<OutputIterator>                          hello;
        karma::rule<OutputIterator, ast::Hello()>                                   hello_msg_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_HELLO_GENERATOR_HPP_ */
