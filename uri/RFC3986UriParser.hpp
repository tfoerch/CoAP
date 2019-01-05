#ifndef COAP_RFC3986Uri_PARSER_HPP_
#define COAP_RFC3986Uri_PARSER_HPP_
/*
 * RFC3986UriParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */
#define BOOST_SPIRIT_UNICODE

#include "uri/RFC3986UriAst.hpp"
#include "uri/RFC3986SchemeParser.hpp"
#include "uri/RFC3986HierPartParser.hpp"
#include "uri/RFC3986QueryAndFragmentParser.hpp"
#include <boost/spirit/include/qi.hpp>

//#include <unicode/unistr.h>
//#include <unicode/bytestream.h>
//
//#include <string>
//
//namespace qi = boost::spirit::qi;
//
//template < typename Iterator >
//struct QuotedString : qi::grammar< Iterator, std::string() >
//{
//  QuotedString();
//  qi::rule< Iterator, std::string() > quoted_string;
//  qi::rule< Iterator, std::string() > escapes;
//  qi::symbols< char const, UChar32 > escaped_character;
//};

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct uri_grammar : qi::grammar< Iterator, ast::Uri()>
  {
    uri_grammar();

    qi::rule<Iterator, ast::Uri()>    uri_rule;
    scheme_grammar<Iterator>          scheme;
    hier_part_grammar<Iterator>       hier_part;
    query_fragment_grammar<Iterator>  query_fragment;
  };
} // rfc3986

#endif /* COAP_RFC3986Uri_PARSER_HPP_ */

