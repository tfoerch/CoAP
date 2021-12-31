#ifndef COAP_RFC3986PercentEncoded_PARSER_HPP_
#define COAP_RFC3986PercentEncoded_PARSER_HPP_
/*
 * RFC3986PercentEncodedParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/spirit/include/qi.hpp>
#include <cstdint>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct percent_encoded_grammar : qi::grammar< Iterator, char()>
  {

    percent_encoded_grammar();

    qi::rule<Iterator, char()>  percent_encoded_rule;
  };
} // rfc3986

#endif /* COAP_RFC3986PercentEncoded_PARSER_HPP_ */

