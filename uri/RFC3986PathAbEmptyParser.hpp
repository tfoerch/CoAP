#ifndef COAP_RFC3986PathAbEmpty_PARSER_HPP_
#define COAP_RFC3986PathAbEmpty_PARSER_HPP_
/*
 * RFC3986PathAbEmptyParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PathAbEmptyAst.hpp"
#include "uri/RFC3986SegmentParser.hpp"
#include <boost/spirit/include/qi.hpp>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct path_ab_empty_grammar : qi::grammar< Iterator, ast::PathAbEmpty()>
  {

    path_ab_empty_grammar();

    qi::rule<Iterator, ast::PathAbEmpty()>  path_ab_empty_rule;
    segment_grammar<Iterator>               segment;
  };
} // rfc3986
#endif /* COAP_RFC3986PathAbEmpty_PARSER_HPP_ */

