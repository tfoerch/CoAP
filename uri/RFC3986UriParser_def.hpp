#ifndef COAP_RFC3986Uri_PARSER_DEF_HPP_
#define COAP_RFC3986Uri_PARSER_DEF_HPP_
/*
 * RFC3986UriParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986UriParser.hpp"
#include "uri/RFC3986UriAstAdapted.hpp"
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
  uri_grammar<Iterator>::uri_grammar()
  : uri_grammar::base_type( uri_rule, "uri" )
  {
    using qi::_1;
    using namespace qi::labels;
    using qi::on_error;
    using qi::fail;
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::val;

    //Uri         = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
    uri_rule %=
           scheme
        >> ':'
        >> hier_part
        >> -(    '?'
              >> query_fragment ) // query
        >> -(    '#'
              >> query_fragment ) // fragment
        ;


    uri_rule.name("uri");
  //  debug(uri_rule);
  //  BOOST_SPIRIT_DEBUG_NODE(uri_rule);

  //  on_error<fail>
  //  (
  //    uri_rule,
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

//#include <boost/spirit/include/phoenix.hpp>
//
//#include <stdexcept>
//
//namespace qi = boost::spirit::qi;
//
//using boost::spirit::unicode::char_;
//using boost::spirit::eol;
//
//namespace my_helpers {
//    void cp2utf8(std::string& a, UChar32 codepoint)
//    {
//        icu::StringByteSink<std::string> bs(&a);
//        icu::UnicodeString::fromUTF32(&codepoint, 1).toUTF8( bs );
//    }
//
//    template<typename Iterator>
//        std::string make_error_message(boost::spirit::info const& info, Iterator first, Iterator last) {
//            std::ostringstream oss;
//            oss << "Illegal escape sequence. Expecting " << info << " here: \"" << std::string(first,last) << "\"";
//            return oss.str();
//        }
//}
//
//BOOST_PHOENIX_ADAPT_FUNCTION(void,        cp2utf8_,            my_helpers::cp2utf8,            2)
//BOOST_PHOENIX_ADAPT_FUNCTION(std::string, make_error_message_, my_helpers::make_error_message, 3)
//
//template < typename Iterator >
//QuotedString<Iterator>::QuotedString()
//: QuotedString::base_type( quoted_string )
//{
//  quoted_string =
//      '"' > *( +( char_ - ( '"' | eol | '\\' ) ) | escapes ) > '"';
//
//  escapes =
//      '\\' > (
//                  escaped_character
//                | ("x" > qi::uint_parser<UChar32, 16, 2, 2>())
//                | ("u" > qi::uint_parser<UChar32, 16, 4, 4>())
//                | ("U" > qi::uint_parser<UChar32, 16, 8, 8>())
//                | (      qi::uint_parser<UChar32,  8, 1, 3>())
//              ) [ cp2utf8_( qi::_val, qi::_1 ) ]
//        ;
//
//        escaped_character.add
//            (  "a", 0x07 ) // alert
//            (  "b", 0x08 ) // backspace
//            (  "f", 0x0c ) // form feed
//            (  "n", 0x0a ) // new line
//            (  "r", 0x0d ) // carriage return
//            (  "t", 0x09 ) // horizontal tab
//            (  "v", 0x0b ) // vertical tab
//            ( "\"", 0x22 ) // literal quotation mark
//            ( "\\", 0x5c ) // literal backslash
//        ;
//
//        namespace phx = boost::phoenix;
//
//        qi::on_error< qi::fail > (
//            escapes,
//            phx::throw_(
//                phx::construct<std::runtime_error>( make_error_message_(qi::_4, qi::_3, qi::_2) )
//            )
//        );
//
//        qi::on_error< qi::fail > (
//            quoted_string,
//            phx::throw_(
//                phx::construct<std::runtime_error>( "Illegal string literal. (Unterminated string?)" )
//            )
//        );
//
//}

#endif /* COAP_RFC3986Uri_PARSER_DEF_HPP_ */

