#ifndef LMP_OBJ_MESSAGE_ID_CTYPES_GENERATOR_HPP_
#define LMP_OBJ_MESSAGE_ID_CTYPES_GENERATOR_HPP_
/*
 * MessageIdCTypesGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdGenerator.hpp"
#include "obj/MessageIdAckGenerator.hpp"
#include "obj/ObjectClassUnknownCTypeGenerator.hpp"
#include "obj/MessageIdCTypesAst.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace msgid
    {
      lmp::DWORD getLength(
        const ast::MessageIdCTypes&  controlChannelIdCTypes);
      std::ostream& operator<<(
        std::ostream&                       os,
        const ast::MessageIdCTypes&  controlChannelIdCTypes);
      namespace generator
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct message_id_ctypes_grammar : karma::grammar<OutputIterator, ast::MessageIdCTypes()>
        {
          message_id_ctypes_grammar();

          lmp::obj::generator::message_id_grammar<OutputIterator>                                   message_id;
          lmp::obj::generator::message_id_ack_grammar<OutputIterator>                               message_id_ack;
          lmp::obj::generator::object_class_unknown_ctype_grammar<OutputIterator,
                                                                 lmp::obj::ObjectClass::MessageID>  unknown_msgid_ctype;
          karma::rule<OutputIterator, ast::MessageIdCTypes()>                                       message_id_ctypes_rule;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_CTYPES_GENERATOR_HPP_ */
