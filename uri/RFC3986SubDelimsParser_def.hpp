#ifndef COAP_RFC3986SubDelims_PARSER_DEF_HPP_
#define COAP_RFC3986SubDelims_PARSER_DEF_HPP_
/*
 * RFC3986SubDelimsParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986SubDelimsParser.hpp"
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
  sub_delims_grammar<Iterator>::sub_delims_grammar()
  : sub_delims_grammar::base_type( sub_delims_rule, "sub_delims" )
  {
    using boost::spirit::ascii::alnum;
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    //sub-delims  = "!" / "$" / "&" / "'" / "(" / ")"
    //            / "*" / "+" / "," / ";" / "="
    sub_delims_rule %=
        char_('!') |
        char_('$') |
        char_('&') |
        char_('\'') |
        char_('(') |
        char_(')') |
        char_('*') |
        char_('+') |
        char_(',') |
        char_(';') |
        char_('=')
        ;

    sub_delims_rule.name("sub_delims");
  //  debug(sub_delims_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(sub_delims_rule);

  }
} // rfc3986

#endif /* COAP_RFC3986SubDelims_PARSER_DEF_HPP_ */

