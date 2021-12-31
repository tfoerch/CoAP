#ifndef COAP_RFC3986IPv6Address_PARSER_HPP_
#define COAP_RFC3986IPv6Address_PARSER_HPP_
/*
 * RFC3986IPv6AddressParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986IPv4AddressParser.hpp"
#include <array>
#include <boost/spirit/include/qi.hpp>
#include <cstdint>


namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  typedef std::array<unsigned char, 16> byte_array16;

  template < typename Iterator >
  struct ipv6_address_grammar : qi::grammar< Iterator, byte_array16(), qi::locals<byte_array16::iterator> >
  {
    typedef std::array<unsigned char, 2> byte_array2;
    typedef std::array<unsigned char, 4> byte_array4;
    typedef std::array<unsigned char, 6> byte_array6;
    typedef std::array<unsigned char, 8> byte_array8;
    typedef std::array<unsigned char, 10> byte_array10;
    typedef std::array<unsigned char, 12> byte_array12;
    typedef std::array<unsigned char, 14> byte_array14;

    ipv6_address_grammar();

    qi::rule<Iterator, byte_array16(), qi::locals<byte_array16::iterator> >  ipv6_address_rule;
    qi::rule<Iterator, byte_array14(), qi::locals<byte_array14::iterator> >  least_sig_112bits_rule;
    qi::rule<Iterator, byte_array14()>                                       least_112bits_rule;
    qi::rule<Iterator, byte_array12(), qi::locals<byte_array12::iterator> >  least_sig_96bits_rule;
    qi::rule<Iterator, byte_array12()>                                       least_96bits_rule;
    qi::rule<Iterator, byte_array10(), qi::locals<byte_array10::iterator> >  least_sig_80bits_rule;
    qi::rule<Iterator, byte_array10()>                                       least_80bits_rule;
    qi::rule<Iterator, byte_array8(), qi::locals<byte_array8::iterator> >    least_sig_64bits_rule;
    qi::rule<Iterator, byte_array8()>                                        least_64bits_rule;
    qi::rule<Iterator, byte_array6(), qi::locals<byte_array6::iterator> >    least_sig_48bits_rule;
    qi::rule<Iterator, byte_array6()>                                        least_48bits_rule;
    qi::rule<Iterator, byte_array4()>                                        least_sig_32bits_rule;
    qi::rule<Iterator, byte_array4()>                                        least_32bits_rule;
    qi::rule<Iterator, byte_array2()>                                        hex_16bits_rule;
    qi::rule<Iterator, byte_array2()>                                        least_16bits_rule;
    ipv4_address_grammar<Iterator>                                           ipv4_address;
  };
} // rfc3986
#endif /* COAP_RFC3986IPv6Address_PARSER_HPP_ */

