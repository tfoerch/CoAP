#ifndef COAP_RFC3986PChar_PARSER_DEF_HPP_
#define COAP_RFC3986PChar_PARSER_DEF_HPP_
/*
 * RFC3986PCharParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PCharParser.hpp"
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;
  namespace fusion = boost::fusion;
  namespace phoenix = boost::phoenix;


  template < typename Iterator >
  pchar_grammar<Iterator>::pchar_grammar()
  : pchar_grammar::base_type( pchar_rule, "pchar" )
  {
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    //pchar         = unreserved / pct-encoded / sub-delims / ":" / "@"
    pchar_rule %=
        unreserved |
        percent_encoded |
        sub_delims |
        char_(':') |
        char_('@')
        ;

    pchar_rule.name("pchar");
  //  debug(pchar_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(pchar_rule);

  }
} // rfc3986

#endif /* COAP_RFC3986PChar_PARSER_DEF_HPP_ */

