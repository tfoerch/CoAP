#ifndef COAP_XML_PARSER_DEF_HPP_
#define COAP_XML_PARSER_DEF_HPP_
/*
 * Parser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "Parser.hpp"
#include "ErrorHandler.hpp"
//#include "TokenStringValueLiteral.hpp"
#include "Annotation.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/optional/optional_io.hpp>

namespace xml
{
  namespace parser
  {
    namespace qi = boost::spirit::qi;
    namespace fusion = boost::fusion;
    namespace phoenix = boost::phoenix;


    template <typename Iterator>
    template <typename Token>
    element<Iterator>::element(
      const Token& tokens)
    : element::base_type(m_element, "element")
    {
      using namespace qi::labels;

      using qi::debug;
      using qi::eps;
      using qi::attr;
      using qi::on_error;
      using qi::on_success;
      using qi::fail;
      using phoenix::at_c;
      using phoenix::val;
//      using boost::phoenix::function;

//      typedef xml::error_handler<typename Lexer::base_iterator_type, Iterator>
//        error_handler_type;
//      typedef function<error_handler_type> error_handler_function;
//      typedef function<xml::annotation<Iterator> > annotation_function;

      m_char_data =
          // qi::token(token_ids::char_data) [ at_c<0>(_val) = _1 ]
          tokens.m_char_data [ at_c<0>(_val) = _1 ]
          ;

#if 0
      m_comment =
          // qi::token(token_ids::comment_begin_mark)
          tokens.m_comment_begin_mark
          // > qi::token(token_ids::comment) [ at_c<0>(_val) = _1 ]
          >  tokens.m_comment [ at_c<0>(_val) = _1 ]
          // >>  qi::token(token_ids::comment_end_mark)
          >> tokens.m_comment_end_mark
          ;
#endif

      m_start_tag_prefix %=
          // qi::token(token_ids::tag_begin)
          tokens.m_tag_begin
          >>  !( /* tokens.m_etag_mark */ qi::token(token_ids::etag_mark) |
                 /* tokens.m_declaration_mark */ qi::token(token_ids::declaration_mark) )
          >   // qi::in_state("ETAG")
              // [
                 // the lexer is in the 'ETAG' state during
                 // matching of the following parser components
          // qi::token(token_ids::name)
          tokens.m_name
             // ]
          ;

      m_end_tag =
          // qi::token(token_ids::etag_begin)
          tokens.m_etag_begin
          >   tokens.m_name /* qi::token(token_ids::name) */ [boost::spirit::_a = _1]
          >   eps(boost::spirit::_a == boost::spirit::_r1) // same name as in start_tag
          >   tokens.m_tag_end_TAG /* qi::token(token_ids::tag_end) */
          ;

      m_markup_content %=
          m_element
//          (   m_element |
//              m_comment )
          >>  -m_char_data
          ;

      m_content %=
              -m_char_data
          >>  *m_markup_content // CharData? ((element | Reference | CDSect | PI | Comment) CharData?)*
          ;

      m_empty_element %=
          // qi::token(token_ids::emptyElem_tag_end)
          tokens.m_emptyElem_tag_end_TAG
          > attr(ast::Content())
          ;

      m_element_with_content %=
          // qi::token(token_ids::tag_end)
          tokens.m_tag_end_TAG
          >   m_content
          >   m_end_tag(boost::spirit::_r1)
          ;

      m_element %=
              m_start_tag_prefix[boost::spirit::_a = _1]
          >   ( m_empty_element |
                m_element_with_content(boost::spirit::_a) )
          ;

      m_element.name("element");
      m_element_with_content.name("element_with_content");
      m_empty_element.name("empty_element");
      m_content.name("content");
      m_markup_content.name("markup_content");
      m_start_tag_prefix.name("start_tag_prefix");
      m_end_tag.name("end_tag");
//      m_char_data.name("char_data");
//      m_comment.name("comment");
      // Debugging and error handling and reporting support.
      BOOST_SPIRIT_DEBUG_NODES(
//          (m_char_data)
//          (m_comment)
          (m_start_tag_prefix)
          (m_end_tag)
          (m_content)
          (m_markup_content)
          (m_element_with_content)
          (m_empty_element)
          (m_element)
      );
      debug(m_element);
      debug(m_empty_element);
      debug(m_element_with_content);
      debug(m_markup_content);
      debug(m_content);
      debug(m_end_tag);
      debug(m_start_tag_prefix);
//      debug(m_comment);
//      debug(m_char_data);
      // Error handling: on error in start, call error_handler.
//      on_error<fail>(m_element,
//                     error_handler_function(error_handler)(
//                         "Error! Expecting ", _4, _3));

        // Annotation: on success in start, call annotation.
//        on_success(m_element,
//                   annotation_function(error_handler.iters)(_val, _1));
    }
  }
}
#endif /* COAP_XML_PARSER_DEF_HPP_ */


