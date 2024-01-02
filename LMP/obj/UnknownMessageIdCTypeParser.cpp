/*
 * UnknownMessageIdCTypeParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownMessageIdCTypeAst.hpp"
#ifdef USE_SPIRIT_X3_PARSER
#include "obj/UnknownMessageIdCTypeParser_def.hpp"
#include "obj/LMPParseConfig.hpp"
#else
#include "obj/ObjectClassUnknownCTypeParser_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
#ifdef USE_SPIRIT_X3_PARSER
      namespace x3 = boost::spirit::x3;

      BOOST_SPIRIT_INSTANTIATE(
        unknown_message_id_ctype_type, iterator_type, context_type);
#else
      typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
      template struct object_class_unknown_ctype_grammar<BufIterType, lmp::obj::ObjectClass::MessageID>;
#endif /* USE_SPIRIT_X3_PARSER */

    }
  }
}

