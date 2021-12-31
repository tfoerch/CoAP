#ifndef COAP_RFC3986RegName_PARSER_HPP_
#define COAP_RFC3986RegName_PARSER_HPP_
/*
 * RFC3986RegNameParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986UnreservedParser.hpp"
#include "uri/RFC3986PercentEncodedParser.hpp"
#include "uri/RFC3986SubDelimsParser.hpp"
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <string>

namespace rfc3986
{
  namespace qi = boost::spirit::qi;

  template < typename Iterator >
  struct reg_name_grammar : qi::grammar< Iterator, std::string()>
  {

    reg_name_grammar();

    qi::rule<Iterator, std::string()>  reg_name_rule;
    unreserved_grammar<Iterator>       unreserved;
    percent_encoded_grammar<Iterator>  percent_encoded;
    sub_delims_grammar<Iterator>       sub_delims;
  };
} // rfc3986
#endif /* COAP_RFC3986RegName_PARSER_HPP_ */

