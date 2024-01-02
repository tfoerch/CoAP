#ifndef LMP_MSG_UNKNOWN_MESSAGE_AST_HPP_
#define LMP_MSG_UNKNOWN_MESSAGE_AST_HPP_
/*
 * UnknownMessageAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectSequenceAst.hpp"
#include "CommonHeaderAst.hpp"
#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    namespace ast
    {
      struct UnknownMessage
      {
        lmp::msg::ast::CommonHeaderUnknownMsgType  m_header;
        lmp::obj::ast::ObjectSequence              m_objects;
      };
      std::ostream& operator<<(
        std::ostream&          os,
        const UnknownMessage&  unknownMessage);
      bool operator==(
        const UnknownMessage&  first,
        const UnknownMessage&  second);
      lmp::WORD getLength(
        const UnknownMessage&  unknownMessage);
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_UNKNOWN_MESSAGE_AST_HPP_ */
