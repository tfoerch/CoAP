#ifndef COAP_XML_TOKENIDS_HPP_
#define COAP_XML_TOKENIDS_HPP_
/*
 * TokenIds.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/spirit/include/lex_lexer.hpp>

namespace xml
{
  namespace lex = boost::spirit::lex;

  struct token_ids
  {
    enum type
    {
      etag_begin = lex::tokenids::min_token_id + 1,
      tag_begin,
      emptyElem_tag_end,
      tag_end,
      etag_mark,
      declaration_mark,
      xml_decl_begin,
      xml_decl_end,
      single_quota,
      double_quote,
      equal,
      doctypedecl_begin_mark,
      cdata_begin_mark,
      cdata,
      cdata_end_mark,
      comment_begin_mark,
      comment_end_mark,
      name,
      char_data,
      comment,
      whitespace
    };
  };
}

#endif /* COAP_XML_TOKENIDS_HPP_ */
