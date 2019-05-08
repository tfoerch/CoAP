#ifndef COAP_XML_SCANNER_DEF_HPP_
#define COAP_XML_SCANNER_DEF_HPP_
/*
 * Scanner_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "Scanner.hpp"

namespace xml { namespace lexer
{
  template <typename BaseIterator>
  xml_tokens<BaseIterator>::xml_tokens()
  : m_etag_begin("<\\/", token_ids::etag_begin),
    m_tag_begin("<", token_ids::tag_begin),
    m_emptyElem_tag_end("\\/>", token_ids::emptyElem_tag_end),
    m_tag_end(">", token_ids::tag_end),
    m_etag_mark("\\/", token_ids::etag_mark),
    m_comment_mark("!", token_ids::comment_mark),
    m_name("[:a-zA-Z_][:a-zA-Z_0-9]*", token_ids::name),
    m_comment("<!--(([^-])|([-][^-]))*-->", token_ids::comment)
  {
    lex::_pass_type _pass;

    this->self +=
          m_etag_begin
        | m_tag_begin
        | m_tag_end
        | m_emptyElem_tag_end
        | m_etag_mark
        | m_comment_mark
        | m_name
        | m_comment
        | lex::string("[ \t\n\r]+", token_ids::whitespace)
          [
            lex::_pass = lex::pass_flags::pass_ignore
          ]
        ;
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