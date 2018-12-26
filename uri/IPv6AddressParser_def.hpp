#ifndef COAP_IPv6Address_PARSER_DEF_HPP_
#define COAP_IPv6Address_PARSER_DEF_HPP_
/*
 * IPv6AddressParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/IPv6AddressParser.hpp"
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

//IPv6address =                            6( h16 ":" ) ls32
//            /                       "::" 5( h16 ":" ) ls32
//            / [               h16 ] "::" 4( h16 ":" ) ls32
//            / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
//            / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
//            / [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
//            / [ *4( h16 ":" ) h16 ] "::"              ls32
//            / [ *5( h16 ":" ) h16 ] "::"              h16
//            / [ *6( h16 ":" ) h16 ] "::"
//
//ls32        = ( h16 ":" h16 ) / IPv4address
//            ; least-significant 32 bits of address
//
//h16         = 1*4HEXDIG
//            ; 16 bits of address represented in hexadecimal

struct getHighByte
{
  template<typename> struct result { typedef boost::uint8_t type; };
  boost::uint8_t operator()(
    const boost::uint16_t&  value) const
  {
    return static_cast<boost::uint8_t>(value >> 8);
  }
};

struct getLowByte
{
  template<typename> struct result { typedef boost::uint8_t type; };
  boost::uint8_t operator()(
    const boost::uint16_t&  value) const
  {
    return static_cast<boost::uint8_t>(value & std::numeric_limits<boost::uint8_t>::max());
  }
};

template < typename Iterator >
ipv6_address_grammar<Iterator>::ipv6_address_grammar()
: ipv6_address_grammar::base_type( ipv6_address_rule, "ipv6_address" )
{
  using qi::eps;
  using qi::_1;
  using namespace qi::labels;
  using qi::on_error;
  using qi::fail;
  using phoenix::at_c;
  using phoenix::construct;
  using phoenix::val;

  boost::phoenix::function<getHighByte>  phx_get_high_byte;
  boost::phoenix::function<getLowByte>   phx_get_low_byte;

  ipv6_address_rule =
      //IPv6address =                            6( h16 ":" ) ls32
      (    eps [ qi::_a = phoenix::begin(qi::_val) ]
        >> qi::repeat(6) [
              hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
           >> ':' ]
        >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ] ) |
      //            /                       "::" 5( h16 ":" ) ls32
      (    eps [ qi::_a = phoenix::begin(qi::_val), *qi::_a++ = 0, *qi::_a++ = 0 ]
        >> "::"
        >> qi::repeat(5) [
              hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
           >> ':' ]
        >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ] ) |
      //            / [               h16 ] "::" 4( h16 ":" ) ls32
      (    eps [ qi::_a = phoenix::begin(qi::_val) ]
        >> (  hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] |
              eps [ *qi::_a++ = 0, *qi::_a++ = 0 ] )
        >> "::"
        >> eps [ *qi::_a++ = 0, *qi::_a++ = 0 ]
        >> qi::repeat(4) [
              hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
           >> ':' ]
        >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ] ) |
      //            / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
      (    eps [ qi::_a = phoenix::begin(qi::_val) ]
        >> ( ( ( (    hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
                   >> ':' ) |
                 eps [ *qi::_a++ = 0, *qi::_a++ = 0 ] )
               >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ) |
             eps [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0 ] )
        >> "::"
        >> eps [ *qi::_a++ = 0, *qi::_a++ = 0 ]
        >> qi::repeat(3) [
              hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
           >> ':' ]
        >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ] ) |
        //            / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
        (    eps [ qi::_a = phoenix::begin(qi::_val) ]
          >> ( ( qi::repeat(2) [
                 (    hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
                   >> ':' ) |
                 eps [ *qi::_a++ = 0, *qi::_a++ = 0 ] ]
                 >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ) |
               eps [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0 ] )
          >> "::"
          >> eps [ *qi::_a++ = 0, *qi::_a++ = 0 ]
          >> qi::repeat(2) [
                hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
             >> ':' ]
          >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ] ) |
        //            / [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
        (    eps [ qi::_a = phoenix::begin(qi::_val) ]
          >> ( ( qi::repeat(3) [
                 (    hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
                   >> ':' ) |
                 eps [ *qi::_a++ = 0, *qi::_a++ = 0 ] ]
                 >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ) |
               eps [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0 ] )
          >> "::"
          >> eps [ *qi::_a++ = 0, *qi::_a++ = 0 ]
          >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
          >> ':'
          >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ] ) |
        //            / [ *4( h16 ":" ) h16 ] "::"              ls32
        (    eps [ qi::_a = phoenix::begin(qi::_val) ]
          >> ( ( qi::repeat(4) [
                 (    hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
                   >> ':' ) |
                 eps [ *qi::_a++ = 0, *qi::_a++ = 0 ] ]
                 >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ) |
               eps [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0,
                     *qi::_a++ = 0, *qi::_a++ = 0 ] )
          >> "::"
          >> eps [ *qi::_a++ = 0, *qi::_a++ = 0 ]
          >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ] ) |
        //            / [ *5( h16 ":" ) h16 ] "::"              h16
        (    eps [ qi::_a = phoenix::begin(qi::_val) ]
          >> ( ( qi::repeat(5) [
                 (    hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
                   >> ':' ) |
                 eps [ *qi::_a++ = 0, *qi::_a++ = 0 ] ]
                 >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ) |
               eps [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0,
                     *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0 ] )
          >> "::"
          >> eps [ *qi::_a++ = 0, *qi::_a++ = 0 ]
          >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ) |
        //            / [ *6( h16 ":" ) h16 ] "::"
        (    eps [ qi::_a = phoenix::begin(qi::_val) ]
          >> ( ( qi::repeat(6) [
                 (    hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
                   >> ':' ) |
                 eps [ *qi::_a++ = 0, *qi::_a++ = 0 ] ]
                 >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ) |
               eps [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0,
                     *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = 0 ] )
          >> "::"
          >> eps [ *qi::_a++ = 0, *qi::_a++ = 0 ] )
        ;

  //ls32        = ( h16 ":" h16 ) / IPv4address
  //            ; least-significant 32 bits of address
  least_sig_32bits_rule =
      (    hex_16bits_rule [ at_c<0>(_val) = at_c<0>(_1), at_c<1>(_val) = at_c<1>(_1) ]
        >> ':'
        >> hex_16bits_rule [ at_c<2>(_val) = at_c<0>(_1), at_c<3>(_val) = at_c<1>(_1) ] ) |
      ipv4_address [ _val = _1 ]
      ;

  //h16         = 1*4HEXDIG
  //            ; 16 bits of address represented in hexadecimal
  hex_16bits_rule =
      qi::uint_parser<boost::uint16_t, 16, 1, 4>() [ at_c<0>(_val) = phx_get_high_byte(_1), at_c<1>(_val) = phx_get_low_byte(_1) ]
      ;

  ipv6_address_rule.name("ipv6_address");

  least_sig_32bits_rule.name("east_sig_32bits");

  hex_16bits_rule.name("hex_16bits");

//  on_error<fail>
//  (
//    ipv6_address_rule,
//    std::cout
//          << val("Error! Expecting ")
//          << _4                               // what failed?
//          << val(" here: \"")
//          << construct<std::string>(_3, _2)   // iterators to error-pos, end
//          << val("\"")
//          << std::endl
//  );
}

#endif /* COAP_IPv6Address_PARSER_DEF_HPP_ */

