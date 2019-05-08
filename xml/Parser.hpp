#ifndef COAP_XML_PARSER_HPP_
#define COAP_XML_PARSER_HPP_
/*
 * Parser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "Ast.hpp"

#include <boost/spirit/include/qi.hpp>

namespace xml
{
  template <typename BaseIterator, typename Iterator>
  struct error_handler;

  namespace parser
  {
    namespace qi = boost::spirit::qi;

    template <typename Iterator, typename Lexer>
    struct element : qi::grammar<Iterator, ast::element(), qi::locals<std::string>>
    {
      typedef error_handler<typename Lexer::base_iterator_type, Iterator>
      error_handler_type;

      element(error_handler_type& error_handler, Lexer const& l);
      template <typename Attrib, typename Context>
      void checkEndTagName(Attrib& attr, Context& context, bool& pass);

      Lexer const&                                                    m_lexer;
      qi::rule<Iterator, std::string()>                               m_start_tag_prefix;
      qi::rule<Iterator, void(std::string), qi::locals<std::string>>  m_end_tag;
      qi::rule<Iterator, std::vector<ast::content>()>                 m_empty_element;
      qi::rule<Iterator, std::vector<ast::content>(std::string)>      m_element_with_content;
      qi::rule<Iterator, ast::element(), qi::locals<std::string>>     m_element;
      qi::rule<Iterator, ast::content()>                              m_content;
    };
  }
}

#endif /* COAP_XML_PARSER_HPP_ */



