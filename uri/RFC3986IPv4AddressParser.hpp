#ifndef COAP_RFC3986IPv4Address_PARSER_HPP_
#define COAP_RFC3986IPv4Address_PARSER_HPP_
/*
 * RFC3986IPv4AddressParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */


#include <array>
#include <boost/spirit/include/qi.hpp>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  typedef std::array<unsigned char, 4> byte_array4;

  template < typename Iterator >
  struct ipv4_address_grammar : qi::grammar< Iterator, byte_array4() >
  {
    ipv4_address_grammar();
    qi::rule< Iterator, byte_array4()>  ipv4_address_rule;
  };
} // rfc3986
#endif /* COAP_RFC3986IPv4Address_PARSER_HPP_ */

