#ifndef COAP_RFC3986IPv4Address_GENERATOR_HPP_
#define COAP_RFC3986IPv4Address_GENERATOR_HPP_
/*
 * RFC3986IPv4AddressGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <array>
#include <boost/spirit/include/karma.hpp>

namespace rfc3986
{
  namespace generator
  {
    namespace karma = boost::spirit::karma;

    typedef std::array<unsigned char, 4> byte_array4;

    template <typename OutputIterator>
    struct ipv4_address_grammar : karma::grammar<OutputIterator, byte_array4()>
    {
      ipv4_address_grammar();

      karma::rule<OutputIterator, byte_array4()>  ipv4_address_rule;
    };
  } // namespace generator
} // namespace rfc3986

#endif /* COAP_RFC3986IPv4Address_GENERATOR_HPP_ */
