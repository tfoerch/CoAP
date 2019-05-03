/*
 * URIUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "uri/RFC3986IPv4AddressParser.hpp"
#include "uri/RFC3986IPv4AddressGenerator.hpp"
#include "uri/RFC3986IPv6AddressParser.hpp"
#include "uri/RFC3986IPv6AddressGenerator.hpp"
#include "uri/RFC3986IPvFutureParser.hpp"
#include "uri/RFC3986IPLiteralParser.hpp"
#include "uri/RFC3986RegNameParser.hpp"
#include "uri/RFC3986HostParser.hpp"
#include "uri/RFC3986AuthorityParser.hpp"
#include "uri/RFC3986PathAbEmptyParser.hpp"
#include "uri/RFC3986PathAbsoluteParser.hpp"
#include "uri/RFC3986PathRootLessParser.hpp"
#include "uri/RFC3986HierPartParser.hpp"
#include "uri/RFC3986UriParser.hpp"
#include <numeric>
#include <unordered_map>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/address_v6.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
//#include <boost/range/adaptor/transformed.hpp>
//#include <boost/range/algorithm/copy.hpp>
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

class A
{
public:
  virtual ~A(){}
  unsigned int getValue() const
  { return do_getValue(); }
  A* clone() const
  { return do_clone(); }
private:
  virtual unsigned int do_getValue() const = 0;
  virtual A* do_clone() const = 0;
};

struct IsEvenFtor
{
  bool operator()(
    const A& a) const
  { return (a.getValue() % 2 == 0); }
};
struct GetValueFtor
{
  unsigned int operator()(
    const A& a) const
  { return a.getValue(); }
};

class B : public A
{
public:
  explicit B(
    unsigned int value)
  : m_value(value)
  {}
private:
  virtual unsigned int do_getValue() const
  { return m_value; }
  virtual A* do_clone() const
  { return new B(*this); }
  B(const B& other)
  : m_value(other.m_value)
  {}
  unsigned int m_value;
};


BOOST_AUTO_TEST_SUITE( ipaddress )


BOOST_AUTO_TEST_CASE( adapters )
{
  boost::ptr_deque<A> container;
  container.push_back(new B(1));
  container.push_back(new B(2));
  container.push_back(new B(3));
  container.push_back(new B(4));
  boost::transform(container, std::ostream_iterator<int>(std::cout, ","), GetValueFtor());
  boost::copy(container |
              boost::adaptors::filtered(IsEvenFtor()) |
              boost::adaptors::transformed(GetValueFtor()),
              std::ostream_iterator<int>(std::cout, ","));
}

BOOST_AUTO_TEST_CASE( ipv4address )
{
  using namespace rfc3986;

  ipv4_address_grammar<std::string::const_iterator>  grammar;
  typedef std::back_insert_iterator<std::string>  StrOutIterType;
  generator::ipv4_address_grammar<StrOutIterType> generator_grammar;
  {
    std::string input = "2.123.34.255";
    byte_array4 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v4(result), boost::asio::ip::make_address_v4(input));
    std::string output;
    StrOutIterType outIter(output);
    BOOST_CHECK(generate(outIter, generator_grammar, result));
    BOOST_CHECK_EQUAL(output, input);
  }
  {
    std::string input = "249.34.199.9";
    byte_array4 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v4(result), boost::asio::ip::make_address_v4(input));
    std::string output;
    StrOutIterType outIter(output);
    BOOST_CHECK(generate(outIter, generator_grammar, result));
    BOOST_CHECK_EQUAL(output, input);
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
  using namespace rfc3986;

  ipv6_address_grammar<std::string::const_iterator>  grammar;
  typedef std::back_insert_iterator<std::string>  StrOutIterType;
  generator::ipv6_address_grammar<StrOutIterType> generator_grammar;
  {
    std::string input = "2a02:8070:a183:4700:15d:3863:62cf:947a";
    byte_array16 result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v6(result), boost::asio::ip::make_address_v6(input));
    std::string output;
    StrOutIterType outIter(output);
    BOOST_CHECK(generate(outIter, generator_grammar, result));
    BOOST_CHECK_EQUAL(output, input);
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

BOOST_AUTO_TEST_CASE( ipvfuture )
{
  using namespace rfc3986;

  ipvfuture_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "va028070a183.47qt00:1+5d:38~3:62cf:947a";
    std::string result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    std::cout << result << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( ipliteral )
{
  using namespace rfc3986;

  ipliteral_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "[2a02:8070:a183:0:15d::947a]";
    ast::IPLiteral result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  }
  {
    std::string input = "[va183.47qt0~3:627a]";
    ast::IPLiteral result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( reg_name )
{
  using namespace rfc3986;

  reg_name_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "example_%a1%83.com";
    std::string result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    std::cout << result << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( host )
{
  using namespace rfc3986;

  host_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "[2a02:8070:a183:0:15d::947a]";
    ast::Host result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  }
  {
    std::string input = "[va183.47qt0~3:627a]";
    ast::Host result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
  {
    std::string input = "example_%a1%83.com";
    ast::Host result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
  {
    std::string input = "249.34.199.9";
    ast::Host result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( authority )
{
  using namespace rfc3986;

  authority_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "[2a02:8070:a183:0:15d::947a]";
    ast::Authority result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  }
  {
    std::string input = "[va183.47qt0~3:627a]:503";
    ast::Authority result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
  {
    std::string input = "example_%a1%83.com:8080";
    ast::Authority result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
  {
    std::string input = "tom@249.34.199.9";
    ast::Authority result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( path_ab_empty )
{
  using namespace rfc3986;

  path_ab_empty_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "";
    ast::PathAbEmpty result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    std::cout << '\'';
    for (const std::string& segm : result.m_pathAbEmpty)
        std::cout << '/' << segm;
    std::cout << '\'' << std::endl;
  }
  {
    std::string input = "/";
    ast::PathAbEmpty result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    std::cout << '\'';
    for (const std::string& segm : result.m_pathAbEmpty)
        std::cout << '/' << segm;
    std::cout << '\'' << std::endl;
  }
  {
    std::string input = "/1st-segm/2nd-segm";
    ast::PathAbEmpty result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    std::cout << '\'';
    for (const std::string& segm : result.m_pathAbEmpty)
        std::cout << '/' << segm;
    std::cout << '\'' << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( path_absolute )
{
  using namespace rfc3986;

  path_absolute_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "/";
    ast::PathAbsolute result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    std::cout << '\'' << '/';
    for (const std::string& segm : result.m_pathAbsolute)
        std::cout << '/' << segm;
    std::cout << '\'' << std::endl;
  }
  {
    std::string input = "/1st-segm/2nd-segm";
    ast::PathAbsolute result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    std::cout << '\'';
    for (const std::string& segm : result.m_pathAbsolute)
        std::cout << '/' << segm;
    std::cout << '\'' << std::endl;
  }
}


BOOST_AUTO_TEST_CASE( path_root_less )
{
  using namespace rfc3986;

  path_root_less_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "1st-segm/2nd-segm";
    ast::PathRootLess result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
    std::cout << '\'';
    for (ast::SeqOfStrings::const_iterator iter = result.m_pathRootLess.begin();
        iter != result.m_pathRootLess.end();
        ++iter)
    {
      if (iter != result.m_pathRootLess.begin())
      {
        std::cout << '/';
      }
      std::cout << *iter;
    }
    std::cout << '\'' << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( hier_part )
{
  using namespace rfc3986;

  hier_part_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "[2a02:8070:a183:0:15d::947a]//";
    ast::HierPart result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  }
  {
    std::string input = "[2a02:8070:a183:0:15d::947a]:8080///1st-segm/2nd-segm";
    ast::HierPart result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
  {
    std::string input = "example_%a1%83.com:8080///";
    ast::HierPart result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
  {
    std::string input = "tom@249.34.199.9///1st-segm/2nd-segm";
    ast::HierPart result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
  {
    std::string input = "/1st-segm/2nd-segm";
    ast::HierPart result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
  {
    std::string input = "1st-segm/2nd-segm";
    ast::HierPart result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
  {
    std::string input = "";
    ast::HierPart result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( uri )
{
  using namespace rfc3986;

  //Uri         = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
  uri_grammar<std::string::const_iterator>  grammar;
  {
    std::string input = "http:[2a02:8070:a183:0:15d::947a]//";
    ast::Uri result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  }
  {
    std::string input = "https:[2a02:8070:a183:0:15d::947a]:8080///1st-segm/2nd-segm?whois&arg1#topic3";
    ast::Uri result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
  {
    std::string input = "http:example_%a1%83.com:8080///";
    ast::Uri result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
  }
  {
    std::string input = "ftp:tom@249.34.199.9///1st-segm/2nd-segm";
    ast::Uri result;
    BOOST_CHECK(parse(input.cbegin(), input.cend(), grammar, result));
  //  std::cout << result << std::endl;
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

