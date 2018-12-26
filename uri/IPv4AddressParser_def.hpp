#ifndef COAP_IPv4Address_PARSER_DEF_HPP_
#define COAP_IPv4Address_PARSER_DEF_HPP_
/*
 * IPv4AddressParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/IPv4AddressParser.hpp"
#if defined(BOOST_ASIO_HAS_STD_ARRAY)
#include <boost/fusion/adapted/std_array.hpp>
#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
#include <boost/fusion/adapted/boost_array.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

namespace boost { namespace spirit { namespace traits {
    template <typename T, size_t N>
        struct is_container<boost::asio::detail::array<T, N>, void> : mpl::false_ { };
} } }

namespace qi = boost::spirit::qi;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;


//            IPv4address = dec-octet "." dec-octet "." dec-octet "." dec-octet
//
//            dec-octet   = DIGIT                 ; 0-9
//                        / %x31-39 DIGIT         ; 10-99
//                        / "1" 2DIGIT            ; 100-199
//                        / "2" %x30-34 DIGIT     ; 200-249
//                        / "25" %x30-35          ; 250-255

template <boost::uint8_t  numLeftShift>
struct ShiftByte
{
  template<typename> struct result { typedef boost::uint32_t type; };
  boost::uint32_t operator()(
    const boost::uint8_t& byte) const
  {
    return
      ( static_cast<boost::uint32_t>(byte) << numLeftShift );
  }
};

template < typename Iterator >
ipv4_address_grammar<Iterator>::ipv4_address_grammar()
: ipv4_address_grammar::base_type( ipv4_address_rule, "ipv4_address" )
{
  using namespace qi::labels;
  using qi::on_error;
  using qi::fail;
  using phoenix::construct;
  using phoenix::val;

  boost::phoenix::function<ShiftByte<24>>      phx_leftshift24;
  boost::phoenix::function<ShiftByte<16>>      phx_leftshift16;
  boost::phoenix::function<ShiftByte<8>>       phx_leftshift8;
  boost::phoenix::function<ShiftByte<0>>       phx_noleftshift;

  ipv4_address_rule %=
         qi::uint_parser<boost::uint8_t, 10, 1, 3>() //[ _val = phx_leftshift24(_1) ]
      >> '.'
      > qi::uint_parser<boost::uint8_t, 10, 1, 3>() //[ _val += phx_leftshift16(_1) ]
      >> '.'
      > qi::uint_parser<boost::uint8_t, 10, 1, 3>() //[ _val += phx_leftshift8(_1) ]
      >> '.'
      > qi::uint_parser<boost::uint8_t, 10, 1, 3>() //[ _val += phx_noleftshift(_1) ]
      ;

  ipv4_address_rule.name("ipv4_address");

  on_error<fail>
  (
    ipv4_address_rule,
    std::cout
          << val("Error! Expecting ")
          << _4                               // what failed?
          << val(" here: \"")
          << construct<std::string>(_3, _2)   // iterators to error-pos, end
          << val("\"")
          << std::endl
  );
}

#endif /* COAP_IPv4Address_PARSER_DEF_HPP_ */

