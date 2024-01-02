#ifndef LMP_MSG_COMMONHEADER_GENERATOR_HPP_
#define LMP_MSG_COMMONHEADER_GENERATOR_HPP_
/*
 * CommonHeaderGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/CommonHeaderAst.hpp"
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    namespace generator
    {
      namespace karma = boost::spirit::karma;

      template <typename OutputIterator, MsgType msgType>
      struct common_header_grammar : karma::grammar<OutputIterator,
                                                    ast::CommonHeaderFlags(lmp::WORD)>
      {
        common_header_grammar();

        boost::phoenix::function<lmp::msg::ast::GetFlags>   phx_getFlags;
        karma::rule<OutputIterator,
                    ast::CommonHeaderFlags(lmp::WORD)>      common_header_rule;
      };

      template <typename OutputIterator>
      struct common_header_unknown_msgType_grammar : karma::grammar<OutputIterator,
                                                                    ast::CommonHeaderUnknownMsgType(lmp::WORD)>
      {
        common_header_unknown_msgType_grammar();

        boost::phoenix::function<lmp::msg::ast::GetFlags>        phx_getFlags;
        karma::rule<OutputIterator,
                    ast::CommonHeaderUnknownMsgType(lmp::WORD)>  common_header_unknown_msgType_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_COMMONHEADER_GENERATOR_HPP_ */
