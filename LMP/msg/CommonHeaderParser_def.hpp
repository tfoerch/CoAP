#ifndef LMP_MSG_COMMONHEADER_PARSER_DEF_HPP_
#define LMP_MSG_COMMONHEADER_PARSER_DEF_HPP_
/*
 * CommonHeader_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/CommonHeaderAstAdapted.hpp"
#include "msg/CommonHeaderParser.hpp"

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
      common_header_flags_grammar<Iterator>::common_header_flags_grammar()
      : common_header_flags_grammar<Iterator>::base_type(common_header_flags_rule, "common_header_flags")
      {
        using qi::byte_;
        using qi::_1;
        using phoenix::at_c;
        using namespace qi::labels;

        common_header_flags_rule =
            byte_(c_supportedVersion << 4)                // version
            >> byte_    [ at_c<0>(_val) = ( _1 & c_controlChannelDownMask ), at_c<1>(_val) = ( _1 & c_lmpRestartMask ) ]            // flags
            >> byte_	                                  // reserved
            ;

        common_header_flags_rule.name("common_header_flags");
      }
      template <typename Iterator>
      common_header_length_grammar<Iterator>::common_header_length_grammar()
      : common_header_length_grammar<Iterator>::base_type(common_header_length_rule, "common_header_length")
      {
        using qi::big_word;
        using qi::_1;
        using namespace qi::labels;

        common_header_length_rule =
            big_word [ _val = _1 ]            // length
            >> big_word                       // reserved
            ;

        common_header_length_rule.name("common_header_length");
      }
    } // namespace parser
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_COMMONHEADER_PARSER_DEF_HPP_ */
