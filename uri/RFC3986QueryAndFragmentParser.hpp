#ifndef COAP_RFC3986QueryAndFragment_PARSER_HPP_
#define COAP_RFC3986QueryAndFragment_PARSER_HPP_
/*
 * RFC3986QueryAndFragmentParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PCharParser.hpp"
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <string>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct query_fragment_grammar : qi::grammar< Iterator, std::string()>
  {

    query_fragment_grammar();

    qi::rule<Iterator, std::string()>  query_fragment_rule;
    pchar_grammar<Iterator>            pchar;
  };
} // rfc3986
#endif /* COAP_RFC3986QueryAndFragment_PARSER_HPP_ */

