#ifndef COAP_IPv6Address_PARSER_HPP_
#define COAP_IPv6Address_PARSER_HPP_
/*
 * IPv6AddressParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/IPv4AddressParser.hpp"
#include <boost/asio/detail/array.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/cstdint.hpp>


namespace qi = boost::spirit::qi;

typedef boost::asio::detail::array<unsigned char, 16> byte_array16;

template < typename Iterator >
struct ipv6_address_grammar : qi::grammar< Iterator, byte_array16(), qi::locals<byte_array16::iterator> >
{
  typedef boost::asio::detail::array<unsigned char, 2> byte_array2;
  typedef boost::asio::detail::array<unsigned char, 4> byte_array4;

  ipv6_address_grammar();

  qi::rule<Iterator, byte_array16(), qi::locals<byte_array16::iterator> >  ipv6_address_rule;
  qi::rule<Iterator, byte_array4()>                                        least_sig_32bits_rule;
  qi::rule<Iterator, byte_array2()>                                        hex_16bits_rule;
  ipv4_address_grammar<Iterator>                                           ipv4_address;
};
#endif /* COAP_IPv6Address_PARSER_HPP_ */

