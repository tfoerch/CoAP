#ifndef COAP_RFC3986IPv6Address_GENERATOR_HPP_
#define COAP_RFC3986IPv6Address_GENERATOR_HPP_
/*
 * RFC3986IPv6AddressGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/asio/detail/array.hpp>
#include <boost/icl/discrete_interval.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/optional.hpp>
#include <boost/cstdint.hpp>

#include <vector>

namespace rfc3986
{
  namespace generator
  {
    namespace karma = boost::spirit::karma;
    namespace icl = boost::icl;
    typedef boost::asio::detail::array<unsigned char, 16> byte_array16;

    template <typename OutputIterator>
    struct ipv6_address_grammar : karma::grammar<OutputIterator, byte_array16(), karma::locals<byte_array16::const_iterator> >
    {
      ipv6_address_grammar();

      karma::rule<OutputIterator, byte_array16(), karma::locals<byte_array16::const_iterator> >  ipv6_address_rule;
      karma::rule<OutputIterator, std::vector<boost::uint16_t>, karma::locals<size_t>, karma::locals<boost::optional<icl::discrete_interval<size_t> > > >  shortIntSeq_rule;
    };
  } // namespace generator
} // namespace rfc3986

#endif /* COAP_RFC3986IPv6Address_GENERATOR_HPP_ */
