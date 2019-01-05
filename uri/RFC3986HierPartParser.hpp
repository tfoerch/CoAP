#ifndef COAP_RFC3986HierPart_PARSER_HPP_
#define COAP_RFC3986HierPart_PARSER_HPP_
/*
 * RFC3986HierPartParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986HierPartAst.hpp"
#include "uri/RFC3986AuthorityParser.hpp"
#include "uri/RFC3986PathAbEmptyParser.hpp"
#include "uri/RFC3986PathAbsoluteParser.hpp"
#include "uri/RFC3986PathRootLessParser.hpp"
#include "uri/RFC3986PathEmptyParser.hpp"
#include <boost/spirit/include/qi.hpp>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct hier_part_grammar : qi::grammar< Iterator, ast::HierPart()>
  {

    hier_part_grammar();

    qi::rule<Iterator, ast::HierPart()>  hier_part_rule;
    authority_grammar<Iterator>          authority;
    path_ab_empty_grammar<Iterator>      path_ab_empty;
    path_absolute_grammar<Iterator>      path_absolute;
    path_root_less_grammar<Iterator>     path_root_less;
    path_empty_grammar<Iterator>         path_empty;
  };
} // rfc3986
#endif /* COAP_RFC3986HierPart_PARSER_HPP_ */

