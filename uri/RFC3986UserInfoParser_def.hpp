#ifndef COAP_RFC3986UserInfo_PARSER_DEF_HPP_
#define COAP_RFC3986UserInfo_PARSER_DEF_HPP_
/*
 * RFC3986UserInfoParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986UserInfoParser.hpp"
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;
  namespace fusion = boost::fusion;
  namespace phoenix = boost::phoenix;


  template < typename Iterator >
  user_info_grammar<Iterator>::user_info_grammar()
  : user_info_grammar::base_type( user_info_rule, "user_info" )
  {
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    //userinfo    = *( unreserved / pct-encoded / sub-delims / ":" )
    user_info_rule %=
          *( unreserved |
             percent_encoded |
             sub_delims |
             char_(':') )
        ;

    user_info_rule.name("user_info");
  //  debug(user_info_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(user_info_rule);

  //  on_error<fail>
  //  (
  //    user_info_rule,
  //    std::cout
  //          << val("Error! Expecting ")
  //          << _4                               // what failed?
  //          << val(" here: \"")
  //          << construct<std::string>(_3, _2)   // iterators to error-pos, end
  //          << val("\"")
  //          << std::endl
  //  );
  }
} // rfc3986

#endif /* COAP_RFC3986UserInfo_PARSER_DEF_HPP_ */

