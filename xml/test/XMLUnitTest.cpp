/*
 * XMLUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "xml/Scanner.hpp"
#include "xml/Parser.hpp"
#include "xml/ErrorHandler.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/optional/optional_io.hpp>

#include <boost/bind/bind.hpp>
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

namespace qi = boost::spirit::qi;
namespace lex = boost::spirit::lex;

enum token_ids
{
  etag_begin = lex::tokenids::min_token_id + 1,
  tag_begin,
  emptyElem_tag_end,
  tag_end,
  etag_mark,
  declaration_mark,
  name,
  char_data
};

template <typename Lexer>
struct test_xml_tokens : lex::lexer<Lexer>
{
  test_xml_tokens()
  {
    m_name = "[:a-zA-Z_][:a-zA-Z_0-9]*";
    m_char_data = "[ \t\n\r]+[^<&>/]+";
    this->self.add
         (m_name, name)
         (m_char_data, char_data)
         ("<\\/", etag_begin)
         ("<", tag_begin)
         ("\\/>", emptyElem_tag_end)
         (">", tag_end)
         ("\\/", etag_mark)
         ("!", declaration_mark)
         ;
  }
  lex::token_def<std::string> m_name;
  lex::token_def<std::string> m_char_data;
};


template <typename Iterator>
struct PrintTokens : boost::spirit::qi::grammar<Iterator>
{
  template <typename Token>
  explicit PrintTokens(const Token& tokens)
  : PrintTokens::base_type(start, "start")
  {
    using qi::debug;
    using boost::spirit::_1;
    start =  *(   qi::tokenid(xml::token_ids::etag_begin)
              |   qi::tokenid(xml::token_ids::tag_begin)
              |   qi::tokenid(xml::token_ids::emptyElem_tag_end)
              |   qi::tokenid(xml::token_ids::tag_end)
              |   qi::tokenid(xml::token_ids::etag_mark)
              |   qi::tokenid(xml::token_ids::declaration_mark)
              |   qi::tokenid(xml::token_ids::name)
              |   qi::tokenid(xml::token_ids::char_data)
              )
              [ std::cout << _1  << "\n" ]
          ;
    start.name("start");
    BOOST_SPIRIT_DEBUG_NODES(
        (start)
    );
  }

  qi::rule<Iterator> start;
};

struct LogTokens
{
  using result_type = bool;
  // typedef std::string::iterator base_iterator_type;
  typedef std::string::const_iterator base_iterator_type;
  typedef boost::mpl::vector<std::string> token_value_types;
  typedef boost::spirit::lex::lexertl::token<base_iterator_type, token_value_types, boost::mpl::true_> token_type;
  bool operator()(const token_type& token) const
  {
    switch(token.id())
    {
      case xml::token_ids::etag_begin:
        std::cout << token.id() << " '</'" << std::endl;
        break;
      case xml::token_ids::tag_begin:
        std::cout << token.id() << " '<'" << std::endl;
        break;
      case xml::token_ids::emptyElem_tag_end:
        std::cout << token.id() << " '/>'" << std::endl;
        break;
      case xml::token_ids::tag_end:
        std::cout << token.id() << " '>'" << std::endl;
        break;
      case xml::token_ids::etag_mark:
        std::cout << token.id() << " '/'" << std::endl;
        break;
      case xml::token_ids::declaration_mark:
        std::cout << token.id() << " '!'" << std::endl;
        break;
      case xml::token_ids::name:
        std::cout << token.id() << "name" << token.value() << std::endl;
        break;
      default:
        std::cout << "LogTokens::operator(): " << token.id() << std::endl;
        break;
    }
    return true;
  }
};



BOOST_AUTO_TEST_SUITE( xml )


BOOST_AUTO_TEST_CASE( elements )
{
  using namespace xml;
  namespace lex = boost::spirit::lex;
//  typedef std::string::iterator base_iterator_type;
  typedef std::string::const_iterator base_iterator_type;
  typedef boost::mpl::vector<std::string> token_value_types;
//  typedef lex::lexertl::token<base_iterator_type, token_value_types, boost::mpl::true_, xml::token_ids::type> token_type;
  typedef lex::lexertl::token<base_iterator_type, token_value_types, boost::mpl::true_> token_type;
//  typedef lex::lexertl::position_token<base_iterator_type, token_value_types, boost::mpl::true_> token_type;
  typedef xml::lexer::xml_tokens<lex::lexertl::actor_lexer<token_type>> xml_lexer_type;
  typedef test_xml_tokens <lex::lexertl::actor_lexer<token_type>> test_xml_lexer_type;
  typedef xml_lexer_type::lexer_type lexer_type;
  typedef lexer_type::iterator_type iterator_type;
//  template bool LogTokens::operator(const token_type&);

  xml_lexer_type  scanner;
  test_xml_lexer_type  test_scanner;
//  typedef std::back_insert_iterator<std::string>  StrOutIterType;
//  generator::ipv4_address_grammar<StrOutIterType> generator_grammar;
  {
    std::string input = "<foo></foo>";
#if 0
    {
      using boost::placeholders::_1;
      base_iterator_type first = input.begin();
      base_iterator_type last = input.end();
      BOOST_CHECK(lex::tokenize(first, last, scanner, boost::bind(LogTokens(), _1)));
    }
    {
      base_iterator_type first = input.begin();
      base_iterator_type last = input.end();
      PrintTokens<iterator_type>  printTokens(scanner);
      BOOST_CHECK(lex::tokenize_and_parse(first, last, scanner, printTokens));
    }
#endif
    {
      base_iterator_type first = input.begin();
      base_iterator_type last = input.end();
      parser::element<iterator_type>  grammar(scanner);
      ast::Element result;
      BOOST_CHECK(lex::tokenize_and_parse(first, last, scanner, grammar, result));
      BOOST_CHECK_EQUAL(result.name, "foo");
      BOOST_CHECK(result.children.empty());
    }
//    iterator_type iter = scanner.begin(first, last);
//    iterator_type end = scanner.end();
//    xml::error_handler<base_iterator_type, iterator_type>
//        error_handler(first, last);             // Our error handler
//    BOOST_CHECK(parse(iter, end, grammar, result));
//    BOOST_CHECK_EQUAL(boost::asio::ip::make_address_v4(result), boost::asio::ip::make_address_v4(input));
//    std::string output;
//    StrOutIterType outIter(output);
//    BOOST_CHECK(generate(outIter, generator_grammar, result));
//    BOOST_CHECK_EQUAL(output, input);
  }
  {
    std::string input = "<foo>bar</foo>";
    {
      base_iterator_type first = input.begin();
      base_iterator_type last = input.end();
      ast::Element result;
      parser::element<iterator_type>  grammar(scanner);
      BOOST_CHECK(lex::tokenize_and_parse(first, last, scanner, grammar, result));
      BOOST_CHECK_EQUAL(result.name, "foo");
      BOOST_CHECK_EQUAL(result.children.size(), 1);
    }
  }
  {
    std::string input = "<foo>text1<bar1>text2</bar1>text3<bar2>text4</bar2>text5</foo>";
    {
      base_iterator_type first = input.begin();
      base_iterator_type last = input.end();
      ast::Element result;
      parser::element<iterator_type>  grammar(scanner);
      BOOST_CHECK(lex::tokenize_and_parse(first, last, scanner, grammar, result));
      BOOST_CHECK_EQUAL(result.name, "foo");
      BOOST_CHECK_EQUAL(result.children.size(), 5);
    }
  }
#if 0
  {
    std::string input = "<foo><bar/></foo>";
    base_iterator_type first = input.begin();
    base_iterator_type last = input.end();
    iterator_type iter = scanner.begin(first, last);
    iterator_type end = scanner.end();
    ast::Element result;
    xml::error_handler<base_iterator_type, iterator_type>
        error_handler(first, last);             // Our error handler
    parser::element<iterator_type, lexer_type>  grammar(error_handler, scanner);
    BOOST_CHECK(parse(iter, end, grammar, result));
    BOOST_CHECK_EQUAL(result.name, "foo");
    BOOST_CHECK_EQUAL(result.children.size(), 1);
  }
  {
//    std::string input = "<foo><!-- --></foo>";
    std::string input = "<foo><!-- declarations for <head> & <body> --></foo>";
    base_iterator_type first = input.begin();
    base_iterator_type last = input.end();
    iterator_type iter = scanner.begin(first, last);
    iterator_type end = scanner.end();
    ast::Element result;
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
    ast::Element result;
    xml::error_handler<base_iterator_type, iterator_type>
        error_handler(first, last);             // Our error handler
    parser::element<iterator_type, lexer_type>  grammar(error_handler, scanner);
    BOOST_CHECK(!parse(iter, end, grammar, result));
  }
#endif
}

BOOST_AUTO_TEST_SUITE_END()

