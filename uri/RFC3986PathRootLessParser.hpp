#ifndef COAP_RFC3986PathRootLess_PARSER_HPP_
#define COAP_RFC3986PathRootLess_PARSER_HPP_
/*
 * RFC3986PathRootLessParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PathRootLessAst.hpp"
#include "uri/RFC3986SegmentNZParser.hpp"
#include "uri/RFC3986SegmentParser.hpp"
#include <boost/spirit/include/qi.hpp>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct path_root_less_grammar : qi::grammar< Iterator, ast::PathRootLess()>
  {

    path_root_less_grammar();

    qi::rule<Iterator, ast::PathRootLess()>  path_root_less_rule;
    segment_nz_grammar<Iterator>             segment_nz;
    segment_grammar<Iterator>                segment;
  };
} // rfc3986
#endif /* COAP_RFC3986PathRootLess_PARSER_HPP_ */

