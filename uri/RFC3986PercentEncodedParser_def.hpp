#ifndef COAP_RFC3986PercentEncoded_PARSER_DEF_HPP_
#define COAP_RFC3986PercentEncoded_PARSER_DEF_HPP_
/*
 * RFC3986PercentEncodedParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PercentEncodedParser.hpp"
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
  percent_encoded_grammar<Iterator>::percent_encoded_grammar()
  : percent_encoded_grammar::base_type( percent_encoded_rule, "percent_encoded" )
  {
    using boost::spirit::ascii::alnum;
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    //percent_encoded  = ALPHA / DIGIT / "-" / "." / "_" / "~"
    percent_encoded_rule %=
           '%'
        >> qi::uint_parser<std::uint8_t, 16, 2, 2>()
        ;

    percent_encoded_rule.name("percent_encoded");
  //  debug(percent_encoded_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(percent_encoded_rule);

  }
} // rfc3986

#endif /* COAP_RFC3986PercentEncoded_PARSER_DEF_HPP_ */

