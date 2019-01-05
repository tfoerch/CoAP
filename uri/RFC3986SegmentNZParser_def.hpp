#ifndef COAP_RFC3986SegmentNZ_PARSER_DEF_HPP_
#define COAP_RFC3986SegmentNZ_PARSER_DEF_HPP_
/*
 * RFC3986SegmentNZParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986SegmentNZParser.hpp"
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
  segment_nz_grammar<Iterator>::segment_nz_grammar()
  : segment_nz_grammar::base_type( segment_nz_rule, "segment_nz" )
  {
    using qi::char_;
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    //              segment-nz    = 1*pchar
    segment_nz_rule %=
          +pchar
        ;

    segment_nz_rule.name("segment_nz");
  //  debug(segment_nz_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(segment_nz_rule);

  //  on_error<fail>
  //  (
  //    segment_nz_rule,
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

#endif /* COAP_RFC3986SegmentNZ_PARSER_DEF_HPP_ */

