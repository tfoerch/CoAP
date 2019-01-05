#ifndef COAP_RFC3986PathEmpty_PARSER_DEF_HPP_
#define COAP_RFC3986PathEmpty_PARSER_DEF_HPP_
/*
 * RFC3986PathEmptyParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PathEmptyParser.hpp"
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
  path_empty_grammar<Iterator>::path_empty_grammar()
  : path_empty_grammar::base_type( path_empty_rule, "path_empty" )
  {
    using qi::eps;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::push_back;
    using phoenix::construct;
    using phoenix::val;

    //path-abempty  = *( "/" segment )
    path_empty_rule =
        eps;

    path_empty_rule.name("path_empty");
  //  debug(path_empty_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(path_empty_rule);

  //  on_error<fail>
  //  (
  //    path_empty_rule,
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

#endif /* COAP_RFC3986PathEmpty_PARSER_DEF_HPP_ */

