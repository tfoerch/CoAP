#ifndef LMP_MSG_COMMONHEADER_GENERATOR_DEF_HPP_
#define LMP_MSG_COMMONHEADER_GENERATOR_DEF_HPP_
/*
 * CommonHeaderGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "CommonHeaderGenerator.hpp"
#include "CommonHeaderAstAdapted.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
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

      template <typename OutputIterator, MsgType msgType>
      common_header_grammar<OutputIterator, msgType>::common_header_grammar()
      : common_header_grammar::base_type(common_header_rule, "common_header")
      {
        using phoenix::at_c;
        using qi::byte_;
        using qi::big_word;
        using namespace qi::labels;

        common_header_rule =
            byte_       [ _1 = (c_supportedVersion << 4) ]  // version
            << byte_    [ _1 = phx_getFlags(_val) ]
//                ( at_c<0>(_val) ?
//                                 ( at_c<1>(_val) ? c_controlChannelDownMask & c_lmpRestartMask : c_controlChannelDownMask ) :
//                                 ( at_c<1>(_val) ? c_lmpRestartMask : 0 ) ) ]              // flags
            << byte_    [ _1 = 0 ]                // reserved
            << byte_    [ _1 = static_cast<typename std::underlying_type<MsgType>::type>(msgType) ]              // msg type
            << big_word [ _1 = _r1 ]              // length
            << big_word [ _1 = 0 ]                // reserved
            ;

        common_header_rule.name("common_header");
      }
      template <typename OutputIterator>
      common_header_unknown_msgType_grammar<OutputIterator>::common_header_unknown_msgType_grammar()
      : common_header_unknown_msgType_grammar::base_type(common_header_unknown_msgType_rule, "common_header_unknown_msgType")
      {
        using phoenix::at_c;
        using qi::byte_;
        using qi::big_word;
        using namespace qi::labels;

        common_header_unknown_msgType_rule =
            byte_       [ _1 = (c_supportedVersion << 4) ]  // version
            << byte_    [ _1 = phx_getFlags(at_c<1>(_val)) ]
            << byte_    [ _1 = 0 ]                // reserved
            << byte_    [ _1 = at_c<0>(_val) ]    // msg type
            << big_word [ _1 = _r1 ]              // length
            << big_word [ _1 = 0 ]                // reserved
            ;

        common_header_unknown_msgType_rule.name("common_header_unknown_msgType");
      }
    } // namespace generate
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_COMMONHEADER_GENERATOR_DEF_HPP_ */
