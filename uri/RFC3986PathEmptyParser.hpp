#ifndef COAP_RFC3986PathEmpty_PARSER_HPP_
#define COAP_RFC3986PathEmpty_PARSER_HPP_
/*
 * RFC3986PathEmptyParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PathEmptyAst.hpp"
#include <boost/spirit/include/qi.hpp>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct path_empty_grammar : qi::grammar< Iterator, ast::PathEmpty()>
  {

    path_empty_grammar();

    qi::rule<Iterator, ast::PathEmpty()>  path_empty_rule;
  };
} // rfc3986
#endif /* COAP_RFC3986PathEmpty_PARSER_HPP_ */

