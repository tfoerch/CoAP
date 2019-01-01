#ifndef COAP_RFC3986Host_PARSER_DEF_HPP_
#define COAP_RFC3986Host_PARSER_DEF_HPP_
/*
 * RFC3986HostParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986HostParser.hpp"
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
  host_grammar<Iterator>::host_grammar()
  : host_grammar::base_type( host_rule, "host" )
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

    // host        = IP-literal / IPv4address / reg-name
    host_rule %=
         ( ipliteral |
           ipv4_address |
           reg_name )
        ;


    host_rule.name("host");
  //  debug(host_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(host_rule);

  //  on_error<fail>
  //  (
  //    host_rule,
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

#endif /* COAP_RFC3986Host_PARSER_DEF_HPP_ */

