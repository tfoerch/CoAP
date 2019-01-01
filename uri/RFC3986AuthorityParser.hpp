#ifndef COAP_RFC3986Authority_PARSER_HPP_
#define COAP_RFC3986Authority_PARSER_HPP_
/*
 * RFC3986AuthorityParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986AuthorityAst.hpp"
#include "uri/RFC3986UserInfoParser.hpp"
#include "uri/RFC3986HostParser.hpp"
#include "uri/RFC3986PortParser.hpp"
#include <boost/spirit/include/qi.hpp>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct authority_grammar : qi::grammar< Iterator, ast::Authority()>
  {

    authority_grammar();

    qi::rule<Iterator, ast::Authority()>  authority_rule;
    user_info_grammar<Iterator>           user_info;
    host_grammar<Iterator>                host;
    port_grammar<Iterator>                port;
  };
} // rfc3986
#endif /* COAP_RFC3986Authority_PARSER_HPP_ */

