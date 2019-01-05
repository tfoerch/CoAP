#ifndef COAP_RFC3986Scheme_PARSER_DEF_HPP_
#define COAP_RFC3986Scheme_PARSER_DEF_HPP_
/*
 * RFC3986SchemeParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986SchemeParser.hpp"
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
  scheme_grammar<Iterator>::scheme_grammar()
  : scheme_grammar::base_type( scheme_rule, "scheme" )
  {
    using boost::spirit::ascii::alpha;
    using boost::spirit::ascii::digit;
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::push_back;
    using phoenix::construct;
    using phoenix::val;

    // scheme      = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
    scheme_rule %=
           alpha
        >> *scheme_tail_char
        ;

    scheme_tail_char %=
        alpha |
        digit |
        char_('+') |
        char_('-') |
        char_('.')
        ;


    scheme_rule.name("scheme");
  //  debug(scheme_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(scheme_rule);

  //  on_error<fail>
  //  (
  //    scheme_rule,
  //    std::cout
  //          << val("Error! Expecting ")
  //          << _4                               // what failed?
  //          << val(" here: \"")
  //          << construct<std::string>(_3, _2)   // iterators to error-pos, end
  //          << val("\"")
  //          << std::endl
  //  );
  }
} // rfc3986

#endif /* COAP_RFC3986Scheme_PARSER_DEF_HPP_ */

