#ifndef COAP_RFC3986IPLiteral_PARSER_HPP_
#define COAP_RFC3986IPLiteral_PARSER_HPP_
/*
 * RFC3986IPLiteralParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986IPLiteralAst.hpp"
#include "uri/RFC3986IPv6AddressParser.hpp"
#include "uri/RFC3986IPvFutureParser.hpp"
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <string>


namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct ipliteral_grammar : qi::grammar< Iterator, ast::IPLiteral()>
  {

    ipliteral_grammar();

    qi::rule<Iterator, ast::IPLiteral()>  ipliteral_rule;
    ipv6_address_grammar<Iterator>        ipv6_address;
    ipvfuture_grammar<Iterator>           ipvfuture;
  };
} // rfc3986
#endif /* COAP_RFC3986IPLiteral_PARSER_HPP_ */

