#ifndef LMP_MSG_COMMONHEADER_PARSER_HPP_
#define LMP_MSG_COMMONHEADER_PARSER_HPP_
/*
 * CommonHeaderParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/CommonHeaderAst.hpp"
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    namespace parser
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct common_header_flags_grammar : qi::grammar<Iterator, ast::CommonHeaderFlags()>
      {
        common_header_flags_grammar();

        qi::rule<Iterator, ast::CommonHeaderFlags()>   common_header_flags_rule;
      };
      template <typename Iterator>
      struct common_header_length_grammar : qi::grammar<Iterator, lmp::WORD()>
      {
    	common_header_length_grammar();

        qi::rule<Iterator, lmp::WORD()>   common_header_length_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_COMMONHEADER_PARSER_HPP_ */
