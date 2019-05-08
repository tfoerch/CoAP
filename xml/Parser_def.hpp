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
#include "TokenStringValueLiteral.hpp"
#include "Annotation.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace xml
{
  namespace parser
  {
    namespace qi = boost::spirit::qi;
    namespace fusion = boost::fusion;
    namespace phoenix = boost::phoenix;


    template <typename Iterator, typename Lexer>
    element<Iterator, Lexer>::element(
      error_handler<typename Lexer::base_iterator_type, Iterator>& error_handler,
      Lexer const& l)
    : element::base_type(m_element, "element"),
      m_lexer(l)
    {
      qi::_1_type _1;
      qi::_2_type _2;
      qi::_3_type _3;
      qi::_4_type _4;

      qi::_val_type _val;

      using namespace qi::labels;

      using qi::eps;
      using qi::attr;
      using qi::on_error;
      using qi::on_success;
      using qi::fail;
      using boost::phoenix::function;

      typedef xml::error_handler<typename Lexer::base_iterator_type, Iterator>
        error_handler_type;
      typedef function<error_handler_type> error_handler_function;
      typedef function<xml::annotation<Iterator> > annotation_function;

      m_start_tag_prefix %=
              m_lexer.m_tag_begin
          >>  !( m_lexer.m_etag_mark |
                 m_lexer.m_comment_mark )
          >   m_lexer.m_name
      ;

      m_end_tag =
              m_lexer.m_etag_begin
          >   m_lexer.m_name [boost::spirit::_a = _1]
          >   eps(boost::spirit::_a == boost::spirit::_r1) // same name as in start_tag
          >   m_lexer.m_tag_end
          ;

      m_content %= ( m_element | l.m_name | l.m_comment )
          ;

      m_empty_element %=
              l.m_emptyElem_tag_end
          > attr(std::vector<ast::content>())
          ;

      m_element_with_content %=
              l.m_tag_end
          >   *m_content
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
      m_start_tag_prefix.name("start_tag_prefix");
      m_end_tag.name("end_tag");
      // Debugging and error handling and reporting support.
      BOOST_SPIRIT_DEBUG_NODES(
          (m_start_tag_prefix)
          (m_end_tag)
          (m_content)
          (m_element_with_content)
          (m_empty_element)
          (m_element)
      );

      // Error handling: on error in start, call error_handler.
      on_error<fail>(m_element,
                     error_handler_function(error_handler)(
                         "Error! Expecting ", _4, _3));

        // Annotation: on success in start, call annotation.
//        on_success(m_element,
//                   annotation_function(error_handler.iters)(_val, _1));
    }
  }
}
#endif /* COAP_XML_PARSER_DEF_HPP_ */


