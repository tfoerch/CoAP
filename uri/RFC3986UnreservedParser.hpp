#ifndef COAP_RFC3986Unreserved_PARSER_HPP_
#define COAP_RFC3986Unreserved_PARSER_HPP_
/*
 * RFC3986UnreservedParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/spirit/include/qi.hpp>
#include <boost/cstdint.hpp>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct unreserved_grammar : qi::grammar< Iterator, char()>
  {

    unreserved_grammar();

    qi::rule<Iterator, char()>  unreserved_rule;
  };
} // rfc3986

#endif /* COAP_RFC3986Unreserved_PARSER_HPP_ */

