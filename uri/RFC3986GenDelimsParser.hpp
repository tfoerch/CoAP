#ifndef COAP_RFC3986GenDelims_PARSER_HPP_
#define COAP_RFC3986GenDelims_PARSER_HPP_
/*
 * RFC3986GenDelimsParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/spirit/include/qi.hpp>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct gen_delims_grammar : qi::grammar< Iterator, char()>
  {

    gen_delims_grammar();

    qi::rule<Iterator, char()>  gen_delims_rule;
  };
} // rfc3986

#endif /* COAP_RFC3986GenDelims_PARSER_HPP_ */

