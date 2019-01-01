#ifndef COAP_RFC3986Host_PARSER_HPP_
#define COAP_RFC3986Host_PARSER_HPP_
/*
 * RFC3986HostParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986HostAst.hpp"
#include "uri/RFC3986IPLiteralParser.hpp"
#include "uri/RFC3986IPv4AddressParser.hpp"
#include "uri/RFC3986RegNameParser.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/cstdint.hpp>
#include <string>


namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct host_grammar : qi::grammar< Iterator, ast::Host()>
  {

    host_grammar();

    qi::rule<Iterator, ast::Host()>  host_rule;
    ipliteral_grammar<Iterator>      ipliteral;
    ipv4_address_grammar<Iterator>   ipv4_address;
    reg_name_grammar<Iterator>       reg_name;
  };
} // rfc3986
#endif /* COAP_RFC3986Host_PARSER_HPP_ */

