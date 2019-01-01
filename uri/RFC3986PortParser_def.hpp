#ifndef COAP_RFC3986Port_PARSER_DEF_HPP_
#define COAP_RFC3986Port_PARSER_DEF_HPP_
/*
 * RFC3986PortParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PortParser.hpp"
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
  port_grammar<Iterator>::port_grammar()
  : port_grammar::base_type( port_rule, "port" )
  {
    using qi::eps;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    //reg-name    = *( unreserved / pct-encoded / sub-delims )
    port_rule %=
        ( qi::uint_parser<boost::uint16_t, 10, 1, 5>() |
          eps [ _val = 0 ] )
        ;

    port_rule.name("port");
  //  debug(port_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(port_rule);

  //  on_error<fail>
  //  (
  //    port_rule,
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

#endif /* COAP_RFC3986Port_PARSER_DEF_HPP_ */

