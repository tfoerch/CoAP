#ifndef COAP_RFC3986PathRootLess_PARSER_DEF_HPP_
#define COAP_RFC3986PathRootLess_PARSER_DEF_HPP_
/*
 * RFC3986PathRootLessParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PathRootLessParser.hpp"
#include "uri/RFC3986PathRootLessAstAdapted.hpp"
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
  path_root_less_grammar<Iterator>::path_root_less_grammar()
  : path_root_less_grammar::base_type( path_root_less_rule, "path_root_less" )
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

    //path-rootless = segment-nz *( "/" segment )
    path_root_less_rule =
            segment_nz [ push_back(at_c<0>(_val), _1) ]
         >> *(    '/'
               >> segment [ push_back(at_c<0>(_val), _1) ] )
        ;

    path_root_less_rule.name("path_root_less");
  //  debug(path_root_less_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(path_root_less_rule);

  //  on_error<fail>
  //  (
  //    path_root_less_rule,
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

#endif /* COAP_RFC3986PathRootLess_PARSER_DEF_HPP_ */

