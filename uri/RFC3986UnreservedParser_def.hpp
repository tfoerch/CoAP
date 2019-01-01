#ifndef COAP_RFC3986Unreserved_PARSER_DEF_HPP_
#define COAP_RFC3986Unreserved_PARSER_DEF_HPP_
/*
 * RFC3986UnreservedParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986UnreservedParser.hpp"
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
  unreserved_grammar<Iterator>::unreserved_grammar()
  : unreserved_grammar::base_type( unreserved_rule, "unreserved" )
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

    //unreserved  = ALPHA / DIGIT / "-" / "." / "_" / "~"
    unreserved_rule %=
        alnum |
        char_('-') |
        char_('.') |
        char_('_') |
        char_('~')
        ;

    unreserved_rule.name("unreserved");
  //  debug(unreserved_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(unreserved_rule);

  }
} // rfc3986

#endif /* COAP_RFC3986Unreserved_PARSER_DEF_HPP_ */

