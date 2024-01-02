#ifndef LMP_OBJ_MESSAGE_ID_CTYPES_GENERATOR_DEF_HPP_
#define LMP_OBJ_MESSAGE_ID_CTYPES_DEF_GENERATOR_HPP_
/*
 * MessageIdCTypesGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdCTypesGenerator.hpp"
#include "obj/MessageIdGenerator_def.hpp"
#include "obj/MessageIdAckGenerator_def.hpp"
#include "obj/ObjectClassUnknownCTypeGenerator_def.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

namespace lmp
{
  namespace obj
  {
    namespace msgid
    {
      namespace generator
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        message_id_ctypes_grammar<OutputIterator>::message_id_ctypes_grammar()
        : message_id_ctypes_grammar::base_type(message_id_ctypes_rule, "message_id_ctypes")
        {
          using phoenix::at_c;
          using namespace qi::labels;

          message_id_ctypes_rule %=
              message_id |
              message_id_ack |
              unknown_msgid_ctype
              ;

          message_id_ctypes_rule.name("message_id_ctypes");
        }
      } // namespace generate
    } // namespace msgid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_CTYPES_GENERATOR_DEF_HPP_ */
