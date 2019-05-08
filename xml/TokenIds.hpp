#ifndef COAP_XML_TOKENIDS_HPP_
#define COAP_XML_TOKENIDS_HPP_
/*
 * TokenIds.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

namespace xml
{
  struct token_ids
  {
    enum type
    {
      invalid,
      etag_begin,
      tag_begin,
      emptyElem_tag_end,
      tag_end,
      etag_mark,
      comment_mark,
      name,
      comment,
      whitespace
    };
  };
}

#endif /* COAP_XML_TOKENIDS_HPP_ */
