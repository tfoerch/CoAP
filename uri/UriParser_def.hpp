#ifndef COAP_URI_PARSER_DEF_HPP_
#define COAP_URI_PARSER_DEF_HPP_
/*
 * UriParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/UriParser.hpp"

#include <boost/spirit/include/phoenix.hpp>

#include <stdexcept>

namespace qi = boost::spirit::qi;

using boost::spirit::unicode::char_;
using boost::spirit::eol;

namespace my_helpers {
    void cp2utf8(std::string& a, UChar32 codepoint)
    {
        icu::StringByteSink<std::string> bs(&a);
        icu::UnicodeString::fromUTF32(&codepoint, 1).toUTF8( bs );
    }

    template<typename Iterator>
        std::string make_error_message(boost::spirit::info const& info, Iterator first, Iterator last) {
            std::ostringstream oss;
            oss << "Illegal escape sequence. Expecting " << info << " here: \"" << std::string(first,last) << "\"";
            return oss.str();
        }
}

BOOST_PHOENIX_ADAPT_FUNCTION(void,        cp2utf8_,            my_helpers::cp2utf8,            2)
BOOST_PHOENIX_ADAPT_FUNCTION(std::string, make_error_message_, my_helpers::make_error_message, 3)

//URI         = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
//
//hier-part   = "//" authority path-abempty
//            / path-absolute
//            / path-rootless
//            / path-empty
//authority   = [ userinfo "@" ] host [ ":" port ]
//userinfo    = *( unreserved / pct-encoded / sub-delims / ":" )
//pct-encoded = "%" HEXDIG HEXDIG
//reserved    = gen-delims / sub-delims
//
//gen-delims  = ":" / "/" / "?" / "#" / "[" / "]" / "@"
//
//sub-delims  = "!" / "$" / "&" / "'" / "(" / ")"
//            / "*" / "+" / "," / ";" / "="
//unreserved  = ALPHA / DIGIT / "-" / "." / "_" / "~"
// scheme      = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
// host        = IP-literal / IPv4address / reg-name
// IP-literal = "[" ( IPv6address / IPvFuture  ) "]"
// IPvFuture  = "v" 1*HEXDIG "." 1*( unreserved / sub-delims / ":" )
//IPv6address =                            6( h16 ":" ) ls32
//            /                       "::" 5( h16 ":" ) ls32
//            / [               h16 ] "::" 4( h16 ":" ) ls32
//            / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
//            / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
//            / [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
//            / [ *4( h16 ":" ) h16 ] "::"              ls32
//            / [ *5( h16 ":" ) h16 ] "::"              h16
//            / [ *6( h16 ":" ) h16 ] "::"
//
//ls32        = ( h16 ":" h16 ) / IPv4address
//            ; least-significant 32 bits of address
//
//h16         = 1*4HEXDIG
//            ; 16 bits of address represented in hexadecimal
//            IPv4address = dec-octet "." dec-octet "." dec-octet "." dec-octet
//
//            dec-octet   = DIGIT                 ; 0-9
//                        / %x31-39 DIGIT         ; 10-99
//                        / "1" 2DIGIT            ; 100-199
//                        / "2" %x30-34 DIGIT     ; 200-249
//                        / "25" %x30-35          ; 250-255
//reg-name    = *( unreserved / pct-encoded / sub-delims )
//port        = *DIGIT
//path          = path-abempty    ; begins with "/" or is empty
//              / path-absolute   ; begins with "/" but not "//"
//              / path-noscheme   ; begins with a non-colon segment
//              / path-rootless   ; begins with a segment
//              / path-empty      ; zero characters
//
//path-abempty  = *( "/" segment )
//path-absolute = "/" [ segment-nz *( "/" segment ) ]
//path-noscheme = segment-nz-nc *( "/" segment )
//path-rootless = segment-nz *( "/" segment )
//path-empty    = 0<pchar>
//
//              segment       = *pchar
//              segment-nz    = 1*pchar
//              segment-nz-nc = 1*( unreserved / pct-encoded / sub-delims / "@" )
//                            ; non-zero-length segment without any colon ":"
//
//              pchar         = unreserved / pct-encoded / sub-delims / ":" / "@"
//              query       = *( pchar / "/" / "?" )
//              fragment    = *( pchar / "/" / "?" )
//URI-reference = URI / relative-ref
//relative-ref  = relative-part [ "?" query ] [ "#" fragment ]
//
//relative-part = "//" authority path-abempty
//              / path-absolute
//              / path-noscheme
//              / path-empty
//absolute-URI  = scheme ":" hier-part [ "?" query ]




template < typename Iterator >
QuotedString<Iterator>::QuotedString()
: QuotedString::base_type( quoted_string )
{
  quoted_string =
      '"' > *( +( char_ - ( '"' | eol | '\\' ) ) | escapes ) > '"';

  escapes =
      '\\' > (
                  escaped_character
                | ("x" > qi::uint_parser<UChar32, 16, 2, 2>())
                | ("u" > qi::uint_parser<UChar32, 16, 4, 4>())
                | ("U" > qi::uint_parser<UChar32, 16, 8, 8>())
                | (      qi::uint_parser<UChar32,  8, 1, 3>()) 
              ) [ cp2utf8_( qi::_val, qi::_1 ) ]
        ;

        escaped_character.add
            (  "a", 0x07 ) // alert
            (  "b", 0x08 ) // backspace
            (  "f", 0x0c ) // form feed
            (  "n", 0x0a ) // new line
            (  "r", 0x0d ) // carriage return
            (  "t", 0x09 ) // horizontal tab
            (  "v", 0x0b ) // vertical tab
            ( "\"", 0x22 ) // literal quotation mark
            ( "\\", 0x5c ) // literal backslash
        ;

        namespace phx = boost::phoenix;

        qi::on_error< qi::fail > (
            escapes,
            phx::throw_(
                phx::construct<std::runtime_error>( make_error_message_(qi::_4, qi::_3, qi::_2) )
            )
        );

        qi::on_error< qi::fail > (
            quoted_string,
            phx::throw_(
                phx::construct<std::runtime_error>( "Illegal string literal. (Unterminated string?)" )
            )
        );

}

#endif /* COAP_URI_PARSER_DEF_HPP_ */

