#ifndef COAP_RFC3986RegName_PARSER_DEF_HPP_
#define COAP_RFC3986RegName_PARSER_DEF_HPP_
/*
 * RFC3986RegNameParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986RegNameParser.hpp"
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
  reg_name_grammar<Iterator>::reg_name_grammar()
  : reg_name_grammar::base_type( reg_name_rule, "reg_name" )
  {
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    //reg-name    = *( unreserved / pct-encoded / sub-delims )
    reg_name_rule %=
          *( unreserved |
             percent_encoded |
             sub_delims )
        ;

    reg_name_rule.name("reg_name");
  //  debug(reg_name_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(reg_name_rule);

  //  on_error<fail>
  //  (
  //    reg_name_rule,
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

#endif /* COAP_RFC3986RegName_PARSER_DEF_HPP_ */

