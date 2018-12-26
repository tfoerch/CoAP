#ifndef COAP_URI_PARSER_HPP_
#define COAP_URI_PARSER_HPP_
/*
 * UriParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */
#define BOOST_SPIRIT_UNICODE

#include <boost/spirit/include/qi.hpp>

#include <unicode/unistr.h>
#include <unicode/bytestream.h>

#include <string>

namespace qi = boost::spirit::qi;

template < typename Iterator >
struct QuotedString : qi::grammar< Iterator, std::string() >
{
  QuotedString();
  qi::rule< Iterator, std::string() > quoted_string;
  qi::rule< Iterator, std::string() > escapes;
  qi::symbols< char const, UChar32 > escaped_character;
};
#endif /* COAP_URI_PARSER_HPP_ */

