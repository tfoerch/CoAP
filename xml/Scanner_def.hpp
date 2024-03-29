#ifndef COAP_XML_SCANNER_DEF_HPP_
#define COAP_XML_SCANNER_DEF_HPP_
/*
 * Scanner_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "Scanner.hpp"

#define BOOST_SPIRIT_DEBUG 1
#define BOOST_SPIRIT_LEXERTL_DEBUG 1

namespace xml { namespace lexer
{
  template <typename Lexer>
  xml_tokens<Lexer>::xml_tokens()
  : m_etag_begin("<\\/", token_ids::etag_begin),
    m_tag_begin("<", token_ids::tag_begin),
//    m_emptyElem_tag_end("\\/>", token_ids::emptyElem_tag_end),
//    m_tag_end(">", token_ids::tag_end),
//    m_etag_mark("\\/", token_ids::etag_mark),
//    m_declaration_mark("!", token_ids::declaration_mark),
    m_etag_begin_TAG("<\\/", token_ids::etag_begin),
    m_tag_begin_TAG("<", token_ids::tag_begin),
    m_emptyElem_tag_end_TAG("\\/>", token_ids::emptyElem_tag_end),
    m_tag_end_TAG(">", token_ids::tag_end),
    m_etag_mark_TAG("\\/", token_ids::etag_mark),
    m_declaration_mark_TAG("!", token_ids::declaration_mark),
//    m_xml_decl_begin("<?xml", token_ids::xml_decl_begin),
//    m_xml_decl_end("?>", token_ids::xml_decl_end),
//    m_single_quota("'", token_ids::single_quota),
//    m_double_quote("\\\"", token_ids::double_quote),
//    m_equal("=", token_ids::equal),
//    m_doctypedecl_begin_mark("<!DOCTYPE", token_ids::doctypedecl_begin_mark),
//    m_cdata_begin_mark("<!\\\[CDATA\\\[", token_ids::cdata_begin_mark),
//    m_cdata_end_mark("]]>", token_ids::cdata_end_mark),
//    m_comment_begin_mark("<!--", token_ids::comment_begin_mark),
//    m_comment_end_mark("-->", token_ids::comment_end_mark),
    m_name("[:a-zA-Z_][:a-zA-Z_0-9]*", token_ids::name),
    m_char_data("[^<&>/]+", token_ids::char_data)
//    m_cdata(".*", token_ids::cdata),
//    m_whitespace("[ \t\n\r]+", token_ids::whitespace),
//    m_comment("(([^-])|([-][^-]))*", token_ids::comment)
  {

    // lexer state "INITIAL" while parsing document and element content
    this->self =
          m_etag_begin [ detail::set_lexer_state("TAG") ]
        | m_tag_begin [ detail::set_lexer_state("TAG") ]
//        | m_etag_mark
//        | m_declaration_mark
//        | m_tag_end
//        | m_emptyElem_tag_end
//        | m_name
//        | m_equal
//        | m_cdata_begin_mark [ set_lexer_state("CDATA") ]
//        | m_comment_begin_mark // [ lex::_state = "COMMENT" ]
//        | m_comment_end_mark // [ lex::_state = "INITIAL" ]
//        | m_comment
//        | m_xml_decl_begin [ lex::_state = "XMLDECL" ]
        | m_char_data
        ;

    // lexer state "TAG" while parsing element tag
    this->self("TAG") =
          m_tag_end_TAG [ detail::set_lexer_state("INITIAL") ]
        | m_emptyElem_tag_end_TAG [ detail::set_lexer_state("INITIAL") ]
        | m_etag_mark_TAG
        | m_etag_begin_TAG
        | m_tag_begin_TAG
        | m_declaration_mark_TAG
        | m_name
//        | m_whitespace
        ;

    // lexer state "XMLDECL" while parsing xml declaration
//    this->self("XMLDECL") +=
//          m_xml_decl_end [ lex::_state = "INITIAL" ]
//        | m_char_data
//        ;

    // lexer state "CDATA" while parsing cdata section
//    this->self("CDATA") +=
//          m_cdata_end_mark [ lex::_state = "INITIAL" ]
//        | m_cdata
//        ;

    // lexer state "COMMENT" while parsing comment
//    this->self("COMMENT") +=
//          m_comment_end_mark [ lex::_state = "INITIAL" ]
//        | m_comment
//        ;
    }

//    template <typename BaseIterator>
//    bool xml_tokens<BaseIterator>::add_(
//        std::string const& keyword, int id_)
//    {
//        // add the token to the lexer
//        token_ids::type id;
//        if (id_ == token_ids::invalid)
//            id = token_ids::type(this->get_next_id());
//        else
//            id = token_ids::type(id_);
//
//        this->self.add(keyword, id);
//        // store the mapping for later retrieval
//        std::pair<typename keyword_map_type::iterator, bool> p =
//            keywords_.insert(typename keyword_map_type::value_type(keyword, id));
//
//        return p.second;
//    }
  }
}

#endif /* COAP_XML_SCANNER_DEF_HPP_ */
