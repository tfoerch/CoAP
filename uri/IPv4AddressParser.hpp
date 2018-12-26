#ifndef COAP_IPv4Address_PARSER_HPP_
#define COAP_IPv4Address_PARSER_HPP_
/*
 * IPv4AddressParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

//#include "uri/IPAddressAst.hpp"

#include <boost/asio/detail/array.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/cstdint.hpp>


namespace qi = boost::spirit::qi;

typedef boost::asio::detail::array<unsigned char, 4> byte_array4;

template < typename Iterator >
struct ipv4_address_grammar : qi::grammar< Iterator, byte_array4() >
{
  ipv4_address_grammar();
  qi::rule< Iterator, byte_array4()>  ipv4_address_rule;
};
#endif /* COAP_IPv4Address_PARSER_HPP_ */

