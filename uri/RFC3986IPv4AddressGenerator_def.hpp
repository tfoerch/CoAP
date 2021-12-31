#ifndef COAP_RFC3986IPv4Address_GENERATOR_DEF_HPP_
#define COAP_RFC3986IPv4Address_GENERATOR_DEF_HPP_
/*
 * RFC3986IPv4AddressGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "RFC3986IPv4AddressGenerator.hpp"
//#if defined(BOOST_ASIO_HAS_STD_ARRAY)
#include <boost/fusion/adapted/std_array.hpp>
//#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
//#include <boost/fusion/adapted/boost_array.hpp>
//#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

namespace boost { namespace spirit { namespace traits {
    template <typename T, size_t N>
        struct is_container<std::array<T, N>, void> : mpl::false_ { };
} } }


namespace rfc3986
{
  namespace generator
  {
    namespace fusion = boost::fusion;
    namespace phoenix = boost::phoenix;

    template <typename OutputIterator>
    ipv4_address_grammar<OutputIterator>::ipv4_address_grammar()
    : ipv4_address_grammar::base_type(ipv4_address_rule, "ipv4_address")
    {
      using phoenix::at_c;

      ipv4_address_rule %=
             karma::uint_generator<std::uint8_t, 10>()
          << '.'
          << karma::uint_generator<std::uint8_t, 10>()
          << '.'
          << karma::uint_generator<std::uint8_t, 10>()
          << '.'
          << karma::uint_generator<std::uint8_t, 10>()
          ;

      ipv4_address_rule.name("ipv4_address");
    }
  } // namespace generator
} // namespace rfc3986

#endif /* COAP_RFC3986IPv4Address_GENERATOR_DEF_HPP_ */
