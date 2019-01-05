#ifndef COAP_RFC3986Segment_PARSER_DEF_HPP_
#define COAP_RFC3986Segment_PARSER_DEF_HPP_
/*
 * RFC3986SegmentParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986SegmentParser.hpp"
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
  segment_grammar<Iterator>::segment_grammar()
  : segment_grammar::base_type( segment_rule, "segment" )
  {
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    //              segment       = *pchar
    segment_rule %=
          *pchar
        ;

    segment_rule.name("segment");
  //  debug(segment_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(segment_rule);

  //  on_error<fail>
  //  (
  //    segment_rule,
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

#endif /* COAP_RFC3986Segment_PARSER_DEF_HPP_ */

