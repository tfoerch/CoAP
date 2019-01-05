#ifndef COAP_RFC3986HierPart_PARSER_DEF_HPP_
#define COAP_RFC3986HierPart_PARSER_DEF_HPP_
/*
 * RFC3986HierPartParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986HierPartParser.hpp"
#include "uri/RFC3986HierPartAstAdapted.hpp"
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
  hier_part_grammar<Iterator>::hier_part_grammar()
  : hier_part_grammar::base_type( hier_part_rule, "hier_part" )
  {
    using boost::spirit::ascii::xdigit;
    using boost::spirit::ascii::alnum;
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    //hier-part   = "//" authority path-abempty
    //            / path-absolute
    //            / path-rootless
    //            / path-empty
    hier_part_rule %=
        (    "//"
          >> authority
          >> path_ab_empty ) |
        path_absolute |
        path_root_less |
        path_empty
        ;


    hier_part_rule.name("hier_part");
  //  debug(hier_part_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(hier_part_rule);

  //  on_error<fail>
  //  (
  //    hier_part_rule,
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

#endif /* COAP_RFC3986HierPart_PARSER_DEF_HPP_ */

