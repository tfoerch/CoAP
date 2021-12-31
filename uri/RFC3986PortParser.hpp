#ifndef COAP_RFC3986Port_PARSER_HPP_
#define COAP_RFC3986Port_PARSER_HPP_
/*
 * RFC3986PortParser.hpp
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
  struct port_grammar : qi::grammar< Iterator, std::uint16_t()>
  {

    port_grammar();

    qi::rule<Iterator, std::uint16_t()>  port_rule;
  };
} // rfc3986
#endif /* COAP_RFC3986Port_PARSER_HPP_ */

