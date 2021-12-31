#ifndef COAP_RFC3986IPv6Address_PARSER_DEF_HPP_
#define COAP_RFC3986IPv6Address_PARSER_DEF_HPP_
/*
 * RFC3986IPv6AddressParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986IPv6AddressParser.hpp"
//#if defined(BOOST_ASIO_HAS_STD_ARRAY)
#include <boost/fusion/adapted/std_array.hpp>
//#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
//#include <boost/fusion/adapted/boost_array.hpp>
//#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

namespace boost { namespace spirit { namespace traits {
    template <typename T, size_t N>
        struct is_container<std::array<T, N>, void> : mpl::false_ { };
} } }

namespace rfc3986
{
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
    template<typename> struct result { typedef std::uint16_t type; };
    std::uint16_t operator()(
      const std::uint16_t&  value) const
    {
      return static_cast<std::uint16_t>(value >> 8);
    }
  };

  struct getLowByte
  {
    template<typename> struct result { typedef std::uint16_t type; };
    std::uint16_t operator()(
      const std::uint16_t&  value) const
    {
      return static_cast<std::uint16_t>(value & std::numeric_limits<std::uint16_t>::max());
    }
  };

  template < typename Iterator >
  ipv6_address_grammar<Iterator>::ipv6_address_grammar()
  : ipv6_address_grammar::base_type( ipv6_address_rule, "ipv6_address" )
  {
    using qi::eps;
    using qi::eoi;
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
        (    eps [ qi::_a = phoenix::begin(qi::_val) ]
          >> qi::repeat(6) [
                hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
             >> ':' ]
          >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ] ) |
        (    "::"
          >> least_112bits_rule [ qi::_a = phoenix::begin(qi::_val), *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1),
                                  *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1), *qi::_a++ = at_c<4>(_1), *qi::_a++ = at_c<5>(_1),
                                  *qi::_a++ = at_c<6>(_1), *qi::_a++ = at_c<7>(_1), *qi::_a++ = at_c<8>(_1), *qi::_a++ = at_c<9>(_1),
                                  *qi::_a++ = at_c<10>(_1), *qi::_a++ = at_c<11>(_1), *qi::_a++ = at_c<12>(_1), *qi::_a++ = at_c<13>(_1) ] ) |
        (    hex_16bits_rule  [ qi::_a = phoenix::begin(qi::_val), *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
          >> "::"
          >> least_96bits_rule [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1),
                                 *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1), *qi::_a++ = at_c<4>(_1), *qi::_a++ = at_c<5>(_1),
                                 *qi::_a++ = at_c<6>(_1), *qi::_a++ = at_c<7>(_1), *qi::_a++ = at_c<8>(_1), *qi::_a++ = at_c<9>(_1),
                                 *qi::_a++ = at_c<10>(_1), *qi::_a++ = at_c<11>(_1) ] ) |
        (    hex_16bits_rule  [ qi::_a = phoenix::begin(qi::_val), *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
          >> ':'
          >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
          >> "::"
          >> least_80bits_rule [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1),
                                 *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1), *qi::_a++ = at_c<4>(_1), *qi::_a++ = at_c<5>(_1),
                                 *qi::_a++ = at_c<6>(_1), *qi::_a++ = at_c<7>(_1), *qi::_a++ = at_c<8>(_1), *qi::_a++ = at_c<9>(_1) ] ) |
        (    hex_16bits_rule  [ qi::_a = phoenix::begin(qi::_val), *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
          >> qi::repeat(2) [
                ':'
             >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ]
          >> "::"
          >> least_64bits_rule [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1),
                                 *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1), *qi::_a++ = at_c<4>(_1), *qi::_a++ = at_c<5>(_1),
                                 *qi::_a++ = at_c<6>(_1), *qi::_a++ = at_c<7>(_1) ] ) |
        (    hex_16bits_rule  [ qi::_a = phoenix::begin(qi::_val), *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
          >> qi::repeat(3) [
                ':'
             >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ]
          >> "::"
          >> least_48bits_rule [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1),
                                 *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1), *qi::_a++ = at_c<4>(_1), *qi::_a++ = at_c<5>(_1) ] ) |
        (    hex_16bits_rule  [ qi::_a = phoenix::begin(qi::_val), *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
          >> qi::repeat(4) [
                ':'
             >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ]
          >> "::"
          >> least_32bits_rule [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1),
                                 *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ] ) |
        (    hex_16bits_rule  [ qi::_a = phoenix::begin(qi::_val), *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
          >> qi::repeat(5) [
                ':'
             >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ]
          >> "::"
          >> least_16bits_rule [ *qi::_a++ = 0, *qi::_a++ = 0, *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ) |
        (    hex_16bits_rule  [ qi::_a = phoenix::begin(qi::_val), *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
          >> qi::repeat(6) [
                ':'
             >> hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ] ]
          >> "::"
          >> eps [ *qi::_a++ = 0, *qi::_a++ = 0 ] )
        ;

    least_112bits_rule =
        least_sig_112bits_rule [ _val = _1 ] |
        least_96bits_rule [ at_c<0>(_val) = 0, at_c<1>(_val) = 0, at_c<2>(_val) = at_c<0>(_1), at_c<3>(_val) = at_c<1>(_1),
                            at_c<4>(_val) = at_c<2>(_1), at_c<5>(_val) = at_c<3>(_1), at_c<6>(_val) = at_c<4>(_1), at_c<7>(_val) = at_c<5>(_1),
                            at_c<8>(_val) = at_c<6>(_1), at_c<9>(_val) = at_c<7>(_1), at_c<10>(_val) = at_c<8>(_1), at_c<11>(_val) = at_c<9>(_1),
                            at_c<12>(_val) = at_c<10>(_1), at_c<13>(_val) = at_c<11>(_1) ]
        ;

    least_sig_112bits_rule =
           eps [ qi::_a = phoenix::begin(qi::_val) ]
        >> qi::repeat(5) [
              hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
           >> ':' ]
        >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ]
        ;

    least_96bits_rule =
        least_sig_96bits_rule [ _val = _1 ] |
        least_80bits_rule [ at_c<0>(_val) = 0, at_c<1>(_val) = 0, at_c<2>(_val) = at_c<0>(_1), at_c<3>(_val) = at_c<1>(_1),
                            at_c<4>(_val) = at_c<2>(_1), at_c<5>(_val) = at_c<3>(_1), at_c<6>(_val) = at_c<4>(_1), at_c<7>(_val) = at_c<5>(_1),
                            at_c<8>(_val) = at_c<6>(_1), at_c<9>(_val) = at_c<7>(_1), at_c<10>(_val) = at_c<8>(_1), at_c<11>(_val) = at_c<9>(_1) ]
        ;

    least_sig_96bits_rule =
           eps [ qi::_a = phoenix::begin(qi::_val) ]
        >> qi::repeat(4) [
              hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
           >> ':' ]
        >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ]
        ;

    least_80bits_rule =
        least_sig_80bits_rule [ _val = _1 ] |
        least_64bits_rule [ at_c<0>(_val) = 0, at_c<1>(_val) = 0, at_c<2>(_val) = at_c<0>(_1), at_c<3>(_val) = at_c<1>(_1),
                            at_c<4>(_val) = at_c<2>(_1), at_c<5>(_val) = at_c<3>(_1), at_c<6>(_val) = at_c<4>(_1), at_c<7>(_val) = at_c<5>(_1),
                            at_c<8>(_val) = at_c<6>(_1), at_c<9>(_val) = at_c<7>(_1) ]
        ;

    least_sig_80bits_rule =
           eps [ qi::_a = phoenix::begin(qi::_val) ]
        >> qi::repeat(3) [
              hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
           >> ':' ]
        >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ]
        ;

    least_64bits_rule =
        least_sig_64bits_rule [ _val = _1 ] |
        least_48bits_rule [ at_c<0>(_val) = 0, at_c<1>(_val) = 0, at_c<2>(_val) = at_c<0>(_1), at_c<3>(_val) = at_c<1>(_1),
                            at_c<4>(_val) = at_c<2>(_1), at_c<5>(_val) = at_c<3>(_1), at_c<6>(_val) = at_c<4>(_1), at_c<7>(_val) = at_c<5>(_1) ]
        ;

    least_sig_64bits_rule =
           eps [ qi::_a = phoenix::begin(qi::_val) ]
        >> qi::repeat(2) [
              hex_16bits_rule  [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
           >> ':' ]
        >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ]
        ;

    least_48bits_rule =
        least_sig_48bits_rule [ _val = _1 ] |
        least_32bits_rule [ at_c<0>(_val) = 0, at_c<1>(_val) = 0, at_c<2>(_val) = at_c<0>(_1), at_c<3>(_val) = at_c<1>(_1),
                            at_c<4>(_val) = at_c<2>(_1), at_c<5>(_val) = at_c<3>(_1) ]
        ;

    least_sig_48bits_rule =
           hex_16bits_rule [ qi::_a = phoenix::begin(qi::_val), *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1) ]
        >> ':'
        >> least_sig_32bits_rule [ *qi::_a++ = at_c<0>(_1), *qi::_a++ = at_c<1>(_1), *qi::_a++ = at_c<2>(_1), *qi::_a++ = at_c<3>(_1) ]
        ;

    least_32bits_rule =
        least_sig_32bits_rule [ _val = _1 ] |
        least_16bits_rule [ at_c<0>(_val) = 0, at_c<1>(_val) = 0, at_c<2>(_val) = at_c<0>(_1), at_c<3>(_val) = at_c<1>(_1) ]
        ;

    //ls32        = ( h16 ":" h16 ) / IPv4address
    //            ; least-significant 32 bits of address
    least_sig_32bits_rule =
        (    hex_16bits_rule [ at_c<0>(_val) = at_c<0>(_1), at_c<1>(_val) = at_c<1>(_1) ]
          >> ':'
          >> hex_16bits_rule [ at_c<2>(_val) = at_c<0>(_1), at_c<3>(_val) = at_c<1>(_1) ] ) |
        ipv4_address [ _val = _1 ]
        ;

    least_16bits_rule =
        hex_16bits_rule [ at_c<0>(_val) = at_c<0>(_1), at_c<1>(_val) = at_c<1>(_1) ] |
        eps [ at_c<0>(_val) = 0, at_c<1>(_val) = 0 ]
        ;

    //h16         = 1*4HEXDIG
    //            ; 16 bits of address represented in hexadecimal
    hex_16bits_rule =
        qi::uint_parser<std::uint16_t, 16, 1, 4>() [ at_c<0>(_val) = phx_get_high_byte(_1), at_c<1>(_val) = phx_get_low_byte(_1) ]
        ;


    ipv6_address_rule.name("ipv6_address");
  //  debug(ipv6_address_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(ipv6_address_rule);

    least_sig_32bits_rule.name("least_sig_32bits");
  //  debug(least_sig_32bits_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(least_sig_32bits_rule);

    hex_16bits_rule.name("hex_16bits");
  //  debug(hex_16bits_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(hex_16bits_rule);

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
} // rfc3986

#endif /* COAP_RFC3986IPv6Address_PARSER_DEF_HPP_ */

