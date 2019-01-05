#ifndef COAP_RFC3986PathAbsolute_PARSER_DEF_HPP_
#define COAP_RFC3986PathAbsolute_PARSER_DEF_HPP_
/*
 * RFC3986PathAbsoluteParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PathAbsoluteParser.hpp"
#include "uri/RFC3986PathAbsoluteAstAdapted.hpp"
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
  path_absolute_grammar<Iterator>::path_absolute_grammar()
  : path_absolute_grammar::base_type( path_absolute_rule, "path_absolute" )
  {
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::push_back;
    using phoenix::construct;
    using phoenix::val;

    //path-absolute = "/" [ segment-nz *( "/" segment ) ]
    path_absolute_rule =
           '/'
        >> -(    segment_nz [ push_back(at_c<0>(_val), _1) ]
              >> *(    '/'
                    >> segment ) [ push_back(at_c<0>(_val), _1) ] )
        ;

    path_absolute_rule.name("path_absolute");
  //  debug(path_absolute_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(path_absolute_rule);

  //  on_error<fail>
  //  (
  //    path_absolute_rule,
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

#endif /* COAP_RFC3986PathAbsolute_PARSER_DEF_HPP_ */

