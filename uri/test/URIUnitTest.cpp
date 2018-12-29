/*
 * URIUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "uri/IPv4AddressParser.hpp"
#include "uri/IPv6AddressParser.hpp"
#include "uri/UriParser.hpp"
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/address_v6.hpp>
#include <string>
#include <iostream>

#define BOOST_TEST_MAIN
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_MODULE LMP
// #include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE( ipaddress )

BOOST_AUTO_TEST_CASE( ipv4address )
{
  ipv4_address_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "2.123.34.255";
    byte_array4 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v4(result), boost::asio::ip::make_address_v4(input));
  }
  {
    std::string input = "249.34.199.9";
    byte_array4 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v4(result), boost::asio::ip::make_address_v4(input));
  }
  {
    std::string input = "139.99.256.19";
    byte_array4 result;
    try {
      BOOST_CHECK(!parse(input.cbegin(), input.cend(), grammar, result));
    } catch(std::exception const& e) {
      std::cout << "error:  " << e.what() << "\n";
    }
  }
}

BOOST_AUTO_TEST_CASE( ipv6address )
{
  ipv6_address_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "2a02:8070:a183:4700:15d:3863:62cf:947a";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183:4700:546e:aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183:4700:546e:aea4:249.34.199.9";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "::8070:a183:4700:6e:aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "::8070:a183:0:546e:aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02::a183:4700:546e:aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "::a183:4700:546e:aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "::4700:546e:aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02::4700:15d:3863:62cf:947a";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070::4700:546e:aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "::546e:aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02::15d:3863:62cf:947a";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070::546e:aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183::546e:aea4:249.34.199.9";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "::aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02::3863:62cf:947a";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070::aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183::aea4:249.34.199.9";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183:4700::aea4:dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "::dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02::62cf:947a";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070::dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183::249.34.199.9";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183:4700::dfad:55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183:4700:15d::62cf:947a";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "::1";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02::947a";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070::55d3";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183::2";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183:4700::5d";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183:0:15d::947a";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183:0:15d:a69b::947a";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "::";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02::";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070::";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183::";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183:4700::";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183:0:15d::";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:a183:0:15d:a69b::";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
  {
    std::string input = "2a02:8070:0:a183:0:15d:a69b::";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
  }
}

BOOST_AUTO_TEST_CASE( test_bind )
{
//  QuotedString<std::string::const_iterator> qs;
//
//  for (std::string const input : {
//          "\"plain string\"",
//          "\"hex\\x20escape\"",
//          "\"oct\\40escape (two digits)\"",
//          "\"oct\\040escape (two digits, leading zero)\"",
//          "\"oct \\105scape (three digits)\"",
//          "\"unterminated string",
//          "\"embedded\\nnewline\"",
//          "\"4-digit unicode \u0065scape\"",
//          "\"8-digit unicode \U00000065scape\"",
//          "\"illegal \\character escape\"",
//          "\"illegal \\xhex escape\"",
//          "\"illegal \\8ct escape\"",
//          "\"illegal \\unicode escape\"",
//          "\"illegal \\Unicode escape\"" } )
//  {
//      std::string result;
//      std::cout << "-------\n" << "\n";
//      std::cout << "input:  '" << input << "'\n";
//      try {
//          parse( input.cbegin(), input.cend(), qs, result );
//          std::cout << "result: '" << result << "'\n";
//      } catch(std::exception const& e) {
//          std::cout << "error:  " << e.what() << "\n";
//      }
//  }

}

BOOST_AUTO_TEST_SUITE_END()

