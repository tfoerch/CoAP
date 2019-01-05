#ifndef COAP_RFC3986QueryAndFragment_PARSER_DEF_HPP_
#define COAP_RFC3986QueryAndFragment_PARSER_DEF_HPP_
/*
 * RFC3986QueryAndFragmentParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986QueryAndFragmentParser.hpp"
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
  query_fragment_grammar<Iterator>::query_fragment_grammar()
  : query_fragment_grammar::base_type( query_fragment_rule, "query_fragment" )
  {
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    //              query       = *( pchar / "/" / "?" )
    //              fragment    = *( pchar / "/" / "?" )
    query_fragment_rule %=
          *( pchar |
             char_('/') |
             char_('?') )
        ;

    query_fragment_rule.name("query_fragment");
  //  debug(query_fragment_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(query_fragment_rule);

  //  on_error<fail>
  //  (
  //    query_fragment_rule,
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

#endif /* COAP_RFC3986QueryAndFragment_PARSER_DEF_HPP_ */

