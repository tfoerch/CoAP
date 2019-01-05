#ifndef COAP_RFC3986Scheme_PARSER_HPP_
#define COAP_RFC3986Scheme_PARSER_HPP_
/*
 * RFC3986SchemeParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/spirit/include/qi.hpp>
#include <string>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct scheme_grammar : qi::grammar< Iterator, std::string()>
  {
    scheme_grammar();

    qi::rule<Iterator, std::string()>  scheme_rule;
    qi::rule<Iterator, char()>         scheme_tail_char;
  };
} // rfc3986
#endif /* COAP_RFC3986Scheme_PARSER_HPP_ */

