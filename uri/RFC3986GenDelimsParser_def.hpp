#ifndef COAP_RFC3986GenDelims_PARSER_DEF_HPP_
#define COAP_RFC3986GenDelims_PARSER_DEF_HPP_
/*
 * RFC3986GenDelimsParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986GenDelimsParser.hpp"
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
  gen_delims_grammar<Iterator>::gen_delims_grammar()
  : gen_delims_grammar::base_type( gen_delims_rule, "gen_delims" )
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

    //gen-delims  = ":" / "/" / "?" / "#" / "[" / "]" / "@"
    //
    gen_delims_rule %=
        char_(':') |
        char_('/') |
        char_('?') |
        char_('#') |
        char_('[') |
        char_(']') |
        char_('@')
        ;

    gen_delims_rule.name("gen_delims");
  //  debug(gen_delims_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(gen_delims_rule);

  }
} // rfc3986

#endif /* COAP_RFC3986GenDelims_PARSER_DEF_HPP_ */

