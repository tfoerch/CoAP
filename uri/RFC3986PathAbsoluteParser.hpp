#ifndef COAP_RFC3986PathAbsolute_PARSER_HPP_
#define COAP_RFC3986PathAbsolute_PARSER_HPP_
/*
 * RFC3986PathAbsoluteParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PathAbsoluteAst.hpp"
#include "uri/RFC3986SegmentNZParser.hpp"
#include "uri/RFC3986SegmentParser.hpp"
#include <boost/spirit/include/qi.hpp>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct path_absolute_grammar : qi::grammar< Iterator, ast::PathAbsolute()>
  {

    path_absolute_grammar();

    qi::rule<Iterator, ast::PathAbsolute()>  path_absolute_rule;
    segment_nz_grammar<Iterator>             segment_nz;
    segment_grammar<Iterator>                segment;
  };
} // rfc3986
#endif /* COAP_RFC3986PathAbsolute_PARSER_HPP_ */

