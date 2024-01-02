#ifndef LMP_MSG_HELLO_AST_HPP_
#define LMP_MSG_HELLO_AST_HPP_
/*
 * HelloAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageType.hpp"
#include "msg/CommonHeaderAst.hpp"
#include "obj/HelloAst.hpp"

namespace lmp
{
  namespace msg
  {
    template <>
    struct MessageTypeTraits<MsgType::Hello>
    {
      typedef MsgType                 message_type;
      static const message_type       msg_type_value; // = MsgType::Hello;
    };
    namespace ast
    {
      struct Hello
      {
        lmp::msg::ast::CommonHeaderFlags   m_header;
        lmp::obj::hello::ast::Hello        m_hello;
      };
      std::ostream& operator<<(
        std::ostream&        os,
        const Hello&         hello);
      bool operator==(
        const Hello&   first,
        const Hello&   second);
      lmp::WORD getLength(
        const Hello&      hello);
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_HELLO_AST_HPP_ */
