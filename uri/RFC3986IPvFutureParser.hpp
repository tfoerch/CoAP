#ifndef COAP_RFC3986IPvFuture_PARSER_HPP_
#define COAP_RFC3986IPvFuture_PARSER_HPP_
/*
 * RFC3986IPvFutureParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986UnreservedParser.hpp"
#include "uri/RFC3986SubDelimsParser.hpp"
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <string>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct ipvfuture_grammar : qi::grammar< Iterator, std::string()>
  {

    ipvfuture_grammar();

    qi::rule<Iterator, std::string()>  ipvfuture_rule;
    qi::rule<Iterator, char()>         allowedChars_rule;
    unreserved_grammar<Iterator>       unreserved;
    sub_delims_grammar<Iterator>       sub_delims;
  };
} // rfc3986
#endif /* COAP_RFC3986IPvFuture_PARSER_HPP_ */

