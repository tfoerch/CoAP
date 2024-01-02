#ifndef LMP_OBJ_MESSAGE_ID_ACK_AST_HPP_
#define LMP_OBJ_MESSAGE_ID_ACK_AST_HPP_
/*
 * MessageIdAckAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"
#include "obj/ObjectClassAst.hpp"
#include "obj/MessageIdClassAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#endif /* USE_SPIRIT_X3_PARSER */


namespace lmp
{
  namespace obj
  {
    template <>
    struct HeaderCTypeTraits<msgid::ClassType, msgid::ClassType::MessageIdAck>
    {
      typedef typename msgid::ClassType                ctype_type;
      static const ObjectClass                          obj_class;
      static const ctype_type                           ctype;
      static const lmp::WORD                            length;
    };
    namespace msgid
    {
      namespace ast
      {
#ifdef USE_SPIRIT_X3_PARSER
        namespace x3 = boost::spirit::x3;
#endif /* USE_SPIRIT_X3_PARSER */
        struct MessageIdAck
#ifdef USE_SPIRIT_X3_PARSER
            : x3::position_tagged
#endif /* USE_SPIRIT_X3_PARSER */
        {
          typedef
            lmp::obj::ast::ObjectHeader<HeaderCTypeTraits<msgid::ClassType,
                                                          msgid::ClassType::MessageIdAck>>  MessageIdAckHeaderType;

          MessageIdAckHeaderType  m_header;
          lmp::DWORD              m_msgId;
        };
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<msgid::ast::MessageIdAck>(
        const msgid::ast::MessageIdAck&  objCType);
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_ACK_AST_HPP_ */
