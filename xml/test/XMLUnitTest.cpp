/*
 * XMLUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "xml/Scanner.hpp"
#include "xml/Parser.hpp"
#include "xml/ErrorHandler.hpp"
#include <numeric>
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



BOOST_AUTO_TEST_SUITE( xml )


BOOST_AUTO_TEST_CASE( elements )
{
  using namespace xml;
  typedef std::string::const_iterator base_iterator_type;
  typedef lexer::xml_tokens<base_iterator_type> lexer_type;
  typedef lexer_type::iterator_type iterator_type;

  lexer_type  scanner;
//  typedef std::back_insert_iterator<std::string>  StrOutIterType;
//  generator::ipv4_address_grammar<StrOutIterType> generator_grammar;
  {
    std::string input = "<foo></foo>";
    base_iterator_type first = input.begin();
    base_iterator_type last = input.end();
    iterator_type iter = scanner.begin(first, last);
    iterator_type end = scanner.end();
    ast::element result;
    xml::error_handler<base_iterator_type, iterator_type>
        error_handler(first, last);             // Our error handler
    parser::element<iterator_type, lexer_type>  grammar(error_handler, scanner);
    BOOST_CHECK(parse(iter, end, grammar, result));
    BOOST_CHECK_EQUAL(result.name, "foo");
    BOOST_CHECK(result.children.empty());
//    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v4(result), boost::asio::ip::make_address_v4(input));
//    std::string output;
//    StrOutIterType outIter(output);
//    BOOST_CHECK(generate(outIter, generator_grammar, result));
//    BOOST_CHECK_EQUAL(output, input);
  }
  {
    std::string input = "<foo>bar</foo>";
    base_iterator_type first = input.begin();
    base_iterator_type last = input.end();
    iterator_type iter = scanner.begin(first, last);
    iterator_type end = scanner.end();
    ast::element result;
    xml::error_handler<base_iterator_type, iterator_type>
        error_handler(first, last);             // Our error handler
    parser::element<iterator_type, lexer_type>  grammar(error_handler, scanner);
    BOOST_CHECK(parse(iter, end, grammar, result));
    BOOST_CHECK_EQUAL(result.name, "foo");
    BOOST_CHECK_EQUAL(result.children.size(), 1);
  }
  {
    std::string input = "<foo>text1<bar1>text2</bar1>text3<bar2>text4</bar2>text5</foo>";
    base_iterator_type first = input.begin();
    base_iterator_type last = input.end();
    iterator_type iter = scanner.begin(first, last);
    iterator_type end = scanner.end();
    ast::element result;
    xml::error_handler<base_iterator_type, iterator_type>
        error_handler(first, last);             // Our error handler
    parser::element<iterator_type, lexer_type>  grammar(error_handler, scanner);
    BOOST_CHECK(parse(iter, end, grammar, result));
    BOOST_CHECK_EQUAL(result.name, "foo");
    BOOST_CHECK_EQUAL(result.children.size(), 5);
  }
  {
    std::string input = "<foo><bar/></foo>";
    base_iterator_type first = input.begin();
    base_iterator_type last = input.end();
    iterator_type iter = scanner.begin(first, last);
    iterator_type end = scanner.end();
    ast::element result;
    xml::error_handler<base_iterator_type, iterator_type>
        error_handler(first, last);             // Our error handler
    parser::element<iterator_type, lexer_type>  grammar(error_handler, scanner);
    BOOST_CHECK(parse(iter, end, grammar, result));
    BOOST_CHECK_EQUAL(result.name, "foo");
    BOOST_CHECK_EQUAL(result.children.size(), 1);
  }
  {
    std::string input = "<foo><!-- --></foo>";
//    std::string input = "<foo><!-- declarations for <head> & <body> --></foo>";
    base_iterator_type first = input.begin();
    base_iterator_type last = input.end();
    iterator_type iter = scanner.begin(first, last);
    iterator_type end = scanner.end();
    ast::element result;
    xml::error_handler<base_iterator_type, iterator_type>
        error_handler(first, last);             // Our error handler
    parser::element<iterator_type, lexer_type>  grammar(error_handler, scanner);
    BOOST_CHECK(parse(iter, end, grammar, result));
    BOOST_CHECK_EQUAL(result.name, "foo");
    BOOST_CHECK_EQUAL(result.children.size(), 1);
  }
  {
    std::string input = "<foo></bar>";
    base_iterator_type first = input.begin();
    base_iterator_type last = input.end();
    iterator_type iter = scanner.begin(first, last);
    iterator_type end = scanner.end();
    ast::element result;
    xml::error_handler<base_iterator_type, iterator_type>
        error_handler(first, last);             // Our error handler
    parser::element<iterator_type, lexer_type>  grammar(error_handler, scanner);
    BOOST_CHECK(!parse(iter, end, grammar, result));
  }

}

BOOST_AUTO_TEST_SUITE_END()

