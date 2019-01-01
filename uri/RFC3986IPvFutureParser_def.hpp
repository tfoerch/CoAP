#ifndef COAP_RFC3986IPvFuture_PARSER_DEF_HPP_
#define COAP_RFC3986IPvFuture_PARSER_DEF_HPP_
/*
 * RFC3986IPvFutureParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986IPvFutureParser.hpp"
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
  ipvfuture_grammar<Iterator>::ipvfuture_grammar()
  : ipvfuture_grammar::base_type( ipvfuture_rule, "ipvfuture" )
  {
    using boost::spirit::ascii::xdigit;
    using boost::spirit::ascii::alnum;
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    // IPvFuture  = "v" 1*HEXDIG "." 1*( unreserved / sub-delims / ":" )
    ipvfuture_rule %=
             'v'
          >> +xdigit
          >> '.'
          >> +allowedChars_rule
        ;

    allowedChars_rule %=
        unreserved      |
        sub_delims |
        ':'
        ;

    ipvfuture_rule.name("ipvfuture");
  //  debug(ipvfuture_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(ipvfuture_rule);

    allowedChars_rule.name("allowedChars");
  //  debug(allowedChars_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(allowedChars_rule);

  //  on_error<fail>
  //  (
  //    ipvfuture_rule,
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

#endif /* COAP_RFC3986IPvFuture_PARSER_DEF_HPP_ */

