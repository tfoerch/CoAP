#ifndef LMP_OBJ_MESSAGE_ID_CTYPES_HPP_
#define LMP_OBJ_MESSAGE_ID_CTYPES_HPP_
/*
 * MessageIdCTypesAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAst.hpp"
#include "obj/MessageIdAckAst.hpp"
#include "obj/UnknownMessageIdCTypeAst.hpp"

#include <boost/variant.hpp>

namespace lmp
{
  namespace obj
  {
    namespace msgid
    {
      namespace ast
      {
         typedef boost::variant<lmp::obj::msgid::ast::MessageId,
                                lmp::obj::msgid::ast::MessageIdAck,
                                lmp::obj::msgid::ast::UnknownMessageIdCType>   MessageIdCTypes;
         std::ostream& operator<<(
           std::ostream&        os,
           const MessageIdCTypes&  msgIdCType);
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<msgid::ast::MessageIdCTypes>(
        const msgid::ast::MessageIdCTypes&  msgIdCType);
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_CTYPES_HPP_ */
